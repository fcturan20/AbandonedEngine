#include "Resource_Type.h"
using namespace TuranAPI::File_System;

vector<Resource_File*> Resource_File::ALL_RESOURCEs = vector<Resource_File*>();

Resource_File::Resource_File(string path, Editor::FileList::File_Type type, unsigned int id) : PATH(path), TYPE(type), ID(id) {
	ALL_RESOURCEs.push_back(this);
}



unsigned int Resource_Type::Get_ID() {
	return ID;
}

vector<Resource_Type*> Resource_Type::ALL_RESOURCEs = vector<Resource_Type*>();

Resource_Type* Resource_Type::Get_Resource_byID(unsigned int id) {
	for (Resource_Type* RESOURCE : ALL_RESOURCEs) {
		if (RESOURCE->ID == id) {
			return RESOURCE;
		}
	}
	cout << "Error: Intended Resource isn't found by ID: " << id << "! So, nullptr has returned!\n";
	return nullptr;
}