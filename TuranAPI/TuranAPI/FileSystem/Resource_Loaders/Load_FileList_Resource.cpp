#include "TuranAPI/FileSystem/FileSystem_Core.h"
#include "TuranAPI/FileSystem/Resource_Types/FileList_Resource.h"
#include "TuranAPI/FileSystem/Resource_Types/Scene_Resource.h"

//Data Formats created by Flatbuffers!
#include <flatbuffers/flatbuffers.h>
#include "TuranAPI/FileSystem/DataFormats/GameResource_generated.h"
#include <string>
#include <vector>

using namespace TuranAPI::File_System;
GameContent::File_Type Convert_to_GameCont_Type(TuranAPI::TuranAPI_ENUMs resource_type);

void FileSystem::Load_Resources_fromFileList(FileList_Resource* FileList_Resource, IAllocator* Allocator) {
	void* File_List_Data = nullptr;
	//No usage for now!
	unsigned int data_size;
	File_List_Data = FileSystem::Read_BinaryFile(FileList_Resource->PATH, data_size);
	while (!File_List_Data) {
		std::cout << "Please enter a new valid PATH: ";
		std::string PATH_str;
		std::cin >> PATH_str;
		String PATH = PATH_str.c_str();
		File_List_Data = FileSystem::Read_BinaryFile(PATH, data_size);
		FileList_Resource->PATH = PATH;
	}

	auto RESOURCE_typeless = GameContent::GetResource(File_List_Data);
	if (RESOURCE_typeless == nullptr) {
		std::cout << "Error: Loading failed! File List isn't a valid resource!\n";
		return;
	}
	auto File_List = RESOURCE_typeless->TYPE_as_File_List();

	if (!File_List) {
		std::cout << "Type isn't File List, Type definition is wrong!\n";
		return;
	}
	auto File_Vector = File_List->FILE_LIST();

	struct TemporarySceneLoadingStruct {
		//Load the scene last!
		void* Scene_data = nullptr; unsigned int Scene_ID = 0; String Scene_PATH = "";
	};
	Vector<TemporarySceneLoadingStruct> All_Scenes(LASTUSEDALLOCATOR, 10, 10);

	//For each file that is in File_List.enginecont!
	for (unsigned int i = 0; i < File_Vector->Length(); i++) {
		auto FILE = File_Vector->Get(i);

		const char* PATH = FILE->PATH()->c_str();
		auto TYPE = FILE->TYPE();
		auto ID = FILE->ID();

		void* data = nullptr;
		unsigned int data_size;
		std::cout << "Reading the file: " << PATH << std::endl;
		data = FileSystem::Read_BinaryFile(PATH, data_size);

		//If compiled resource isn't found!
		if (data == nullptr) {
			std::cout << "Resource isn't found in path: " << PATH << std::endl;
			continue;
		}
		Resource_Type* loaded_resource = nullptr;
		std::cout << "Data size: " << data_size << std::endl;

		
		
		//If the resource is valid!
		switch (TYPE) {
		case GameContent::File_Type_Static_Model:
			loaded_resource = FileSystem::Load_Model(data, ID, PATH);
			break;
		case GameContent::File_Type_Material_Type:
			loaded_resource = FileSystem::Load_Material_Type(data, ID, PATH);
			break;
		case GameContent::File_Type_Texture:
			loaded_resource = FileSystem::Load_Texture(data, ID, PATH);
			break;
		case GameContent::File_Type_Material_Instance:
			loaded_resource = FileSystem::Load_Material_Inst(data, ID, PATH);
			break;
		case GameContent::File_Type_Scene:
			All_Scenes.push_back(TemporarySceneLoadingStruct{data, ID, PATH});
			break;
		default:
			std::cout << "Loaded file's type isn't supported, but this shouldn't have happened! Problem maybe the exporting progress!\n";
			TuranAPI::Breakpoint();
			return;
		}
		if (loaded_resource != nullptr) {
			if (!loaded_resource->Verify_Resource_Data()) {
				TuranAPI::Breakpoint("There is a resource isn't verified in FileList: " + FileList_Resource->NAME + "!");
			}
		}
		else {
			if (TYPE != GameContent::File_Type_Scene) {
				TuranAPI::Breakpoint("There is a loaded resource that is nullptr in FileList: " + FileList_Resource->NAME + "! So it isn't added to loaded Content List vector.");
				continue;
			}
			else {
				//Resource Type is Scene, it is loaded later!
				continue;
			}
		}
		FileList_Resource->Get_ContentListVector()->push_back(loaded_resource);
	}

	if (All_Scenes.size() > 0) {
		for (unsigned int ALLSCENEs_INDEX = 0; ALLSCENEs_INDEX < All_Scenes.size(); ALLSCENEs_INDEX++) {
			//Load the scene last!
			Scene_Resource* SCENE = (Scene_Resource*)FileSystem::Load_Scene(
				All_Scenes[ALLSCENEs_INDEX].Scene_data, All_Scenes[ALLSCENEs_INDEX].Scene_ID, All_Scenes[ALLSCENEs_INDEX].Scene_PATH);
			FileList_Resource->Get_ContentListVector()->push_back(SCENE);
		}
	}
}

