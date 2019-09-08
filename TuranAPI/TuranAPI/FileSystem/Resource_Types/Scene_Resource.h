#pragma once
#include "TuranAPI/API_includes.h"
#include "Resource_Type.h"
#include "GameObjects/GameComponents/GameComponent.h"

namespace TuranAPI {
	namespace File_System {



		class TURANAPI Scene_Resource : public TuranAPI::File_System::Resource_Type {
		public:
			virtual TuranAPI::TuranAPI_ENUMs Get_Resource_Type();
			vector<Game_Object::GameComponent*> ADDED_COMPONENTs;

			static Scene_Resource* SCENE;
		};
	}
}