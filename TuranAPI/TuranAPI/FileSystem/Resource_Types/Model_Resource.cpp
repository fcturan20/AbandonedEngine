#include "Model_Resource.h"
using namespace TuranAPI::File_System;

vector<Static_Model_Data*> Static_Model_Data::ALL_MODEL_DATAs = vector<Static_Model_Data*>{};

Static_Mesh_Data::~Static_Mesh_Data() {
	delete[] POSITIONs;
	delete[] NORMALs;
	delete[] TEXTCOORDs;
	delete[] TANGENTs;
	delete[] BITANGENTs;
}



//Static Model Data class function definitions

Static_Model_Data::Static_Model_Data(Static_Mesh_Data** mesh_array, unsigned int mesh_number, unsigned int id, string name) {
	//First, store the model's pointer!
	ALL_MODEL_DATAs.push_back(this);

	MESH_ARRAY_PTR = mesh_array;
	MESH_NUMBER = mesh_number;
	ID = id;
	NAME = name;
}

Static_Model_Data::Static_Model_Data() : Resource_Type() {
	//First, store the model's pointer!
	ALL_MODEL_DATAs.push_back(this);
}

		//GETTER-SETTERs

unsigned int Static_Model_Data::Get_Mesh_Number() {
	return MESH_NUMBER;
}
Static_Mesh_Data* Static_Model_Data::Get_Mesh_byIndex(unsigned int index) {
	return MESH_ARRAY_PTR[index];
}
void Static_Model_Data::Set_ID_and_NAME(unsigned int id, string name) {
	ID = id;
	NAME = name;
}

Static_Model_Data* Static_Model_Data::Find_Model_byID(unsigned int ID) {
	for (Static_Model_Data* MODEL : Static_Model_Data::ALL_MODEL_DATAs) {
		if (ID == MODEL->ID) {
			return MODEL;
		}
	}
	cout << "ERROR: Intended Model isn't found by ID!: " << ID << endl;
	TuranAPI::Breakpoint();
}

TuranAPI::TuranAPI_ENUMs Static_Model_Data::Get_Resource_Type() {
	return STATIC_MODEL_RESOURCE;
}


const vec3* Static_Mesh_Data::Get_Positions() const {
	return POSITIONs;
}

const unsigned int* Static_Mesh_Data::Get_Indices() const {
	return INDICEs;
}

const vec3* Static_Mesh_Data::Get_Normals() const {
	return NORMALs;
}

const vec2* Static_Mesh_Data::Get_TextCoords() const {
	return TEXTCOORDs;
}

const vec3* Static_Mesh_Data::Get_Tangents() const {
	return TANGENTs;
}

const vec3* Static_Mesh_Data::Get_Bitangents() const {
	return BITANGENTs;
}

int Static_Mesh_Data::Get_Vertex_Number() const {
	return VERTEX_NUMBER;
}

int Static_Mesh_Data::Get_Indice_Number() const {
	return INDICEs_LENGTH;
}

void Static_Mesh_Data::Set_GFXI_Mesh(void* gpu_mesh) {
	GFXI_MESH = gpu_mesh;
}