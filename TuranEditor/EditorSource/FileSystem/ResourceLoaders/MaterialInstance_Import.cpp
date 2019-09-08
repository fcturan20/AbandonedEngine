#include "MaterialInstance_Import.h"
#include "EditorSource/FileSystem/EditorFileSystem_Core.h"
#include "TuranAPI/IMGUI/IMGUI_Core.h"

#include "EditorSource/Editors/Status_Window.h"

using namespace TuranAPI::File_System;
using namespace TuranAPI::IMGUI;

MaterialInstance_ImportWindow::MaterialInstance_ImportWindow(TuranAPI::File_System::FileList_Resource* filelist) : IMGUI_WINDOW("Material Instance Import"), FILELIST(filelist){}

void MaterialInstance_ImportWindow::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window(Window_Name, Is_Window_Open, false)) {
		IMGUI::End_Window();
	}

	IMGUI::Input_Text("Output Folder", &OUTPUT_FOLDER);
	IMGUI::Input_Text("Output Name", &OUTPUT_NAME);
	string PATH = OUTPUT_FOLDER + OUTPUT_NAME;
	if (IMGUI::Button("Import")) {
		Material_Instance* created_matinst = FileSystem::Create_Instance_ofMaterialType(selected_materialtype, PATH);
		FileSystem::Write_a_Resource_toDisk(created_matinst);
		FILELIST->Get_ContentListVector()->push_back(created_matinst);
		FileSystem::Write_a_Resource_toDisk(FILELIST);
	}


	vector<string> item_names;
	for (Resource_Type* RESOURCE : TuranAPI::File_System::Material_Type_Resource::ALL_MATERIAL_TYPEs) {
		item_names.push_back(RESOURCE->NAME);
	}
	static int selected_list_item_index = 0;
	//Show selected content's properties!
	if (IMGUI::SelectList_OneLine("Material Type List", &selected_list_item_index, &item_names)) {
		selected_materialtype = TuranAPI::File_System::Material_Type_Resource::ALL_MATERIAL_TYPEs[selected_list_item_index];
	}



	IMGUI::End_Window();
}