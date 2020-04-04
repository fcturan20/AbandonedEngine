#include "MaterialInstance_Import.h"
#include "EditorSource/FileSystem/EditorFileSystem_Core.h"
#include "TuranAPI/IMGUI/IMGUI_Core.h"

#include "EditorSource/Editors/Status_Window.h"
#include <string>

using namespace TuranAPI::File_System;
using namespace TuranAPI::IMGUI;

static Material_Instance* Create_Instance_ofMaterialType(Material_Type_Resource* material_type, Vector<Material_Uniform>& Uniform_List, const char* output_path);

MaterialInstance_CreationWindow::MaterialInstance_CreationWindow(TuranAPI::File_System::FileSystem* filesystem) : IMGUI_WINDOW("Material Instance Import"), FILESYSTEM(filesystem){}

void MaterialInstance_CreationWindow::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window(Window_Name, Is_Window_Open, false)) {
		IMGUI::End_Window();
	}

	IMGUI::Input_Text("Output Folder", &OUTPUT_FOLDER);
	IMGUI::Input_Text("Output Name", &OUTPUT_NAME);
	const char* PATH = OUTPUT_FOLDER + OUTPUT_NAME;

	Material_Instance* created_matinst;
	Vector<Material_Uniform> UNIFORM_LIST(LASTUSEDALLOCATOR, 2, 4);

	if (IMGUI::Button("Create")) {
		Material_Instance* created_matinst = Create_Instance_ofMaterialType(selected_materialtype, UNIFORM_LIST, PATH);
		FILESYSTEM->Add_Content_toFileList(created_matinst);
		delete PATH;
	}


	Vector<const char*> item_names(LASTUSEDALLOCATOR, 100, 1000);
	for (size_t i = 0; i < Material_Type_Resource::ALL_MATERIALTYPEs.size(); i++) {
		Resource_Type* RESOURCE = Material_Type_Resource::ALL_MATERIALTYPEs[i];
		item_names.push_back(RESOURCE->NAME);
	}
	static int selected_list_item_index = 0;
	
	const char* nameof_selectlistline = "Material Type List";
	std::size_t selected_listitemindex = selected_list_item_index;
	//Show Material Type list and if one of them is selected, create uniforms for the material instance
	if (IMGUI::SelectList_OneLine(nameof_selectlistline, &selected_listitemindex, &item_names)) {
		selected_materialtype = TuranAPI::File_System::Material_Type_Resource::ALL_MATERIALTYPEs[selected_list_item_index];
		for (unsigned int i = 0; i < selected_materialtype->UNIFORMs.size(); i++) {
			Material_Uniform& UNIFORM = selected_materialtype->UNIFORMs[i];
			UNIFORM_LIST.push_back(UNIFORM);
		}
	}

	if (IMGUI::Begin_Tree("Uniform List")) {
		for (unsigned int i = 0; i < UNIFORM_LIST.size(); i++) {
			Material_Uniform* UNIFORM = &UNIFORM_LIST[i];

			if (IMGUI::Begin_Tree(std::to_string(i).c_str())) {
				IMGUI::Input_Text("Uniform Name", &UNIFORM->VARIABLE_NAME);
				
				IMGUI::End_Tree();
			}
		}
		IMGUI::End_Tree();
	}


	IMGUI::End_Window();
}


//Output Path should be Directory + Name. Like "C:/dev/Content/First". Every Material Instance has .matinstcont extension!
TuranAPI::File_System::Material_Instance* Create_Instance_ofMaterialType(TuranAPI::File_System::Material_Type_Resource* material_type, Vector<Material_Uniform>& UNIFORM_LIST, const char* output_path) {
	Material_Instance* MATERIAL_INSTANCE = new Material_Instance;
		MATERIAL_INSTANCE->ID = FileSystem::Create_Resource_ID();
	MATERIAL_INSTANCE->Material_Type = material_type;
	std::string NAME = output_path;
	NAME = NAME.substr(NAME.find_last_of('/') + 1);
	NAME = NAME.substr(0, NAME.find_last_of('.'));
	MATERIAL_INSTANCE->NAME = NAME.c_str();
	MATERIAL_INSTANCE->UNIFORM_LIST = material_type->UNIFORMs;
	const char* PATH = Text_Add(output_path, ".matinstcont");
	std::cout << "Path of Material Instance is: " << PATH << std::endl;
	MATERIAL_INSTANCE->PATH = PATH;
	delete PATH;
	return MATERIAL_INSTANCE;
}