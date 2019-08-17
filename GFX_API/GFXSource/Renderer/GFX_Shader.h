#pragma once
#include "GFXSource/GFX_Includes.h"

#include "GFX_Shader_Resource.h"

/* You can create a GFX_Shader, but you have to define shader's source code in disk and have to define its GFX API!

*/
class GFXAPI GFX_Shader {
protected:
	friend class OGL3_Shader;
	friend class GFXI_Draw_Resource;

	static vector<GFX_Shader*> ALL_SHADERs;
	GFX_Shader_Resource* RESOURCEs;
	string VERTEX_SOURCE, FRAGMENT_SOURCE;
	string VERTEX_DISK_PATH, FRAGMENT_DISK_PATH;
	string NAME;
	TuranAPI_ENUMs TYPE;
	bool Is_Compiled = false;

	//IDs of Shader Stages!
	unsigned int VERTEX_ID, FRAGMENT_ID, PROGRAM_ID;

	//Read the Shader Code File and Convert it to a String
	static string ReadShader(const string &shaderPath_string);

public:
	GFX_Shader(string name, TuranAPI_ENUMs gfx_api_type, string vertex_shader_path, string fragment_shader_path);

	//Global Functions to find Shaders!
	static GFX_Shader* Find_Shader_byName(string name);

	unsigned int Return_Shader_ID();

	string Return_Name();
};
