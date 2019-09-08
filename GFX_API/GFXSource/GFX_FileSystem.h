#pragma once
#include "GFX_Includes.h"
#include "TuranAPI/FileSystem/Resource_Types/Resource_Type.h"
#include "TuranAPI/FileSystem/Resource_Types/FileList_Resource.h"

class GFXAPI GFX_FileSystem {
protected:
	static TuranAPI::File_System::FileList_Resource GFXContentList_onDisk;
public:
	virtual void Load_GFX_Contents_fromDisk() = 0;
	virtual void Clear_All_GFXContents() = 0;

	//GETTER-SETTERs
	static TuranAPI::File_System::Resource_Type* Get_GFXContent_byName(string NAME);
	static TuranAPI::File_System::Resource_Type* Get_GFXContent_byID(unsigned int ID);
	static TuranAPI::File_System::FileList_Resource* Get_GFXContentList();
};

