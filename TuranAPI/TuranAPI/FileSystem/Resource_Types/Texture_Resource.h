#pragma once
#include "TuranAPI/API_includes.h"
#include "Resource_Type.h"

namespace TuranAPI {
	namespace File_System {
		struct TURANAPI Texture_Properties {
			TuranAPI_ENUMs DIMENSION = API_TEXTURE_2D, MIPMAP_FILTERING = API_TEXTURE_LINEAR_FROM_1MIP, WRAPPING = API_TEXTURE_REPEAT, CHANNEL_TYPE = API_TEXTURE_RGB, VALUE_TYPE = VAR_UBYTE8;
			Texture_Properties();
			Texture_Properties(TuranAPI_ENUMs dimension, TuranAPI_ENUMs mipmap_filtering = API_TEXTURE_LINEAR_FROM_1MIP, TuranAPI_ENUMs wrapping = API_TEXTURE_REPEAT, TuranAPI_ENUMs channel_type = API_TEXTURE_RGB, TuranAPI_ENUMs value_type = VAR_UBYTE8);
		};

		class TURANAPI Texture_Resource : public Resource_Type {
		public:
			static vector<Texture_Resource*> ALL_TEXTUREs;

			Texture_Properties Properties;
			int WIDTH, HEIGHT;
			unsigned char* DATA;
			unsigned int DATA_SIZE;
			//GL_ID is the ID of the texture in the GPU
			unsigned int GL_ID = 0;

			virtual TuranAPI::TuranAPI_ENUMs Get_Resource_Type();
			Texture_Resource();
		};
	}
}

