#pragma once
#include "GFXSource/GFX_Includes.h"

//Create Render Targets as textures
class GFXAPI GFX_Render_Target {
private:
	friend class GFX_Draw_Pass; 
	friend class OGL3_Draw_Pass;
	friend class OGL3_SYS;
	friend class OGL3_Renderer;
	
	unsigned int ID;
	GFX_ENUM DIMENSION;
	GFX_ENUM FORMAT;
	GFX_ENUM ATTACHMENT;
	GFX_ENUM FORMAT_VALUETYPE;
};