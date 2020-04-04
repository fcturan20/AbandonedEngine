#include "GFX_FileSystem.h"

using namespace TuranAPI::File_System;

namespace GFX_API {




	/*
	TuranAPI::File_System::FileList_Resource* GFX_FileSystem::Get_GFXContentList() {
		return &SELF->GFXContentList_onDisk;
	}

	TuranAPI::File_System::Resource_Type* GFX_FileSystem::Get_GFXContent_byName(const char* NAME) {
		for (std::size_t i = 0; i < SELF->GFXContentList_onDisk.Get_ContentListVector()->size(); i++) {
			Resource_Type* RESOURCE = (*SELF->GFXContentList_onDisk.Get_ContentListVector())[i];
			if (RESOURCE->NAME == NAME) {
				return RESOURCE;
			}
		}
	}

	TuranAPI::File_System::Resource_Type* GFX_FileSystem::Get_GFXContent_byID(unsigned int ID) {
		for (std::size_t i = 0; i < SELF->GFXContentList_onDisk.Get_ContentListVector()->size(); i++) {
			Resource_Type* RESOURCE = (*SELF->GFXContentList_onDisk.Get_ContentListVector())[i];
			if (RESOURCE->ID == ID) {
				return RESOURCE;
			}
		}
	}

	void GFX_FileSystem::Add_Content_toFileList(TuranAPI::File_System::Resource_Type* Resource) {
		//TuranAPI::LOG_STATUS("Adding a GFX Content to List! Name: " + Resource->NAME + " ID: " + to_string(Resource->ID) + " PATH: " + Resource->PATH);
		GFXContentList_onDisk.Get_ContentListVector()->push_back(Resource);
		FileSystem::Write_a_Resource_toDisk(&GFXContentList_onDisk);
		FileSystem::Write_a_Resource_toDisk(Resource);
		TuranAPI::LOG_STATUS("Added the GFX Content to List successfully!");
	}

	void GFX_FileSystem::Remove_Content_fromFileList(unsigned int index) {
		//TuranAPI::LOG_STATUS("Removing a GFX Content from the List! List Index: " + to_string(index));

		Resource_Type* Resource = ((*GFXContentList_onDisk.Get_ContentListVector())[index]);

		FileSystem::Delete_File(Resource->PATH);
		//Clear all of the loaded resources from the memory
		delete Resource;
		Resource = nullptr;
		GFXContentList_onDisk.Get_ContentListVector()->erase(index);
		Write_a_Resource_toDisk(&GFXContentList_onDisk, true);

		TuranAPI::LOG_STATUS("Removed the GFX Content from the List successfully!");
	}

	const Vector<TuranAPI::File_System::Resource_Type*>* GFX_FileSystem::Get_Const_FileListContentVector() {
		return GFXContentList_onDisk.Get_ContentListVector();
	}

	unsigned int GFX_FileSystem::Get_LengthOf_FileListContentVector() {
		return GFXContentList_onDisk.Get_ContentListVector()->size();
	}

	void GFX_FileSystem::Load_FileListContents_fromDisk() {
		TuranAPI::LOG_STATUS("Started to load GFX Contents!");
		TuranAPI::File_System::FileSystem::Load_Resources_fromFileList(&GFXContentList_onDisk);
		TuranAPI::LOG_STATUS("Finished loading GFX Contents!");
	}

	void GFX_FileSystem::Clear_FileListContents() {
		TuranAPI::LOG_STATUS("Clearing the GFX Contents!");

		for (std::size_t i = 0; i < GFXContentList_onDisk.Get_ContentListVector()->size(); i++) {
			Resource_Type* RESOURCE = (*GFXContentList_onDisk.Get_ContentListVector())[i];
			const char* PATH = RESOURCE->PATH;

			FileSystem::Delete_File(PATH);
			//Clear all of the loaded resources from the memory
			delete RESOURCE;
			RESOURCE = nullptr;
		}
		//Clear all of the loaded resource references!
		GFXContentList_onDisk.Get_ContentListVector()->clear();

		FileSystem::Write_a_Resource_toDisk(&GFXContentList_onDisk);
		TuranAPI::LOG_STATUS("Cleared the GFX Contents!");
	}*/
}