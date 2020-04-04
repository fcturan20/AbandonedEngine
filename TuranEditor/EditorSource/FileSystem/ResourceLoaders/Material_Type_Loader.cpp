#include "Material_Type_Loader.h"
#include "EditorSource/FileSystem/EditorFileSystem_Core.h"
//To show import status
#include "EditorSource/Editors/Status_Window.h"
//To compile shader program!
#include "GFXSource/GFX_Core.h"
#include <string>

using namespace TuranAPI::File_System;
using namespace TuranAPI::IMGUI;

std::initializer_list<const char*> uniformnamelist{ "Unsigned Integer 32-bit", "Integer 32-bit", "Float 32-bit", "Vec2 (2 float)", "Vec3 (3 float)", "Vec4 (4 float)", "Matrix 4x4", "Texture 2D" };
static Vector<const char*> UNIFORM_VAR_TYPE_NAMEs(LASTUSEDALLOCATOR, 0, uniformnamelist);
Material_Import_Window::Material_Import_Window(TuranAPI::File_System::FileSystem* filesystem)
	: IMGUI_WINDOW("Material Type Import"), FILESYSTEM(filesystem), Material_Uniforms(LASTUSEDALLOCATOR, 4, 4), selectlist_vector(LASTUSEDALLOCATOR, 4, 10){}

TuranAPI::TuranAPI_ENUMs Find_in_Uniform_VarTypes(const int& var_type);

void Material_Import_Window::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window(Window_Name, Is_Window_Open, false)) {
		IMGUI::End_Window();
	}

	std::cout << "Material Type Import screen is active!\n";
	IMGUI::Input_Text("Vertex Resource Path", &MATERIALTYPE_VERTEX_PATH);
	IMGUI::Input_Text("Fragment Resource Path", &MATERIALTYPE_FRAGMENT_PATH);
	IMGUI::Input_Text("Output Folder", &OUTPUT_FOLDER);
	IMGUI::Input_Text("Output Name", &OUTPUT_NAME);
	
	if (IMGUI::Button("Import")) {
		String status;
		const char* PATH = OUTPUT_FOLDER + OUTPUT_NAME;

		//Check if this resource is already loaded to Content_List!
		for (size_t i = 0; i < FILESYSTEM->Get_Const_FileListContentVector()->size(); i++) {
			Resource_Type* RESOURCE = (*FILESYSTEM->Get_Const_FileListContentVector())[i];
			if (PATH == RESOURCE->PATH) {
				status = "Resource is already loaded and is in the Resource List!";
				Status_Window* error_window = new Status_Window(status);
				return;
			}
		}


		//A little check for each uniform! Only variable names are checked.
		for (unsigned int i = 0; i < Material_Uniforms.size(); i++) {
			Material_Uniform& UNIFORM = Material_Uniforms[i];
			if (UNIFORM.VARIABLE_NAME == "") {
				std::cout << "A uniform's name isn't set, please check all uniform names!\n";
				SLEEP_THREAD(8);
				IMGUI::End_Window();
				return;
			}
		}
		Resource_Type* imported_resource = Material_Type_Loader::Load_MaterialType(MATERIALTYPE_VERTEX_PATH, MATERIALTYPE_FRAGMENT_PATH, PATH, &Material_Uniforms, &status);
		Status_Window* error_window = new Status_Window(status);
		if (imported_resource) {
			FILESYSTEM->Add_Content_toFileList(imported_resource);
		}

		Material_Uniforms.clear();
		selectlist_vector.clear();
		

		//Finish the window here! No status checking for now!
		Is_Window_Open = false;
		IMGUI::End_Window();
		return;
	}

	IMGUI::Same_Line();
	if (IMGUI::Button("Add Uniform")) {
		Material_Uniforms.push_back(Material_Uniform());
	}
	IMGUI::Same_Line();
	if (IMGUI::Button("Read Material Type")) {
		VERTEX_SOURCE = *FileSystem::Read_TextFile(MATERIALTYPE_VERTEX_PATH, LASTUSEDALLOCATOR);
		FRAGMENT_SOURCE = *FileSystem::Read_TextFile(MATERIALTYPE_FRAGMENT_PATH, LASTUSEDALLOCATOR);
		is_Reading_Shaders = true;
	}
	selectlist_vector.resize(Material_Uniforms.size());
	if (IMGUI::Begin_Tree("Uniform List")) {
		for (unsigned int i = 0; i < Material_Uniforms.size(); i++) {
			Material_Uniform* UNIFORM = &Material_Uniforms[i];

			if (IMGUI::Begin_Tree(std::to_string(i).c_str())) {
				IMGUI::Input_Text("Uniform Name", &UNIFORM->VARIABLE_NAME);
				size_t selected = selectlist_vector[i];
				if (IMGUI::SelectList_OneLine("Uniform Variable Type", &selected, &UNIFORM_VAR_TYPE_NAMEs)) {
					UNIFORM->VARIABLE_TYPE = Find_in_Uniform_VarTypes(selectlist_vector[i]);
					if (UNIFORM->VARIABLE_TYPE == TuranAPI::TuranAPI_ENUMs::TURAN_NULL)
						Status_Window* error_window = new Status_Window("Error: Intended var_type index isn't supported for now in Find_in_Uniform_VarTypes! This means, UNIFORM_VARTYPEs string vector doesn't match with this function!");
				}
				IMGUI::End_Tree();
			}
		}
		IMGUI::End_Tree();
	}
	if (is_Reading_Shaders) {
		IMGUI::Text("Vertex Source:");
		IMGUI::Text(VERTEX_SOURCE);
		IMGUI::Text("Fragment Source:");
		IMGUI::Text(FRAGMENT_SOURCE + "\n\n");
	}


	IMGUI::End_Window();
}




