#include "FileSystem_Core.h"
//Data Formats created by Flatbuffers!
#include <flatbuffers/flatbuffers.h>
#include "DataFormats/GameResource_generated.h"

#include <fstream>
#include <sstream>

using namespace TuranAPI::File_System;


void Save_a_MaterialType_toDisk(Resource_Type* Material_Type_Data);
void Save_a_MaterialInst_toDisk(Resource_Type* Material_Inst_Data);
void Save_a_StaticModel_toDisk(Resource_Type* Model_Data);
void Save_a_Texture_toDisk(Resource_Type* Texture_Data);
void Save_a_Scene_toDisk(Resource_Type* Scene_Data);
void Save_a_FileList_toDisk(Resource_Type* FileList_Data);


FileSystem* FileSystem::SELF = nullptr;
String* FileSystem::Read_TextFile(const char* path, TuranAPI::MemoryManagement::IAllocator* Allocator) {
	String* finalstring = new (Allocator) String;
	std::ifstream textfile;
	textfile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		textfile.open(path);
		std::stringstream string_data;
		string_data << textfile.rdbuf();
		textfile.close();
		*finalstring = string_data.str().c_str();
		return finalstring;
	}
	catch (std::ifstream::failure error)
	{
		std::cout << "Error: Text file couldn't read: " << path << std::endl;
		return finalstring;
	}
}

void FileSystem::Write_TextFile(const char* text, const char* path, bool write_to_end) {
	if (write_to_end) {
		std::ofstream Output_File;
		Output_File.open(path, std::ios::out | std::ios::app);
		Output_File << text << std::endl;
		Output_File.close();
	}
	else {
		std::ofstream Output_File;
		Output_File.open(path, std::ios::out | std::ios::trunc);
		Output_File << text << std::endl;
		Output_File.close();
	}
}

void FileSystem::Write_TextFile(const String* text, const char* path, bool write_to_end) {
	if (write_to_end) {
		std::ofstream Output_File;
		Output_File.open(path, std::ios::out | std::ios::app);
		Output_File << *text << std::endl;
		Output_File.close();
	}
	else {
		std::ofstream Output_File;
		Output_File.open(path, std::ios::out | std::ios::trunc);
		Output_File << *text << std::endl;
		Output_File.close();
	}
}

//If read fails, data_ptr is set to nullptr!
void* FileSystem::Read_BinaryFile(const char* path, unsigned int& size, IAllocator*) {
	std::ifstream Binary_File;
	Binary_File.open(path, std::ios::binary | std::ios::in | std::ios::ate);
	if (!(Binary_File.is_open())) {
		std::cout << "There is no such file: " << path << std::endl;
		return nullptr;
	}

	Binary_File.seekg(0, std::ios::end);
	int length = Binary_File.tellg();
	Binary_File.seekg(0, std::ios::beg);
	char* read_data = new char[length];
	Binary_File.read(read_data, length);
	Binary_File.close();
	size = length;
	return read_data;
}

//Use only for creating new binary files! 
//If you want to overwrite to a file, Overwrite_BinaryFile is available!
void FileSystem::Write_BinaryFile(const char* path, void* data, unsigned int size) {
	//Try to create to a file (Check if the operation fails)
	std::ofstream Output_File(path, std::ios::binary | std::ios::out);
	if (!Output_File.is_open()) {
		//TuranAPI::Breakpoint(Text_Add(path, " couldn't be outputted!\n"));
		return;
	}

	//Write to a file and finish all of the operation!
	Output_File.write((const char*)data, size);
	Output_File.close();
	std::cout << path << " is outputted successfully!\n";
}

//This function will delete the previous content of the file and fill with new data!
void FileSystem::Overwrite_BinaryFile(const char* path, void* data, unsigned int size) {
	//ios::trunc is used to clear the file before outputting the data!
	std::ofstream Output_File(path, std::ios::binary | std::ios::out | std::ios::trunc);
	if (!Output_File.is_open()) {
		std::cout << "Error: " << path << " couldn't be outputted!\n";
		return;
	}

	if (data == nullptr) {
		std::cout << "data is nullptr!\n";
	}
	if (size == 0) {
		std::cout << "data size is 0!\n";
	}
	//Write to a file and finish all of the operation!
	Output_File.write((const char*)data, size);
	Output_File.close();
	std::cout << path << " is outputted successfully!\n";
	
}

void FileSystem::Delete_File(const char* path) {
	std::remove(path);
}


//There should be smart things, but I don't have time for that!
//Every imported resource will have ID that isn't used before!
unsigned int FileSystem::Create_Resource_ID() {
	SELF->LAST_ID += 1;
	return SELF->LAST_ID;
}


void FileSystem::Write_a_Resource_toDisk(Resource_Type* resource_data, bool Verify_ResourceData) {
	resource_data->ID = Create_Resource_ID();
	if (Verify_ResourceData) {
		if (!resource_data->Verify_Resource_Data()) {
			//There should be log!
			TuranAPI::Breakpoint(STL::String("While writing a resource to disk, the resource data isn't verified!\n", LASTUSEDALLOCATOR));
			return;
		}
	}

	//Model Proccess
	switch (resource_data->Get_Resource_Type()) {
	case TuranAPI_ENUMs::STATIC_MODEL_RESOURCE:
		std::cout << "Compiles a Static_Model Flatbuffer data!\n";
		Save_a_StaticModel_toDisk(resource_data);
		break;
	case TuranAPI_ENUMs::MATERIAL_TYPE_RESOURCE:
		std::cout << "Compiles a Material_Type Flatbuffer data!\n";
		Save_a_MaterialType_toDisk(resource_data);
		break;
	case TuranAPI_ENUMs::MATERIAL_INSTANCE_RESOURCE:
		std::cout << "Compiles a Material_Instance Flatbuffer data!\n";
		Save_a_MaterialInst_toDisk(resource_data);
		break;
	case TuranAPI_ENUMs::TEXTURE_RESOURCE:
		std::cout << "Compiles a Texture Flatbuffer data!\n";
		Save_a_Texture_toDisk(resource_data);
		break;
	case TuranAPI_ENUMs::FILE_LIST_RESOURCE:
		std::cout << "Compiles a FileList Flatbuffer data!\n";
		Save_a_FileList_toDisk(resource_data);
		break;
	case TuranAPI_ENUMs::SCENE_RESOURCE:
		std::cout << "Compiles a Scene Flatbuffer data!\n";
		Save_a_Scene_toDisk(resource_data);
		break;
	default:
		TuranAPI::Breakpoint("This data type can't be saved to disk!\n");
	}
}


unsigned int FileSystem::Get_LAST_ID() {
	return SELF->LAST_ID;
}


