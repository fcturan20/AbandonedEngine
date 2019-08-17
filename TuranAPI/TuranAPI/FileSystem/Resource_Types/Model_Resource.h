#pragma once
#include "TuranAPI/API_includes.h"

#include "Resource_Type.h"

namespace TuranAPI {
	namespace File_System {
		//Non-animated mesh data!
		//Stores vertex attribute pointers!
		struct TURANAPI Static_Mesh_Data {
		private:
			vec3* POSITIONs = nullptr, * NORMALs = nullptr, * TANGENTs = nullptr, * BITANGENTs = nullptr;
			unsigned int* INDICEs = nullptr;
			vec2* TEXTCOORDs = nullptr;
			int VERTEX_NUMBER = 0, INDICEs_LENGTH = 0;
		public:
			~Static_Mesh_Data() {
				delete[] POSITIONs;
				delete[] NORMALs;
				delete[] TEXTCOORDs;
				delete[] TANGENTs;
				delete[] BITANGENTs;
			}

			vec3* Get_Positions();
			unsigned int* Get_Indices();
			vec3* Get_Normals();
			vec2* Get_TextCoords();
			vec3* Get_Tangents();
			vec3* Get_Bitangents();
			int Get_Vertex_Number();
			int Get_Indice_Number();
		};

		//Non-animated model data!
		//Stores only pointers for the contained Meshes' vertex attribute datas!
		struct TURANAPI Static_Model_Data : public Resource_Type {
			//Meshes will be stored as pointers in an array, so point to that "Pointer Array"
			Static_Mesh_Data** MESH_ARRAY_PTR;
			unsigned int MESH_NUMBER;
			//Model's ID that is stored in .gamecont!
			unsigned int ID;

			//If a pointer uses model_data pointer, when this deleted, set its pointer to nullptr
			//This pointer-to-pointer is used for this purpose!
			void** POINTER_TO_MODELPOINTER;

			static vector<Static_Model_Data*> ALL_MODEL_DATAs;
			Static_Model_Data(Static_Mesh_Data** mesh_array, unsigned int mesh_number, unsigned int id);
		};
	}
}