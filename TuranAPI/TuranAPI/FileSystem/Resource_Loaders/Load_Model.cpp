#include "TuranAPI/FileSystem/FileSystem_Core.h"
using namespace TuranAPI::File_System;

void FileSystem::Load_Model(void* data, unsigned int id) {
	cout << "Loading a mesh, ID is: " << id << endl;
	auto RESOURCE = GameContent::GetResource(data)->TYPE_as_Static_Model();

	//Get how much material the model has!
	unsigned int Material_Number = RESOURCE->MATERIALs()->Length();
	unsigned int Mesh_Number = RESOURCE->MESHes()->Length();

	//Material Instance loading
	for (unsigned int flatbuffer_material_index = 0; flatbuffer_material_index < Material_Number; flatbuffer_material_index++) {

	}

	//Static_Mesh_Data will be created as pointer, so array will store pointers!
	//So, create a Pointer for "Pointer Array"
	Static_Mesh_Data** Meshes_Array = new Static_Mesh_Data* [Mesh_Number];

	//For each mesh!
	for (unsigned int flatbuffer_mesh_index = 0; flatbuffer_mesh_index < Mesh_Number; flatbuffer_mesh_index++) {
		auto MESH = RESOURCE->MESHes()->Get(flatbuffer_mesh_index);
		auto POSITIONs = MESH->Positions();
		auto TEXTCOORDs = MESH->TextCoords();
		auto NORMALs = MESH->Normals();
		auto TANGENTs = MESH->Tangents();
		auto BITANGENTs = MESH->Bitangents();
		auto INDICEs = MESH->Indices();
		unsigned int Material_Index = MESH->Material_Index();
	}

	//Create a model!
	Static_Model_Data* model = new Static_Model_Data(Meshes_Array, Mesh_Number, id);
}