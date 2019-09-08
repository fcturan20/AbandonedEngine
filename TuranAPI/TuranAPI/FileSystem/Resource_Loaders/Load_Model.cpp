#include "TuranAPI/FileSystem/DataFormats/GameResource_generated.h"
#include "TuranAPI/API_FileSystem.h"
using namespace TuranAPI::File_System;
using namespace TuranAPI::Game_Object;

Resource_Type* FileSystem::Load_Model(void* data, unsigned int id, const string& path) {
	cout << "Loading a model, ID is: " << id << endl;
	auto RESOURCE_typeless = GameContent::GetResource(data);
	if (RESOURCE_typeless == nullptr) {
		cout << "Error: Loading failed! Model isn't a valid resource!\n";
		return nullptr;
	}
	auto RESOURCE = RESOURCE_typeless->TYPE_as_Static_Model();

	if (!RESOURCE) {
		cout << "Type isn't Static Model, Type definition is wrong!\n";
		return nullptr;
	}

	//Get how much material the model has!
	//unsigned int Material_Number = RESOURCE->MATERIALs()->Length();
	unsigned int Mesh_Number = RESOURCE->MESHes()->Length();
	
	if (id > LAST_ID) {
		LAST_ID = id;
	}

	/*
	//Material Instance loading
	for (unsigned int flatbuffer_material_index = 0; flatbuffer_material_index < Material_Number; flatbuffer_material_index++) {
		assert(true || "Define Material Instance loading process!\n");
	}*/

	//Static_Mesh_Data will be created as pointer, so array will store pointers!
	//So, create a Pointer for "Pointer Array"
	Static_Mesh_Data** Meshes_Array = new Static_Mesh_Data* [Mesh_Number];

	//For each mesh!
	for (unsigned int mesh_index = 0; mesh_index < Mesh_Number; mesh_index++) {
		auto MESH = RESOURCE->MESHes()->Get(mesh_index);
		if (MESH == nullptr) {
			cout << "Error: Mesh is nullptr!\n";
			continue;
		}
		Static_Mesh_Data* Static_Mesh = new Static_Mesh_Data;
		Static_Mesh->POSITIONs = (vec3*)MESH->Positions()->Data();
		Static_Mesh->TEXTCOORDs = (vec2*)MESH->TextCoords()->Data();
		Static_Mesh->NORMALs = (vec3*)MESH->Normals()->Data();
		Static_Mesh->TANGENTs = (vec3*)MESH->Tangents()->Data();
		Static_Mesh->BITANGENTs = (vec3*)MESH->Bitangents()->Data();
		Static_Mesh->INDICEs = (unsigned int*)MESH->Indices()->Data();
		Static_Mesh->VERTEX_NUMBER = MESH->Positions()->Length();
		Static_Mesh->INDICEs_LENGTH = MESH->Indices()->Length();
		Meshes_Array[mesh_index] = Static_Mesh;

		//unsigned int Material_Index = MESH->Material_Index();
		//assert(false && "Set loaded Material Instances to compiled Static_Mesh_Data s!");
	}

	string NAME = path.substr(path.find_last_of('/') + 1);
	NAME = NAME.substr(0, NAME.find_last_of('.'));
	//Create a model!
	Static_Model_Data* model = new Static_Model_Data(Meshes_Array, Mesh_Number, id, NAME);
	model->PATH = path;
	for (unsigned int i = 0; i < model->Get_Mesh_Number(); i++) {
		Static_Mesh_Data* mesh = model->Get_Mesh_byIndex(i);

		unsigned int total_size = 0;
		total_size += mesh->VERTEX_NUMBER * ((sizeof(vec3) * 4) + sizeof(vec2));
		total_size += mesh->INDICEs_LENGTH * sizeof(unsigned int);
		cout << "Size in bytes: " << total_size << endl;
	}
	return model;
}


