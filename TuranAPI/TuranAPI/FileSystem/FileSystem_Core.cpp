#include "FileSystem_Core.h"

using namespace TuranAPI::File_System;
FileSystem* FileSystem::SELF;
unsigned int FileSystem::LAST_ID;
string FileSystem::GlobalFileList_PATH = "File_List.enginecont";
//Don't use this, instantinating this class doesn't do anyting!
FileSystem::FileSystem(){}


//FileList namespace
using namespace Editor;

//Read File_List.enginecont to load the project!
void FileSystem::Start_FileSystem() {
	void* File_List_Data = nullptr;
	unsigned int data_size;
	File_List_Data = Read_BinaryFile(GlobalFileList_PATH);

	//If File_List.enginecont isn't found, require user to give the correct path until he gives an available File_List.bin path!
	while (File_List_Data == nullptr) {
		cout << "File_List.enginecont couldn't be found, please enter the location:";
		GlobalFileList_PATH = "";
		cin >> GlobalFileList_PATH;
		File_List_Data = Read_BinaryFile(GlobalFileList_PATH);
	}
}

//If read fails, data_ptr is set to nullptr!
void* FileSystem::Read_BinaryFile(string path) {
	std::ifstream Binary_File;
	Binary_File.open(path, ios::binary | ios::in);
	if (!(Binary_File.is_open())) {
		cout << "There is no such file: " << path << endl;
		return nullptr;
	}

	Binary_File.seekg(0, ios::end);
	int length = Binary_File.tellg();
	Binary_File.seekg(0, ios::beg);
	char* read_data = new char[length];
	Binary_File.read(read_data, length);
	Binary_File.close();
	return read_data;
}

//Use only for creating new binary files! 
//If you want to overwrite to a file, Overwrite_BinaryFile is available!
void FileSystem::Write_BinaryFile(string path, void* data, unsigned int size) {
	//Try to create to a file (Check if the operation fails)
	std::ofstream Output_File(path, ios::binary | ios::out);
	if (!Output_File.is_open()) {
		cout << "Error: " << path << " couldn't be outputted!\n";
		return;
	}

	//Write to a file and finish all of the operation!
	Output_File.write((const char*)data, size);
	Output_File.close();
	cout << path << " is outputted successfully!\n";
}

//This function will delete the previous content of the file and fill with new data!
void FileSystem::Overwrite_BinaryFile(string path, void* data, unsigned int size) {
	//ios::trunc is used to clear the file before outputting the data!
	std::ofstream Output_File(path, ios::binary | ios::out | ios::trunc);
	if (!Output_File.is_open()) {
		cout << "Error: " << path << " couldn't be outputted!\n";
		return;
	}

	//Write to a file and finish all of the operation!
	Output_File.write((const char*)data, size);
	Output_File.close();
	cout << path << " is outputted successfully!\n";
}

void FileSystem::Load_Resources(void* filelist_data) {
	auto File_List = FileList::GetFileList(filelist_data);
	auto File_Vector = File_List->FILE_LIST();
	LAST_ID = File_List->LAST_ID();

	//For each file that is in File_List.enginecont!
	for (unsigned int i = 0; i < File_Vector->Length(); i++) {
		auto FILE = File_Vector->Get(i);
		const char* PATH = FILE->PATH()->c_str();
		auto TYPE = FILE->TYPE();
		auto ID = FILE->ID();

		void* data = nullptr;
		data = Read_BinaryFile(PATH);

		//If compiled resource isn't found!
		if (data == nullptr) {
			cout << "Resource isn't found in path: " << PATH << endl;
			continue;
		}


		Resource_File* file = new Resource_File(PATH, TYPE, ID);


		//Create Scene* here, because Scene* should be created at last
		//If the resource is valid!
		switch (TYPE) {
		case FileList::File_Type_Static_Model:
			Load_Model(data, ID);

			//Add here a call to Mesh_Loader!
			break;
		case FileList::File_Type_Scene:
			cout << "There is a scene!\n";

			//Initialize the Scene* pointer that is defined above!
		}
	}

	auto NANOSUIT_FILE = File_Vector->Get(0);
	cout << "First File's path is: " << NANOSUIT_FILE->PATH()->c_str() << endl;
}


void FileSystem::Update_GlobalResourceList() {
	cout << "Submitting the changes of Resource File class to disk!\n";
	cout << "This means, new important resources is being saved to File_List.enginecont!\n";

	//Create a flatbufferbuilder and FileList to build the data!
	flatbuffers::FlatBufferBuilder builder(1024);
	FileList::FileListBuilder file_list_builder(builder);

	//Read each Resource_File struct and create a File struct for each of them!
	//Store each created File struct in a vector to set FileList's vector!
	vector<flatbuffers::Offset<Editor::FileList::File>> resources;
	for (Resource_File* RESOURCE : Resource_File::ALL_RESOURCEs) {
		FileList::FileBuilder file_build(builder);
		file_build.add_PATH(builder.CreateString(RESOURCE->PATH));
		file_build.add_TYPE(RESOURCE->TYPE);
		file_build.add_ID(RESOURCE->ID);
		auto finished_file = file_build.Finish();
		resources.push_back(finished_file);
	}
	auto finished_vector = builder.CreateVector(resources);

	//Create, initialize and finish editing the File_List!
	file_list_builder.add_FILE_LIST(finished_vector);
	file_list_builder.add_LAST_ID(LAST_ID);
	auto finished_file_list = file_list_builder.Finish();
	builder.Finish(finished_file_list);

	//Get data pointer and data size from builder!
	void* data = builder.GetBufferPointer();
	unsigned int data_size = builder.GetSize();

	//Overwrite the File_List with new File_List!
	Overwrite_BinaryFile(GlobalFileList_PATH, data, data_size);
}

//There should be smart things, but I don't have time for that!
//Every imported resource will have ID that isn't used before!
unsigned int FileSystem::Create_Resource_ID() {
	return LAST_ID + 1;
}