//Use this function to import a shader stage first time! Not for reloading a shader!
//Output Path defines DIRECTORY + NAME! Like "C:/dev/Content/First_Material". Every MatType has .mattypecont extension!
TuranAPI::File_System::Resource_Type* Material_Type_Loader::Load_MaterialType(const char* vertex_path, const char* fragment_path, const char* output_path, Vector<Material_Uniform>* material_inputs, String* compilation_status) {
	//Name and Save Location calculations! Name will only be used in UI for better user experience.
	std::string PATH = *output_path + ".mattypecont";

	//Check if this resource is already compiled and saved!
	for (size_t i = 0; i < EDITOR_FILESYSTEM->Get_Const_FileListContentVector()->size(); i++) {
		Resource_Type* RESOURCE = (*EDITOR_FILESYSTEM->Get_Const_FileListContentVector())[i];
		if (PATH.c_str() == RESOURCE->PATH) {
			*compilation_status = "Resource is already loaded before and is in the Resource List!";;
			return nullptr;
		}
	}

	//Get the source codes of the shaders!
	const char* vertex_source = *FileSystem::Read_TextFile(vertex_path);
	const char* fragment_source = *FileSystem::Read_TextFile(fragment_path);

	const char* gfx_compile_status = "";
	TuranAPI::LOG_NOTCODED("In Material_Type_Loader, Compile_MaterialType(&gfx_compile_status, &vertex_source, &fragment_source); should be coded in NOT_CODED's line!", true);

	if (gfx_compile_status != "") {
		*compilation_status = gfx_compile_status;
		return nullptr;
	}
	//If application arrives here, that means shader compiles perfectly!

	TuranAPI::File_System::Material_Type_Resource* MATERIAL = new TuranAPI::File_System::Material_Type_Resource();
	MATERIAL->VERTEX_SOURCE = vertex_source;
	MATERIAL->FRAGMENT_SOURCE = fragment_source;
	MATERIAL->GFX_API = TuranAPI::TuranAPI_ENUMs::OPENGL4;
	delete vertex_source;
	delete fragment_source;

	//Add Material Uniforms to compiled resource
	for (unsigned int i = 0; i < material_inputs->size(); i++) {
		Material_Uniform& material_uniform = (*material_inputs)[i];
		MATERIAL->UNIFORMs.push_back(material_uniform);
	}

	//Set material's other things to help saving!
	MATERIAL->PATH = PATH.c_str();
	auto NAME = PATH.substr(PATH.find_last_of('/') + 1);
	NAME = NAME.substr(0, NAME.find_last_of('.'));
	MATERIAL->NAME = NAME.c_str();

	//For now, all of the shader's will be set as OpenGL3 shader!
	FileSystem::Write_a_Resource_toDisk(MATERIAL);
	
	*compilation_status = "Succesfully compiled and saved the resource to disk!";
	return MATERIAL;
}


TuranAPI::TuranAPI_ENUMs Find_in_Uniform_VarTypes(const int& var_type) {
	switch (var_type) {
	case 0:
		return TuranAPI::TuranAPI_ENUMs::VAR_UINT32;
	case 1:
		return TuranAPI::TuranAPI_ENUMs::VAR_INT32;
	case 2:
		return TuranAPI::TuranAPI_ENUMs::VAR_FLOAT32;
	case 3:
		return TuranAPI::TuranAPI_ENUMs::VAR_VEC2;
	case 4:
		return TuranAPI::TuranAPI_ENUMs::VAR_VEC3;
	case 5:
		return TuranAPI::TuranAPI_ENUMs::VAR_VEC4;
	case 6:
		return TuranAPI::TuranAPI_ENUMs::VAR_MAT4x4;
	case 7:
		return TuranAPI::TuranAPI_ENUMs::API_TEXTURE_2D;
	default:
		return TuranAPI::TuranAPI_ENUMs::TURAN_NULL;
	}
}