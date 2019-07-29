#pragma once
#include "Includes.h"

#include "Engine/Scene/Scene_Core.h"

#include "GFX_Shader.h"

class GFXI_Draw_Resource {
	friend class GFX_Draw_Pass;
	//Code which parts of a mesh will be stored and how for each Draw Resource!
protected:
	Scene* SCENE;

	//Clean resources every frame!
	//Static resources shouldn't be cleaned in final product but I don't have time for that
	virtual void Clean_Resource() {

	}

	unsigned int Find_ShaderID_byName(string shader_name) {
		return GFX_Shader::Find_Shader_byName(shader_name)->PROGRAM_ID;
	}
};