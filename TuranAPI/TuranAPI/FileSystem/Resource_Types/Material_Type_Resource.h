#pragma once
#include "Resource_Type.h"

namespace TuranAPI {
	namespace File_System {
		//A Material_Type is an Shader Pipeline Stage (Vertex and Fragment for now!)!
		class Material_Type_Resource : public Resource_Type {
			//Only store paths, because we want to play with shader's source text!
			string VERTEX_SOURCE_PATH, FRAGMENT_SOURCE_PATH;
		};
	}
}
