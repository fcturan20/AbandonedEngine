#include "FileList_Resource.h"

using namespace TuranAPI::File_System;

FileList_Resource::FileList_Resource(const String& path) : ContentListVector(LASTUSEDALLOCATOR, 4, 4){
	PATH = path;
	String* name = (path.substr(path.find_lastof('/') + 1, path.find_lastof('.')));
	NAME = *name;
	delete name;
}

TuranAPI::TuranAPI_ENUMs FileList_Resource::Get_Resource_Type() {
	return TuranAPI::TuranAPI_ENUMs::FILE_LIST_RESOURCE;
}

Vector<Resource_Type*>* FileList_Resource::Get_ContentListVector() {
	return &ContentListVector;
}

bool FileList_Resource::Verify_Resource_Data() {
	if (NAME != "" && PATH != "") {
		for (size_t i = 0; i < ContentListVector.size(); i++) {
			Resource_Type* Resource = ContentListVector[i];
			if (!Resource->Verify_Resource_Data()) {
				TuranAPI::Breakpoint("File List Resource isn't verified because a Resource isn't verified!\n");
				return false;
			}
		}
	}
	else {
		TuranAPI::Breakpoint("File List Resource isn't verified because it has invalid Name or Path!\n" +
			String("Name: ") + NAME + String("\nPath: ") + PATH + String("\n"));
		return false;
	}
	return true;
}