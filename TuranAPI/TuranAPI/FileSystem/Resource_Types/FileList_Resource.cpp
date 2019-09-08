#include "FileList_Resource.h"

using namespace TuranAPI::File_System;

FileList_Resource::FileList_Resource(const string& path) {
	PATH = path;
	NAME = path.substr(path.find_last_of('/') + 1, path.size());
	NAME = path.substr(0, path.find_last_of('.'));
}

TuranAPI::TuranAPI_ENUMs FileList_Resource::Get_Resource_Type() {
	return TuranAPI::FILE_LIST_RESOURCE;
}

vector<Resource_Type*>* FileList_Resource::Get_ContentListVector() {
	return &All_Resources;
}