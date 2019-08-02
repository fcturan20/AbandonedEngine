#pragma once
#include "Includes.h"

#include "Graphics/GFX/GFX_ENUMs.h"

class GFX_Texture {
	friend class OGL3_Texture;
	friend class Mesh_Loader;

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

	GFX_Texture() {
		ALL_TEXTUREs.push_back(this);
	}
};

vector<GFX_Texture*> GFX_Texture::ALL_TEXTUREs = vector<GFX_Texture*>();