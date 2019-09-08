#pragma once
#include "TuranAPI/API_includes.h"
#include "GameComponent.h"

#include "TuranAPI/FileSystem/Resource_Types/Model_Resource.h"
#include "TuranAPI/FileSystem/Resource_Types/Material_Type_Resource.h"

namespace TuranAPI {
	namespace Game_Object {

		/* There are some abstractions and lacks in this class, here is some definitions:
		1) In a model, each part that has different material index is created as a mesh according to .obj file!
		2) So, each model consists of meshes!
		3) This means you would specify each mesh's shader in this class, but I don't want to complicate this anymore!
		4) So, for now, each mesh of the model uses the same material/shader and each model has one material/shader!
		5) There is no difference between the terms "material" and "shader", because there isn't a material system in engine!
		*/
		class TURANAPI StaticModel_Component : public GameComponent {
		public:
			mat4 Model_Transform;
			TuranAPI::File_System::Static_Model_Data* MODEL;
			vector<TuranAPI::File_System::Material_Instance*> MATERIALs;

			StaticModel_Component(TuranAPI::File_System::Static_Model_Data* model);
			virtual TuranAPI::TuranAPI_ENUMs Get_Component_Type() override;
		};
	}
}
