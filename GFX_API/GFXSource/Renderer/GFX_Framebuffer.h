#pragma once
#include "GFXSource/GFX_Includes.h"

#include "GFX_Render_Target.h"

//This is a storage struct that has no functions
//Changing this doesn't affect the actual framebuffer until one of member variables is used!
//Because of that, a framebuffer should only created by a Draw Pass
//Please don't change any object by yourself, GFX has enough functions to change framebuffers
//If you are creating your own render pipeline or whatsoever, you can use this storage class because GFX doesn't store all objects of this class
//Only Draw Passes has framebuffers and Windows has their own by default because of OpenGL3 drivers!
struct GFXAPI GFX_Framebuffer {
public:

	unsigned int ID;
	vector<GFX_Render_Target*> BOUND_RTs;

	unsigned int MSAA_spp;
	unsigned int WIDTH, HEIGHT;
	GFX_Framebuffer(unsigned int width, unsigned int height);
};