void Save_a_FileList_toDisk(Resource_Type* FileList_Data) {
	FileList_Resource* FileList = (FileList_Resource*)FileList_Data;

	//Create a flatbufferbuilder and FileList to build the data!
	flatbuffers::FlatBufferBuilder builder(1024);


	//Read each Resource_File struct and create a File struct for each of them!
	//Store each created File struct in a vector to set FileList's vector!
	std::vector<flatbuffers::Offset<GameContent::File>> Resources;
	for (std::size_t i = 0; i < FileList->Get_ContentListVector()->size();i++) {
		Resource_Type* RESOURCE = (*FileList->Get_ContentListVector())[i];
		if (RESOURCE == nullptr || !RESOURCE->Verify_Resource_Data()) {
			continue;
		}
		std::cout << "Adding resource to GameContent List: " << RESOURCE->PATH << std::endl;
		auto PATH = builder.CreateString(RESOURCE->PATH);
		auto RESOURCE_TYPE = RESOURCE->Get_Resource_Type();
		GameContent::FileBuilder file_build(builder);
		file_build.add_PATH(PATH);
		file_build.add_TYPE(Convert_to_GameCont_Type(RESOURCE->Get_Resource_Type()));
		std::cout << "ID: " << RESOURCE->ID << std::endl;
		file_build.add_ID(RESOURCE->ID);
		auto finished_file = file_build.Finish();
		Resources.push_back(finished_file);
		std::cout << "Added resource to GameContent List: " << RESOURCE->PATH << std::endl;
	}
	auto finished_vector = builder.CreateVector(Resources);

	auto finished_filelist = GameContent::CreateFileList(builder, finished_vector, FileSystem::Get_LAST_ID());
	//Create, initialize and finish editing the File_List!
	auto finished_RESOURCE = GameContent::CreateResource(builder, GameContent::Resource_Type_File_List, finished_filelist.Union());
	builder.Finish(finished_RESOURCE);

	//Get data pointer and data size from builder!
	void* data = builder.GetBufferPointer();
	unsigned int data_size = builder.GetSize();

	//Overwrite the File_List with new File_List!
	FileSystem::Overwrite_BinaryFile(FileList->PATH, data, data_size);
}

GameContent::File_Type Convert_to_GameCont_Type(TuranAPI::TuranAPI_ENUMs resource_type) {
	switch (resource_type) {
	case TuranAPI::TuranAPI_ENUMs::STATIC_MODEL_RESOURCE:
		return GameContent::File_Type_Static_Model;
	case TuranAPI::TuranAPI_ENUMs::MATERIAL_TYPE_RESOURCE:
		return GameContent::File_Type_Material_Type;
	case TuranAPI::TuranAPI_ENUMs::TEXTURE_RESOURCE:
		return GameContent::File_Type_Texture;
	case TuranAPI::TuranAPI_ENUMs::MATERIAL_INSTANCE_RESOURCE:
		return GameContent::File_Type_Material_Instance;
	case TuranAPI::TuranAPI_ENUMs::SCENE_RESOURCE:
		return GameContent::File_Type_Scene;
	default:
		std::cout << "Error: Intended resource type isn't found in FileList!\n";
		TuranAPI::Breakpoint();
		return GameContent::File_Type_ERROR;
	}
}