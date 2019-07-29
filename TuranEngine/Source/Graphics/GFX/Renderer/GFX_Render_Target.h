#pragma once
#include "Includes.h"

#include "Graphics/GFX/GFX_ENUMs.h"

//Create Render Targets as textures
class GFX_Render_Target {
private:
	friend class GFX_Draw_Pass; 
	friend class OGL3_Draw_Pass;
	friend class OGL3_SYS;
	friend class OGL3_Renderer;
	
	unsigned int ID;
	TEXTURE_DIMENSION DIMENSION;
	TEXTURE_FORMAT FORMAT;
	TEXTURE_ATTACHMENT ATTACHMENT;
	TEXTURE_FORMAT_VALUETYPE FORMAT_VALUETYPE;
};