#include "TuranAPI/API_FileSystem.h"
//Data Formats created by Flatbuffers!
#include <flatbuffers/flatbuffers.h>
#include "TuranAPI/FileSystem/DataFormats/GameResource_generated.h"

using namespace TuranAPI::File_System;
GameContent::File_Type Convert_to_GameCont_Type(TuranAPI::TuranAPI_ENUMs resource_type);

void FileSystem::Load_Resources_fromFileList(FileList_Resource* Empty_File_List) {
	void* File_List_Data = nullptr;
	//No usage for now!
	unsigned int data_size;
	File_List_Data = FileSystem::Read_BinaryFile(Empty_File_List->PATH, data_size);


	auto RESOURCE_typeless = GameContent::GetResource(File_List_Data);
	if (RESOURCE_typeless == nullptr) {
		cout << "Error: Loading failed! File List isn't a valid resource!\n";
		return;
	}
	auto File_List = RESOURCE_typeless->TYPE_as_File_List();

	if (!File_List) {
		cout << "Type isn't File List, Type definition is wrong!\n";
		return;
	}
	auto File_Vector = File_List->FILE_LIST();

	//Load the scene last!
	void* Scene_data = nullptr; unsigned int Scene_ID = 0; string Scene_PATH = "";

	//For each file that is in File_List.enginecont!
	for (unsigned int i = 0; i < File_Vector->Length(); i++) {
		auto FILE = File_Vector->Get(i);
		string PATHx = FILE->PATH()->c_str();
		string Name = PATHx.substr(PATHx.find_last_of('/') + 1);
		Name = Name.substr(0, Name.find_last_of('.'));

		const char* PATH = FILE->PATH()->c_str();
		auto TYPE = FILE->TYPE();
		auto ID = FILE->ID();

		void* data = nullptr;
		unsigned int data_size;
		cout << "Reading the file: " << PATH << endl;
		data = FileSystem::Read_BinaryFile(PATH, data_size);

		//If compiled resource isn't found!
		if (data == nullptr) {
			cout << "Resource isn't found in path: " << PATH << endl;
			continue;
		}
		Resource_Type* loaded_resource;
		cout << "Data size: " << data_size << endl;

		

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
			Scene_data = data; Scene_ID = ID; Scene_PATH = PATH;
			break;
		default:
			cout << "Loaded file's type isn't supported, but this shouldn't have happened! Problem maybe the exporting progress!\n";
			TuranAPI::Breakpoint();
			return;
		}
		Empty_File_List->Get_ContentListVector()->push_back(loaded_resource);
	}

	if (Scene_data == nullptr) {
		cout << "There is no scene data!\n";
	}
	else {
		//Load the scene last!
		Scene_Resource* SCENE = (Scene_Resource*)FileSystem::Load_Scene(Scene_data, Scene_ID, Scene_PATH);
		Empty_File_List->Get_ContentListVector()->push_back(SCENE);
	}
}

void Save_a_FileList_toDisk(Resource_Type* FileList_Data) {
	FileList_Resource* FileList = (FileList_Resource*)FileList_Data;

	//Create a flatbufferbuilder and FileList to build the data!
	flatbuffers::FlatBufferBuilder builder(1024);


	//Read each Resource_File struct and create a File struct for each of them!
	//Store each created File struct in a vector to set FileList's vector!
	vector<flatbuffers::Offset<GameContent::File>> resources;
	for (Resource_Type* RESOURCE : *FileList->Get_ContentListVector()) {
		if (RESOURCE == nullptr || RESOURCE->PATH == "") {
			continue;
		}
		cout << "Adding resource to GameContent List: " << RESOURCE->PATH << endl;
		auto PATH = builder.CreateString(RESOURCE->PATH);
		auto RESOURCE_TYPE = RESOURCE->Get_Resource_Type();
		GameContent::FileBuilder file_build(builder);
		file_build.add_PATH(PATH);
		file_build.add_TYPE(Convert_to_GameCont_Type(RESOURCE->Get_Resource_Type()));
		cout << "ID: " << RESOURCE->ID << endl;
		file_build.add_ID(RESOURCE->ID);
		auto finished_file = file_build.Finish();
		resources.push_back(finished_file);
		cout << "Added resource to GameContent List: " << RESOURCE->PATH << endl;
	}
	auto finished_vector = builder.CreateVector(resources);

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
	case TuranAPI::STATIC_MODEL_RESOURCE:
		return GameContent::File_Type_Static_Model;
	case TuranAPI::MATERIAL_TYPE_RESOURCE:
		return GameContent::File_Type_Material_Type;
	case TuranAPI::TEXTURE_RESOURCE:
		return GameContent::File_Type_Texture;
	case TuranAPI::MATERIAL_INSTANCE_RESOURCE:
		return GameContent::File_Type_Material_Instance;
	case TuranAPI::SCENE_RESOURCE:
		return GameContent::File_Type_Scene;
	default:
		cout << "Error: Intended resource type isn't found in FileList!\n";
		TuranAPI::Breakpoint();
		return GameContent::File_Type_ERROR;
	}
}