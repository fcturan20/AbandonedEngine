#pragma once
#include "GFXSource/GFX_Includes.h"

class GFXAPI GFX_Texture {
	friend class OGL3_Texture;
	friend class Model_Loader;

	static vector<GFX_Texture*> ALL_TEXTUREs;

	const char* PATH;
	unsigned char* DATA;
	int WIDTH, HEIGHT;


	unsigned int ID;
	GFX_ENUM DIMENSION;
	GFX_ENUM FORMAT_VALUETYPE;
	GFX_ENUM MIPMAP_FILTERING;
	GFX_ENUM WRAPPING;
	GFX_ENUM CHANNEL_TYPE;

	GFX_Texture();
};
