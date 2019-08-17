#include "GFX_Texture.h"


vector<GFX_Texture*> GFX_Texture::ALL_TEXTUREs = vector<GFX_Texture*>();

GFX_Texture::GFX_Texture() {
	ALL_TEXTUREs.push_back(this);
}