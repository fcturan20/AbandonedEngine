#pragma once
#include "GFX_Includes.h"
#include "TuranAPI/FileSystem/Resource_Types/Resource_Type.h"
#include "TuranAPI/FileSystem/Resource_Types/FileList_Resource.h"



namespace GFX_API {
	//This class will be Interface for GL specific FileSystems (Vulkan_FileSystem etc)
	//Derived classes should provide functions for loading material types etc
	class GFXAPI GFX_FileSystem : public TuranAPI::File_System::FileSystem {
	public:
		virtual void Add_Content_toFileList(TuranAPI::File_System::Resource_Type* Resource) = 0;
		virtual void Remove_Content_fromFileList(unsigned int index) = 0;
		virtual const Vector<TuranAPI::File_System::Resource_Type*>* Get_Const_FileListContentVector() = 0;
		virtual unsigned int Get_LengthOf_FileListContentVector() = 0;

		//Read File_List.usercont to load the project!
		virtual void Load_FileListContents_fromDisk() = 0;
		//Clear all of the resource list! But resource files (.gfxcont) aren't deleted.
		virtual void Clear_FileListContents() = 0;
	};
#define GFX_FILESYSTEM GFX_FileSystem::SELF
}