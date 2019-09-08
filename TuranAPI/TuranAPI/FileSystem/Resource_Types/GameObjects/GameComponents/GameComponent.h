#pragma once
#include "TuranAPI/API_includes.h"

//#include "TuranAPI/FileSystem/Resource_Types/Resource_Type.h"

namespace TuranAPI {
	namespace Game_Object {


		class TURANAPI GameComponent {
			//friend class GameObject;	This class is deactive for now!
		protected:
			vec3 POSITION, ROTATION, SCALE;
			//Is component's transform changed this frame? Default is true because application starts!
			bool is_TRANSFORM_CHANGED = true;

			GameComponent();
		public:
			string NAME;

			//Transport a component to a new position!
			void Translate(vec3 new_position);
			//Rotate a component to a new rotation!
			void Rotate(vec3 new_rotation);
			//Scale a component to a new rotation!
			void Scale(vec3 new_scale);
			virtual TuranAPI::TuranAPI_ENUMs Get_Component_Type() = 0;

			vec3 Get_Position();
			vec3 Get_Rotation();
			vec3 Get_Scale();
		};
	}
}