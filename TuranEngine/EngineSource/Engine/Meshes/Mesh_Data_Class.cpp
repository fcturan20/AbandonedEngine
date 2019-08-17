#include "Mesh_Data_Class.h"

string Mesh_Data::Get_Name() {
	return NAME;
}


void* Mesh_Data::Get_GFXI_Mesh() {
	return GFX_MESH;
}

void Mesh_Data::Set_GFXI_Mesh(void* gfx_mesh) {
	GFX_MESH = gfx_mesh;
}