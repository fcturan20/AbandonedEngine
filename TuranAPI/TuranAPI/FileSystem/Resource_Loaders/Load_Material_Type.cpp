#include "TuranAPI/FileSystem/FileSystem_Core.h"
//Data Formats created by Flatbuffers!
#include <flatbuffers/flatbuffers.h>
#include "TuranAPI/FileSystem/DataFormats/GameResource_generated.h"

using namespace TuranAPI::File_System;


GameContent::GFX_APIs Convert_to_GameContent_GFXAPIs(TuranAPI::TuranAPI_ENUMs language) {
	switch (language) {
	case TuranAPI::TuranAPI_ENUMs::OPENGL4:
		return GameContent::GFX_APIs_OPENGL3;
	default:
		std::cout << "Material Type's GFX_API can't be converted to File_List::GFX_APIs! OpenGL 3 is returned!\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		return GameContent::GFX_APIs_OPENGL3;
	}
}

TuranAPI::TuranAPI_ENUMs Convert_to_TuranAPIEnums_GFXAPIs(GameContent::GFX_APIs language) {
	switch (language) {
	case GameContent::GFX_APIs_OPENGL3:
		return TuranAPI::TuranAPI_ENUMs::OPENGL4;
	default:
		std::cout << "Material Type file's type can't be converted to TuranAPIEnums!\n";
		return TuranAPI::TuranAPI_ENUMs::TURAN_NULL;
	}
}

Material_Type_Resource* Find_MaterialType_byID(unsigned int ID) {
	/*
	for (unsigned int i = 0; i < Material_Type_Resource::ALL_MATERIALTYPEs.size(); i++) {
		Material_Type_Resource* material_type = Material_Type_Resource::ALL_MATERIALTYPEs[i];
		if (material_type->Get_ID() == ID) {
			return material_type;
		}
	}*/
	return nullptr;
}

TuranAPI::TuranAPI_ENUMs Convert_to_TuranAPIEnums_UniformVarType(GameContent::MATERIAL_INSTANCE_UNIFORM uniform_var_type) {
	switch (uniform_var_type) {
	case GameContent::MATERIAL_INSTANCE_UNIFORM_UINT32:
		return TuranAPI::TuranAPI_ENUMs::VAR_UINT32;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_INT32:
		return TuranAPI::TuranAPI_ENUMs::VAR_INT32;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_FLOAT:
		return TuranAPI::TuranAPI_ENUMs::VAR_FLOAT32;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_VEC2:
		return TuranAPI::TuranAPI_ENUMs::VAR_VEC2;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_VEC3:
		return TuranAPI::TuranAPI_ENUMs::VAR_VEC3;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_VEC4:
		return TuranAPI::TuranAPI_ENUMs::VAR_VEC4;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_Mat4x4:
		return TuranAPI::TuranAPI_ENUMs::VAR_MAT4x4;
	case GameContent::MATERIAL_INSTANCE_UNIFORM_TEXTURE2D:
		return TuranAPI::TuranAPI_ENUMs::API_TEXTURE_2D;
	default:
		std::cout << "Error: Uniform Var type couldn't be converted to TuranAPIEnums in Convert_to_TuranAPIEnums_UniformVarType() in Load_Material_Type.cpp!\n";
		SLEEP_THREAD(10);
	}
}

String Get_UniformName_fromFlatbuffer(const GameContent::MATERIAL_INSTANCE_UNIFORM_TABLE* flatbuffer_uniform, TuranAPI::TuranAPI_ENUMs uniform_var_type) {
	switch (uniform_var_type) {
	case TuranAPI::TuranAPI_ENUMs::VAR_UINT32:
		return flatbuffer_uniform->UNIFORM_as_UINT32()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::VAR_INT32:
		return flatbuffer_uniform->UNIFORM_as_INT32()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::VAR_FLOAT32:
		return flatbuffer_uniform->UNIFORM_as_FLOAT()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC2:
		return flatbuffer_uniform->UNIFORM_as_VEC2()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC3:
		return flatbuffer_uniform->UNIFORM_as_VEC3()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC4:
		return flatbuffer_uniform->UNIFORM_as_VEC4()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::VAR_MAT4x4:
		return flatbuffer_uniform->UNIFORM_as_Mat4x4()->NAME()->str().c_str();
	case TuranAPI::TuranAPI_ENUMs::API_TEXTURE_2D:
		return flatbuffer_uniform->UNIFORM_as_TEXTURE2D()->NAME()->str().c_str();
	default:
		std::cout << "Error: Uniform Var Type isn't supported in Get_UniformName_fromFlatbuffer() in Load_Material_Type.cpp!\n";
		SLEEP_THREAD(10);
	}
}

