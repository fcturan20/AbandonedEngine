#include "EditorFileSystem_Core.h"
#include "TuranAPI/Profiler/Profiler_Core.h"
//Data Formats created by Flatbuffers!
#include <flatbuffers/flatbuffers.h>
#include "TuranAPI/FileSystem/DataFormats/GameResource_generated.h"

using namespace Editor::File_System;
using namespace TuranAPI::File_System;
string GameContentList_PATH = "C:/dev/TuranEngine/TuranEditor/File_List.enginecont";

TuranAPI::File_System::FileList_Resource Editor_FileSystem::GameContentList_onDisk(GameContentList_PATH);

static Editor_FileSystem* SELF = nullptr;
GameContent::File_Type Convert_to_GameCont_Type(TuranAPI::TuranAPI_ENUMs resource_type);



void Editor_FileSystem::Start_EditorFileSystem() {
	SELF = new Editor_FileSystem;
}

void Editor_FileSystem::Load_GameContents_fromDisk() {
	cout << "Game Contents are being loaded now!\n";
	TuranAPI::Profiler::Profiler_Core::Start_Timing();

	TuranAPI::File_System::FileSystem::Load_Resources_fromFileList(&GameContentList_onDisk);

	cout << "Game Contents are loaded in " << TuranAPI::Profiler::Profiler_Core::Get_Timing_in_Seconds() << " seconds!\n";
	TuranAPI::Profiler::Profiler_Core::End_Timing();
	cout << "Game Contents loaded!\n";
}


void Editor_FileSystem::Clear_GlobalGameContentList() {
	cout << "Clearing the Game Content List!\n";

	for (Resource_Type* RESOURCE : *GameContentList_onDisk.Get_ContentListVector()) {
		string PATH = RESOURCE->PATH;

		FileSystem::Delete_File(PATH);
		//Clear all of the loaded resources from the memory
		delete RESOURCE;
		RESOURCE = nullptr;
	}
	//Clear all of the loaded resource references!
	GameContentList_onDisk.Get_ContentListVector()->clear();

	FileSystem::Write_a_Resource_toDisk(&GameContentList_onDisk);
}

GameContent::File_Type Convert_to_GameCont_Type(TuranAPI::TuranAPI_ENUMs resource_type) {
	switch (resource_type) {
	case TuranAPI::STATIC_MODEL_RESOURCE:
		return GameContent::File_Type_Static_Model;
	case TuranAPI::MATERIAL_TYPE_RESOURCE:
		return GameContent::File_Type_Material_Type;
	case TuranAPI::TEXTURE_RESOURCE:
		return GameContent::File_Type_Texture;
	default:
		cout << "Error: Intended resource type isn't found in FileList!\n";
		TuranAPI::Breakpoint();
		return GameContent::File_Type_ERROR;
	}
}

TuranAPI::File_System::Resource_Type* Editor_FileSystem::Get_GameContent_byName(string NAME) {
	for (Resource_Type* RESOURCE : *GameContentList_onDisk.Get_ContentListVector()) {
		if (RESOURCE->NAME == NAME) {
			return RESOURCE;
		}
	}
}

TuranAPI::File_System::Resource_Type* Editor_FileSystem::Get_GameContent_byID(unsigned int ID) {
	for (Resource_Type* RESOURCE : *GameContentList_onDisk.Get_ContentListVector()) {
		if (RESOURCE->ID == ID) {
			return RESOURCE;
		}
	}
}

TuranAPI::File_System::FileList_Resource* Editor_FileSystem::Get_GameContentList() {
	return &GameContentList_onDisk;
}