void Save_a_StaticModel_toDisk(Resource_Type* resource_data) {
	Static_Model_Data* Model_Data = (Static_Model_Data*)resource_data;

	//Create a flatbufferbuilder and FileList to build the data!
	flatbuffers::FlatBufferBuilder builder(1024);

	vector<flatbuffers::Offset<GameContent::MESH>> FLATBUFFER_MESHES;
	//For each mesh of the model!
	for (unsigned int mesh_index = 0; mesh_index < Model_Data->Get_Mesh_Number(); mesh_index++) {
		Static_Mesh_Data* MESH = Model_Data->Get_Mesh_byIndex(mesh_index);

		//Add POSITIONs attribute to a vector!
		vector<GameContent::Vec3> FLATBUFFER_POSITIONs;
		for (unsigned int position_index = 0; position_index < MESH->Get_Vertex_Number(); position_index++) {
			FLATBUFFER_POSITIONs.push_back(
				GameContent::Vec3(
					(MESH->Get_Positions())[position_index].x,
					(MESH->Get_Positions())[position_index].y,
					(MESH->Get_Positions())[position_index].z
				)
			);
		}

		//Add TEXTCOORDs attribute to a vector!
		vector<GameContent::Vec2> FLATBUFFER_TEXTCOORDs;
		for (unsigned int textcoord_index = 0; textcoord_index < MESH->Get_Vertex_Number(); textcoord_index++) {
			FLATBUFFER_TEXTCOORDs.push_back(
				GameContent::Vec2(
					(MESH->Get_TextCoords())[textcoord_index].x,
					(MESH->Get_TextCoords())[textcoord_index].y
				)
			);
		}

		//Add NORMALs attribute to a vector!
		vector<GameContent::Vec3> FLATBUFFER_NORMALs;
		for (unsigned int normal_index = 0; normal_index < MESH->Get_Vertex_Number(); normal_index++) {
			FLATBUFFER_NORMALs.push_back(
				GameContent::Vec3(
					(MESH->Get_Normals())[normal_index].x,
					(MESH->Get_Normals())[normal_index].y,
					(MESH->Get_Normals())[normal_index].z
				)
			);
		}

		//Add TANGENTs attribute to a vector!
		vector<GameContent::Vec3> FLATBUFFER_TANGENTs;
		for (unsigned int tangent_index = 0; tangent_index < MESH->Get_Vertex_Number(); tangent_index++) {
			FLATBUFFER_TANGENTs.push_back(
				GameContent::Vec3(
					(MESH->Get_Tangents())[tangent_index].x,
					(MESH->Get_Tangents())[tangent_index].y,
					(MESH->Get_Tangents())[tangent_index].z
				)
			);
		}

		//Add BITANGENTs attribute to a vector!
		vector<GameContent::Vec3> FLATBUFFER_BITANGENTs;
		for (unsigned int bitangent_index = 0; bitangent_index < MESH->Get_Vertex_Number(); bitangent_index++) {
			FLATBUFFER_BITANGENTs.push_back(
				GameContent::Vec3(
					(MESH->Get_Tangents())[bitangent_index].x,
					(MESH->Get_Tangents())[bitangent_index].y,
					(MESH->Get_Tangents())[bitangent_index].z
				)
			);
		}

		vector<unsigned int> FLATBUFFER_INDICEs;
		for (unsigned int indice_index = 0; indice_index < MESH->Get_Indice_Number(); indice_index++) {
			FLATBUFFER_INDICEs.push_back((MESH->Get_Indices())[indice_index]);
		}

		auto FINISHED_MESH_DATA = GameContent::CreateMESHDirect(builder, &FLATBUFFER_POSITIONs, &FLATBUFFER_TEXTCOORDs, &FLATBUFFER_NORMALs, &FLATBUFFER_TANGENTs, &FLATBUFFER_BITANGENTs, &FLATBUFFER_INDICEs);
		FLATBUFFER_MESHES.push_back(FINISHED_MESH_DATA);
	}
	auto FINISHED_MESHES_VECTOR = builder.CreateVector(FLATBUFFER_MESHES);

	auto FINISHED_MODEL_DATA = GameContent::CreateSTATIC_MODEL(builder, FINISHED_MESHES_VECTOR);
	auto FINISHED_RESOURCE_DATA = GameContent::CreateResource(builder, GameContent::Resource_Type_Static_Model, FINISHED_MODEL_DATA.Union());
	builder.Finish(FINISHED_RESOURCE_DATA);

	void* data_ptr = builder.GetBufferPointer();
	unsigned int data_size = builder.GetSize();

	
	//Check if the data is complete!
	flatbuffers::Verifier verifier((uint8_t*)data_ptr, data_size);
	if (!GameContent::VerifyResourceBuffer(verifier)) {
		cout << "Data isn't verified for name: " << Model_Data->NAME << endl;
		assert(false && "Error while compiling data to disk!");
	}

	cout << "Exporting resource as a .meshcont: " << resource_data->PATH << endl;
	FileSystem::Overwrite_BinaryFile(resource_data->PATH, data_ptr, data_size);

	cout << "Resource is successfully added to the Content_List.enginecont\n";
	
}

