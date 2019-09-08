#include "GFX_FileSystem.h"

using namespace TuranAPI::File_System;
static string GFXContentList_PATH = "C:/dev/TuranEngine/OpenGL3/GFX_ContentsList.gfxcont";

TuranAPI::File_System::FileList_Resource GFX_FileSystem::GFXContentList_onDisk(GFXContentList_PATH);

TuranAPI::File_System::FileList_Resource* GFX_FileSystem::Get_GFXContentList() {
	return &GFXContentList_onDisk;
}

TuranAPI::File_System::Resource_Type* GFX_FileSystem::Get_GFXContent_byName(string NAME) {
	for (Resource_Type* RESOURCE : *GFXContentList_onDisk.Get_ContentListVector()) {
		if (RESOURCE->NAME == NAME) {
			return RESOURCE;
		}
	}
}

TuranAPI::File_System::Resource_Type* GFX_FileSystem::Get_GFXContent_byID(unsigned int ID) {
	for (Resource_Type* RESOURCE : *GFXContentList_onDisk.Get_ContentListVector()) {
		if (RESOURCE->ID == ID) {
			return RESOURCE;
		}
	}
}
