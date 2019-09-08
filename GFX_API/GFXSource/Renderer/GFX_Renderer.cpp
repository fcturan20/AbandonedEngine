#include "GFX_Renderer.h"

GFX_Renderer* GFX_Renderer::Renderer_OBJ = nullptr;

GFX_Renderer::~GFX_Renderer() {
	cout << "Renderer is destroying!\n";
}

void GFX_Renderer::Compile_All_MaterialTypes() {
	for (TuranAPI::File_System::Material_Type_Resource* MATERIAL_TYPE : TuranAPI::File_System::Material_Type_Resource::ALL_MATERIAL_TYPEs) {
		string compilation_status;
		Renderer_OBJ->Compile_MaterialType(&compilation_status, &MATERIAL_TYPE->VERTEX_SOURCE, &MATERIAL_TYPE->FRAGMENT_SOURCE, &MATERIAL_TYPE->PROGRAM_ID, &MATERIAL_TYPE->VERTEX_ID, &MATERIAL_TYPE->FRAGMENT_ID);
	}
}