//Load material resource from the data provided by FileList.enginecont
Resource_Type* FileSystem::Load_Material_Type(void* data, unsigned int id, const char* path, IAllocator* Allocator) {
	auto RESOURCE_typeless = GameContent::GetResource(data);
	if (RESOURCE_typeless == nullptr) {
		std::cout << "Error: Loading failed! Material Type isn't a valid resource!\n";
		return nullptr;
	}
	std::cout << "Loading Material Type (Shader Stage) ID: " << id << std::endl;
	auto RESOURCE = RESOURCE_typeless->TYPE_as_Material_Type();

	if (!RESOURCE) {
		std::cout << "Type isn't Material Type, type definition is wrong!\n";
		return nullptr;
	}
	if (id > SELF->LAST_ID) {
		SELF->LAST_ID = id;
	}


	Material_Type_Resource* material = new Material_Type_Resource;
	material->GFX_API = Convert_to_TuranAPIEnums_GFXAPIs(RESOURCE->GFX_API());
	material->VERTEX_SOURCE = RESOURCE->VERTEX_SHADER()->str().c_str();
	material->FRAGMENT_SOURCE = RESOURCE->FRAGMENT_SHADER()->str().c_str();
	material->PATH = path;
	material->ID = id;

	//Uniform loading progress!
	for (unsigned int i = 0; i < RESOURCE->MATERIAL_INPUTs()->size(); i++) {
		Material_Uniform uniform;
		auto UNIFORM_typeless = RESOURCE->MATERIAL_INPUTs()->Get(i);
		uniform.VARIABLE_TYPE = Convert_to_TuranAPIEnums_UniformVarType(UNIFORM_typeless->UNIFORM_type());
		uniform.VARIABLE_NAME = Get_UniformName_fromFlatbuffer(UNIFORM_typeless, uniform.VARIABLE_TYPE);
		material->UNIFORMs.push_back(uniform);
	}

	std::string NAME = path;
	NAME = NAME.substr(NAME.find_last_of('/') + 1);
	NAME = NAME.substr(0, NAME.find_last_of('.'));
	material->NAME = NAME.c_str();
	return material;
}

flatbuffers::Offset<void> Create_a_Uniform(flatbuffers::FlatBufferBuilder* builder, const Material_Uniform* material_uniform);
GameContent::Mat4x4 Create_a_Flatbuffer_Matrix4x4(flatbuffers::FlatBufferBuilder* builder, mat4x4 read_matrix);
//mat4x4 Read_a_Flatbuffer_Mat4x4(GameContent::Mat4x4* read_matrix);
GameContent::MATERIAL_INSTANCE_UNIFORM Convert_to_Flatbufer_Uniform_Type(TuranAPI::TuranAPI_ENUMs uniform_type);

//Create flatbuffer data to export resource into a .gamecont
void Save_a_MaterialType_toDisk(Resource_Type* Resource_Data) {
	Material_Type_Resource* Material_Type = (Material_Type_Resource*)Resource_Data;
	flatbuffers::FlatBufferBuilder builder(1024);


	std::vector<flatbuffers::Offset<GameContent::MATERIAL_INSTANCE_UNIFORM_TABLE>> MATERIAL_UNIFORMs;
	//Add uniforms to Flatbuffer data!
	for (std::size_t i = 0; i < Material_Type->UNIFORMs.size(); i++) {
		Material_Uniform& material_uniform = Material_Type->UNIFORMs[i];
		std::cout << "Uniform is being proccessed: " << material_uniform.VARIABLE_NAME << std::endl;
		MATERIAL_UNIFORMs.push_back(
			GameContent::CreateMATERIAL_INSTANCE_UNIFORM_TABLE(builder, 
				Convert_to_Flatbufer_Uniform_Type(material_uniform.VARIABLE_TYPE), 
				Create_a_Uniform(&builder, &material_uniform)
			)
		);

	}
	auto finished_UNIFORMs_VECTOR = builder.CreateVector(MATERIAL_UNIFORMs);

	auto VERTEX_SOURCE = builder.CreateString(Material_Type->VERTEX_SOURCE);
	auto FRAGMENT_SOURCE = builder.CreateString(Material_Type->FRAGMENT_SOURCE);
	auto Graphics_Language = Convert_to_GameContent_GFXAPIs(Material_Type->GFX_API);
	auto MATERIAL_TYPE = GameContent::CreateMATERIAL_TYPE(builder, Graphics_Language, VERTEX_SOURCE, FRAGMENT_SOURCE, finished_UNIFORMs_VECTOR);
	auto FINISHED_RESOURCE_DATA = GameContent::CreateResource(builder, GameContent::Resource_Type_Material_Type, MATERIAL_TYPE.Union());
	builder.Finish(FINISHED_RESOURCE_DATA);

	unsigned int data_size = builder.GetSize();

	std::cout << "Compiled Material Type Resource to Flatbuffer type!\n";
	void* data_ptr = builder.GetBufferPointer();

	//Check if the data is complete!
	flatbuffers::Verifier verifier((uint8_t*)data_ptr, data_size);
	if (!GameContent::VerifyResourceBuffer(verifier)) {
		std::cout << "Data isn't verified for name: " << Material_Type->NAME << std::endl;
		assert(false && "Error while compiling data to disk!");
	}

	std::cout << "Exporting resource as a .mattypecont: " << Resource_Data->PATH << std::endl;
	FileSystem::Overwrite_BinaryFile(Resource_Data->PATH, data_ptr, data_size);

	std::cout << "Resource is successfully added to the Content_List.enginecont\n";
}

