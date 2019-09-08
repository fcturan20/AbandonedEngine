#pragma once
#include "EngineSource/TuranEngine.h"
#include "TuranAPI/API_FileSystem.h"

/*
1) This namespace is defined in Engine
2) But extended in Editor to handle Editor specific files too!
*/
namespace Editor {
	namespace File_System {
		/*
		1) This class is used to load the project's editor datas;
		2) You can specify how to create and load new data types here!
		3) If project's File_List.bin isn't found, gives error to either specify the location or create a new project!
		*/
		class Editor_FileSystem {
			static TuranAPI::File_System::FileList_Resource GameContentList_onDisk;
		public:
			static void Start_EditorFileSystem();

			//Read File_List.usercont to load the project!
			static void Load_GameContents_fromDisk();

			//Clear all of the resource list! But resource files (.gamecont) aren't deleted.
			static void Clear_GlobalGameContentList();

			
			static TuranAPI::File_System::Material_Instance* Create_Instance_ofMaterialType(TuranAPI::File_System::Material_Type_Resource* material_type);

			//GETTER-SETTERs
			static TuranAPI::File_System::Resource_Type* Get_GameContent_byName(string NAME);
			static TuranAPI::File_System::Resource_Type* Get_GameContent_byID(unsigned int ID);
			static TuranAPI::File_System::FileList_Resource* Get_GameContentList();
		};
	}
}