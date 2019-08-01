#pragma once
#include "Includes.h"

#include "GFX_Shader_Resource.h"

/* You can create a GFX_Shader, but you have to define shader's source code in disk and have to define its GFX API!

*/
class GFX_Shader {
protected:
	friend class OGL3_Shader;
	friend class GFXI_Draw_Resource;

	static vector<GFX_Shader*> ALL_SHADERs;
	GFX_Shader_Resource* RESOURCEs;
	string VERTEX_SOURCE, FRAGMENT_SOURCE;
	string VERTEX_DISK_PATH, FRAGMENT_DISK_PATH;
	string NAME;
	GFX_ENUM TYPE;
	bool Is_Compiled = false;

	//IDs of Shader Stages!
	unsigned int VERTEX_ID, FRAGMENT_ID, PROGRAM_ID;

	//Read the Shader Code File and Convert it to a String
	static string ReadShader(const string &shaderPath_string);

public:
	GFX_Shader(string name, GFX_ENUM type, string vertex_shader_path, string fragment_shader_path)
		: NAME(name) {
		VERTEX_SOURCE = ReadShader(vertex_shader_path);
		FRAGMENT_SOURCE = ReadShader(fragment_shader_path);

		VERTEX_DISK_PATH = vertex_shader_path;
		FRAGMENT_DISK_PATH = fragment_shader_path;
		if (type == OPENGL_3) {
			TYPE = OPENGL_3;
		}
		ALL_SHADERs.push_back(this);
	}

	//Global Functions to find Shaders!
	static GFX_Shader* Find_Shader_byName(string name) {
		for (GFX_Shader* shader : ALL_SHADERs) {
			if (shader->NAME == name) {
				return shader;
			}
		}

		cout << "Error: Intended shader isn't found! Name: " << name << endl;
		return nullptr;
	}

	unsigned int Return_Shader_ID() {
		return PROGRAM_ID;
	}

	string Return_Name() {
		return NAME;
	}
};

vector<GFX_Shader*> GFX_Shader::ALL_SHADERs = vector<GFX_Shader*>();

string GFX_Shader::ReadShader(const string &shaderPath_string) {
	const char* shaderPath = shaderPath_string.c_str();
	ifstream shaderFile;
	shaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);
		stringstream shaderFile_stream;
		shaderFile_stream << shaderFile.rdbuf();
		shaderFile.close();
		return shaderFile_stream.str();
	}
	catch (ifstream::failure error)
	{
		cout << "Error: Shader file couldn't read: " << shaderPath_string << endl;
		return "Error";
	}
}

GFX_Shader Surface_Shader("Surface_Shader", OPENGL_3, "Source/Graphics/OPENGL3/Shaders/Main.vert", "Source/Graphics/OPENGL3/Shaders/Main.frag");
GFX_Shader PostProcess_Shader("PostProcess_Shader", OPENGL_3, "Source/Graphics/OPENGL3/Shaders/Post_Process.vert", "Source/Graphics/OPENGL3/Shaders/Post_Process.frag");