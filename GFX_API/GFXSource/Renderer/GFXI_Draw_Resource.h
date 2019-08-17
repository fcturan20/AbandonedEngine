#pragma once
#include "GFXSource/GFX_Includes.h"

#include "GFX_Shader.h"

class GFXAPI GFXI_Draw_Resource {
	friend class GFX_Draw_Pass;
	//Code which parts of a mesh will be stored and how for each Draw Resource!
protected:

	//Clean resources every frame!
	//Static resources shouldn't be cleaned in final product but I don't have time for that
	virtual void Clean_Resource();

	unsigned int Find_ShaderID_byName(string shader_name);
};