#include "Content_Browser.h"
#include "EditorSource/FileSystem/EditorFileSystem_Core.h"
#include "TuranAPI/API_IMGUI.h"
#include "GFXSource/GFX_FileSystem.h"

#include "Status_Window.h"
#include "Properties_Window.h"

#include "EditorSource/FileSystem/ResourceLoaders/Model_Loader.h"
#include "EditorSource/FileSystem/ResourceLoaders/Material_Type_Loader.h"
#include "EditorSource/FileSystem/ResourceLoaders/MaterialInstance_Import.h"
#include "EditorSource/FileSystem/ResourceLoaders/Texture_Loader.h"
#include "EditorSource/Editors/Scene_Editor.h"


using namespace TuranAPI::IMGUI;
using namespace TuranAPI::File_System;
using namespace Editor::File_System;

GameContent_Browser::GameContent_Browser() : IMGUI_WINDOW("GameContent Browser") {

}

void GameContent_Browser::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window(Window_Name, Is_Window_Open, false)) {
		IMGUI::End_Window();
		return;
	}
	if (GameContent_EditMode) {
		vector<string> item_names;
		for (Resource_Type* RESOURCE : *Editor_FileSystem::Get_GameContentList()->Get_ContentListVector()) {
			item_names.push_back(RESOURCE->NAME);
		}
		GameContentList_CheckList.resize(item_names.size(), false);

		if (IMGUI::Button("Delete All")) {
			Editor_FileSystem::Clear_GlobalGameContentList();
			GameContentList_CheckList.clear();
			GameContent_EditMode = false;
		}
		IMGUI::Same_Line();
		if (IMGUI::Button("Delete")) {
			vector<Resource_Type*>* Vector_to_Erase = Editor_FileSystem::Get_GameContentList()->Get_ContentListVector();
			if (Vector_to_Erase->size() != GameContentList_CheckList.size()) {
				cout << "Error: in Delete Items from Vector(), 2 vectors should have same size!\n";
				TuranAPI::Breakpoint();
			}
			for (unsigned int i = 0; i < Vector_to_Erase->size(); i++) {
				bool should_erase = GameContentList_CheckList[i];
				if (should_erase) {
					Resource_Type* resource_to_delete = (*Vector_to_Erase)[i];
					FileSystem::Delete_File(resource_to_delete->PATH);
					delete resource_to_delete;
					resource_to_delete = nullptr;
					Vector_to_Erase->erase(Vector_to_Erase->begin() + i);
					GameContentList_CheckList.erase(GameContentList_CheckList.begin() + i);
					i -= 1;
					cout << "Deleted an item!\n";
				}
			}
			GameContentList_CheckList.clear();
			GameContent_EditMode = false;
			TuranAPI::File_System::FileSystem::Write_a_Resource_toDisk(Editor_FileSystem::Get_GameContentList());
		}
		IMGUI::Same_Line();
		if (IMGUI::Button("Cancel")) {
			GameContentList_CheckList.clear();
			GameContent_EditMode = false;
		}
		else {
			IMGUI::CheckListBox("Game Content List", &GameContentList_CheckList, &item_names);
		}

		IMGUI::End_Window();
		return;
	}
	else {
		if (IMGUI::Button("Edit List")) {
			GameContent_EditMode = true;
		}
		IMGUI::Same_Line();
		//Import Buttons
		{
			if (IMGUI::Button("Import Model")) {new Model_Import_Window(Editor::File_System::Editor_FileSystem::Get_GameContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Import Material Type")) {new Material_Import_Window(Editor::File_System::Editor_FileSystem::Get_GameContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Import Texture")) {new Texture_Import_Window(Editor::File_System::Editor_FileSystem::Get_GameContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Create Material Instance")) {new MaterialInstance_ImportWindow(Editor::File_System::Editor_FileSystem::Get_GameContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Create Scene")) { new Scene_Create_Window(Editor::File_System::Editor_FileSystem::Get_GameContentList()); }
		}

		//Even if there is a importing proccess, show the contents!
		int selected_list_item_index = -1;
		vector<string> item_names;
		for (Resource_Type* RESOURCE : *Editor::File_System::Editor_FileSystem::Get_GameContentList()->Get_ContentListVector()) {
			item_names.push_back(RESOURCE->NAME);
		}
		//Show selected content's properties!
		if (IMGUI::Selectable_ListBox("Game Content List", &selected_list_item_index, &item_names)) {
			ResourceProperties_Window* properties = new ResourceProperties_Window(
				(*Editor::File_System::Editor_FileSystem::Get_GameContentList()->Get_ContentListVector())[selected_list_item_index]
			);
		}

		IMGUI::End_Window();
		return;
	}
}


