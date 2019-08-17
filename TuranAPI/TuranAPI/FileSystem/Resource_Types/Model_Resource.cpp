#include "Model_Resource.h"
using namespace TuranAPI::File_System;

#include "TuranAPI/FileSystem/DataFormats/GameResource_generated.h"

vector<Static_Model_Data*> Static_Model_Data::ALL_MODEL_DATAs = vector<Static_Model_Data*>();

Static_Model_Data::Static_Model_Data(Static_Mesh_Data** mesh_array, unsigned int mesh_number, unsigned int id) {
	//First, store the model's pointer!
	ALL_MODEL_DATAs.push_back(this);

	MESH_ARRAY_PTR = mesh_array;
	MESH_NUMBER = mesh_number;
	ID = id;
}


vec3* Static_Mesh_Data::Get_Positions() {
	return POSITIONs;
}

unsigned int* Static_Mesh_Data::Get_Indices() {
	return INDICEs;
}

vec3* Static_Mesh_Data::Get_Normals() {
	return NORMALs;
}

vec2* Static_Mesh_Data::Get_TextCoords() {
	return TEXTCOORDs;
}

vec3* Static_Mesh_Data::Get_Tangents() {
	return TANGENTs;
}

vec3* Static_Mesh_Data::Get_Bitangents() {
	return BITANGENTs;
}

int Static_Mesh_Data::Get_Vertex_Number() {
	return VERTEX_NUMBER;
}

int Static_Mesh_Data::Get_Indice_Number() {
	return INDICEs_LENGTH;
}