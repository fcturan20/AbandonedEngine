#pragma once
#include "TuranAPI/API_includes.h"

#include "TuranAPI/FileSystem/DataFormats/File_List_generated.h"

namespace TuranAPI {
	namespace File_System {

		//Each valid resource file has this structure, we will use this to identify the resource!
		struct TURANAPI Resource_File {
			string PATH;
			Editor::FileList::File_Type TYPE;
			unsigned int ID;
			//Store all of the resources!
			static vector<Resource_File*> ALL_RESOURCEs;
			Resource_File(string path, Editor::FileList::File_Type type, unsigned int id);
		};


		//Each resource is inherited from this!
		//So, ID is meant to each resource!
		class TURANAPI Resource_Type
		{
			unsigned int ID;
			Editor::FileList::File_Type TYPE;
			static vector<Resource_Type*> ALL_RESOURCEs;
		public:
			unsigned int Get_ID();
			static Resource_Type* Get_Resource_byID(unsigned int id);
		};
	}
}