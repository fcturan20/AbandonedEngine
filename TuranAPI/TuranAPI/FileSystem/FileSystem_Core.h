#pragma once
#include "TuranAPI/API_includes.h"

//Data Formats created by Flatbuffers!
#include <flatbuffers/flatbuffers.h>
#include "DataFormats/File_List_generated.h"
#include "DataFormats/GameResource_generated.h"

//Resource Types to present data in API!
#include "Resource_Types/Resource_Type.h"
#include "Resource_Types/Model_Resource.h"

/*
	1) This class is to add data types to Engine!
	2) An added data type should be type of .gamecont or .enginecont
*/
namespace TuranAPI {
	namespace File_System {

		/*
		Use this class instead of including Flatbuffers!
		*/
		class TURANAPI FileSystem {
		protected:
			//Don't use this, instantinating this class doesn't do anyting!
			FileSystem();

			static FileSystem* SELF;
			static unsigned int LAST_ID;
			static string GlobalFileList_PATH;

			static unsigned int Create_Resource_ID();
			static void* Read_BinaryFile(string path);
			static void Write_BinaryFile(string path, void* data, unsigned int size);
			static void Overwrite_BinaryFile(string path, void* data, unsigned int size);
		public:
			//Load the project!
			static void Start_FileSystem();

			static void Update_GlobalResourceList();
			static void Load_Resources(void* globalfilelist_data);



			//Add resource types here!
			//And these functions will be defined in Resource_Loaders folder!

			static void Load_Model(void* data, unsigned int id);
			static void Load_Material_Type(void* data, unsigned int id);
		};
	}
}