GameContent::MATERIAL_INSTANCE_UNIFORM Convert_to_Flatbufer_Uniform_Type(TuranAPI::TuranAPI_ENUMs uniform_type) {
	switch (uniform_type) {
	case TuranAPI::TuranAPI_ENUMs::VAR_UINT32:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_UINT32;
	case TuranAPI::TuranAPI_ENUMs::VAR_INT32:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_INT32;
	case TuranAPI::TuranAPI_ENUMs::VAR_FLOAT32:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_FLOAT;
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC2:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_VEC2;
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC3:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_VEC3;
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC4:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_VEC4;
	case TuranAPI::TuranAPI_ENUMs::VAR_MAT4x4:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_Mat4x4;
	case TuranAPI::TuranAPI_ENUMs::API_TEXTURE_2D:
		return GameContent::MATERIAL_INSTANCE_UNIFORM_TEXTURE2D;
	default:
		std::cout << "There is a problem with Convert_to_Flatbuffer_Uniform_Type!\n";
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}
}

//Create uniforms with no data!
flatbuffers::Offset<void> Create_a_Uniform(flatbuffers::FlatBufferBuilder* builder, const Material_Uniform* material_uniform) {
	auto UNIFORM_NAME = builder->CreateString(material_uniform->VARIABLE_NAME);
	switch (material_uniform->VARIABLE_TYPE) {
	case TuranAPI::TuranAPI_ENUMs::VAR_UINT32:
		return GameContent::CreateUNIFORM_UINT32(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::VAR_INT32:
		return GameContent::CreateUNIFORM_UINT32(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::VAR_FLOAT32:
		return GameContent::CreateUNIFORM_FLOAT(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC2:
		return GameContent::CreateUNIFORM_VEC2(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC3:
		return GameContent::CreateUNIFORM_VEC3(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::VAR_VEC4:
		return GameContent::CreateUNIFORM_VEC4(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::VAR_MAT4x4:
		return GameContent::CreateUNIFORM_MAT4x4(*builder, UNIFORM_NAME).Union();
	case TuranAPI::TuranAPI_ENUMs::API_TEXTURE_2D:
		return GameContent::CreateUNIFORM_TEXTURE2D(*builder, UNIFORM_NAME).Union();
	default:
		std::cout << "There is a problem in Create_a_Uniform!\n";
		TuranAPI::Breakpoint();
	}
}

GameContent::Mat4x4 Create_a_Flatbuffer_Matrix4x4(flatbuffers::FlatBufferBuilder* builder, mat4x4 read_matrix) {
	GameContent::Vec4 first_row(read_matrix[0][0], read_matrix[1][0], read_matrix[2][0], read_matrix[3][0]);
	GameContent::Vec4 second_row(read_matrix[0][1], read_matrix[1][1], read_matrix[2][1], read_matrix[3][1]);
	GameContent::Vec4 third_row(read_matrix[0][2], read_matrix[1][2], read_matrix[2][2], read_matrix[3][2]);
	GameContent::Vec4 fourth_row(read_matrix[0][3], read_matrix[1][3], read_matrix[2][3], read_matrix[3][3]);
	return GameContent::Mat4x4(first_row, second_row, third_row, fourth_row);
}

/*
mat4x4 Read_a_Flatbuffer_Mat4x4(GameContent::Mat4x4* read_matrix) {
	mat4x4 return_matrix;
	return_matrix[0][0] = read_matrix->ROW_1().x;	return_matrix[1][0] = read_matrix->ROW_1().y;	return_matrix[2][0] = read_matrix->ROW_1().z;	return_matrix[3][0] = read_matrix->ROW_1().w;
	return_matrix[0][1] = read_matrix->ROW_2().x;	return_matrix[1][1] = read_matrix->ROW_2().y;	return_matrix[2][1] = read_matrix->ROW_2().z;	return_matrix[3][1] = read_matrix->ROW_2().w;
	return_matrix[0][2] = read_matrix->ROW_3().x;	return_matrix[1][2] = read_matrix->ROW_3().y;	return_matrix[2][2] = read_matrix->ROW_3().z;	return_matrix[3][2] = read_matrix->ROW_3().w;
	return_matrix[0][3] = read_matrix->ROW_4().x;	return_matrix[1][3] = read_matrix->ROW_4().y;	return_matrix[2][3] = read_matrix->ROW_4().z;	return_matrix[3][3] = read_matrix->ROW_4().w;
	return return_matrix;
}*/