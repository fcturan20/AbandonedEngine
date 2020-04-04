#pragma once
#include "TuranAPI/API_includes.h"
#include "Resource_Type.h"
#include "Model_Resource.h"

namespace TuranAPI {
	namespace File_System {

		struct TURANAPI Material_Uniform {
			String VARIABLE_NAME = ("");
			TuranAPI_ENUMs VARIABLE_TYPE;
			void* DATA = nullptr;
			Material_Uniform(const char* variable_name, TuranAPI_ENUMs variable_type);
			bool Verify_UniformData();
			Material_Uniform();
		};



		class TURANAPI Material_Type_Resource : public Resource_Type {
		public:
			virtual TuranAPI::TuranAPI_ENUMs Get_Resource_Type();
			virtual bool Verify_Resource_Data();

			Vector<Material_Type_Resource*> ALL_MATERIALTYPEs;

			Material_Type_Resource();

			//The GFX_API, Vertex and Fragment sources are written with.
			TuranAPI_ENUMs GFX_API;
			String VERTEX_SOURCE, FRAGMENT_SOURCE;
			Vector<TuranAPI::File_System::Material_Uniform> UNIFORMs;
		};





		//Don't forget, data handling for each uniform type is the responsibility of the user!
		class TURANAPI Material_Instance : public Resource_Type {
		public:
			Vector<Material_Instance*> ALL_MATERIALINSTs;
			static Material_Instance* Find_MaterialInst_byID(unsigned int ID);

			Material_Instance();

			Material_Type_Resource* Material_Type;

			//Uniforms won't change at run-time because we are defining uniforms at compile-time, but it is an easier syntax for now!
			//This list will be defined per material type (for example: Surface_PBR, Surface_Phong, Texture View etc.)
			Vector<Material_Uniform> UNIFORM_LIST;

			virtual TuranAPI_ENUMs Get_Resource_Type();
			virtual bool Verify_Resource_Data();
			unsigned int Find_Uniform_byName(const char* uniform_name);
		public:
			void Set_Uniform_Data(const char* uniform_name, void* pointer_to_data);
		};
	}
}
