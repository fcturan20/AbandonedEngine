#pragma once
#include "OpenGL3Source/OpenGL3_Includes.h"


class OGL3_API OGL3_Shader {
public:
	static void Compile_All_Shaders();
	static TuranAPI_ENUMs Find_Shader_Type(GFX_Shader* shader);


	//There is a Compile_All_Shaders(), don't forget it!
	//Compile a shader program
	//This class is used to compile a specific shader when a shader editing tool is used!
	//So, this is a feature for future
	//For now, all shaders will be compiled at once when application starts!
	static void Compile_Shader(GFX_Shader* shader);
};