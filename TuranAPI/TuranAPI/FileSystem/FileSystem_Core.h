#pragma once
#include "TuranAPI/API_includes.h"

//Resource Types to present data in API!
#include "Resource_Types/Resource_Type.h"
#include "Resource_Types/Material_Type_Resource.h"
#include "Resource_Types/FileList_Resource.h"

/*
	1) This class is to add data types to Engine!
	2) An added data type should be type of .gamecont or .enginecont
*/
namespace TuranAPI {
	namespace File_System {

		/*
		Handles all of the Resource I/O operations!
		If you want to add a data format, or write/read a file, modify this class!
		*/
		class TURANAPI FileSystem {
		protected:
			static unsigned int LAST_ID;


		public:
			//Create resource ID for new imported (compiled) resources!
			static unsigned int Create_Resource_ID();

			static void* Read_BinaryFile(string path, unsigned int& size);
			static void Write_BinaryFile(string path, void* data, unsigned int size);
			static void Overwrite_BinaryFile(string path, void* data, unsigned int size);
			static void Delete_File(string path);


			//Read text file!
			static string Read_TextFile(string path);

			//Add resource types here!
			//These functions will be defined in Resource_Loaders folder!
			//These functions load compiled resources to memory

			static Resource_Type* Load_Model(void* data, unsigned int id, const string& path);
			static Resource_Type* Load_Material_Type(void* data, unsigned int id, const string& path);
			static Resource_Type* Load_Material_Inst(void* data, unsigned int id, const string& path);
			static Resource_Type* Load_Texture(void* data, unsigned int id, const string& path);
			static Resource_Type* Load_Scene(void* data, unsigned int id, const string& path);



			static unsigned int Get_LAST_ID();

			//Save a resource to disk! Any type is possible (GFX_Default, Engine_Default, User etc.)
			//Don't forget to update your resource list (if you have one)!
			static void Write_a_Resource_toDisk(Resource_Type* resource_data);

			//Load resources from a FileList to a vector!
			static void Load_Resources_fromFileList(FileList_Resource* Empty_File_List);


			static Material_Instance* Create_Instance_ofMaterialType(Material_Type_Resource* material_type, const string& output_path);
		};
	}
}