GFX_Content_Browser::GFX_Content_Browser() : IMGUI_WINDOW("GFX Content Browser"){}

void GFX_Content_Browser::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window(Window_Name, Is_Window_Open, false)) {
		IMGUI::End_Window();
		return;
	}
	if (GFXContent_EditMode) {
		vector<string> item_names;
		for (Resource_Type* RESOURCE : *GFX_FileSystem::Get_GFXContentList()->Get_ContentListVector()) {
			item_names.push_back(RESOURCE->NAME);
		}
		GFXContentList_CheckList.resize(item_names.size(), false);

		if (IMGUI::Button("Delete All")) {
			GFX_API::FileSystem->Clear_All_GFXContents();
			GFXContentList_CheckList.clear();
			GFXContent_EditMode = false;
		}
		IMGUI::Same_Line();
		if (IMGUI::Button("Delete")) {
			vector<Resource_Type*>* Vector_to_Erase = GFX_FileSystem::Get_GFXContentList()->Get_ContentListVector();
			if (Vector_to_Erase->size() != GFXContentList_CheckList.size()) {
				cout << "Error: Vector to Erase and Erase list doesn't match in Content Browser.cpp!\n";
				TuranAPI::Breakpoint();
			}
			for (unsigned int i = 0; i < Vector_to_Erase->size(); i++) {
				bool should_erase = GFXContentList_CheckList[i];
				if (should_erase) {
					Vector_to_Erase->erase(Vector_to_Erase->begin() + i);
					GFXContentList_CheckList.erase(GFXContentList_CheckList.begin() + i);
					i -= 1;
					cout << "Deleted an item!\n";
				}
			}
			GFXContentList_CheckList.clear();
			GFXContent_EditMode = false;
			TuranAPI::File_System::FileSystem::Write_a_Resource_toDisk(GFX_FileSystem::Get_GFXContentList());
		}
		IMGUI::Same_Line();
		if (IMGUI::Button("Cancel")) {
			GFXContentList_CheckList.clear();
			GFXContent_EditMode = false;
		}
		else {
			IMGUI::CheckListBox("GFX Content List", &GFXContentList_CheckList, &item_names);
		}

		IMGUI::End_Window();
		return;
	}
	else {
		if (IMGUI::Button("Edit List")) {
			GFXContent_EditMode = true;
		}
		IMGUI::Same_Line();
		//Import Buttons
		{
			if (IMGUI::Button("Import Model")) { Model_Import_Window* import_window = new Model_Import_Window(GFX_FileSystem::Get_GFXContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Import Material Type")) { Material_Import_Window* import_window = new Material_Import_Window(GFX_FileSystem::Get_GFXContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Import Texture")) { Texture_Import_Window* import_window = new Texture_Import_Window(GFX_FileSystem::Get_GFXContentList()); }
			IMGUI::Same_Line();
			if (IMGUI::Button("Create Material Instance")) { MaterialInstance_ImportWindow* import_window = new MaterialInstance_ImportWindow(GFX_FileSystem::Get_GFXContentList()); }
		}

		//Even if there is a importing proccess, show the contents!
		int selected_list_item_index = -1;
		vector<string> item_names;
		for (Resource_Type* RESOURCE : *GFX_FileSystem::Get_GFXContentList()->Get_ContentListVector()) {
			item_names.push_back(RESOURCE->NAME);
		}
		//Show selected content's properties!
		if (IMGUI::Selectable_ListBox("GFX Content List", &selected_list_item_index, &item_names)) {
			ResourceProperties_Window* properties = new ResourceProperties_Window(
				(*GFX_API::FileSystem->Get_GFXContentList()->Get_ContentListVector())[selected_list_item_index]
			);
		}

		IMGUI::End_Window();
		return;
	}
}