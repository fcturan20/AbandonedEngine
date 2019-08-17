#pragma once
#include "OpenGL3Source/OpenGL3_Includes.h"

#include "OGL3_Shader.h"

//This class is to send uniforms to shader with GFX API specific way! I mean, this class handles OpenGL3 calls to send uniforms
class OGL3_API OGL3_Material {
private:
	static void Bind_Uniform(GFX_Material* material, unsigned int uniform_list_index);
public:
	static void Bind_Material(GFX_Material* material);
};
