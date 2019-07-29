#pragma once
#include "Includes.h"

#include "GFX_Shader_Resource.h"

class GFX_Shader {
protected:
	//I don't know why, but OGL3_Shader can't access a GFX_Shader object's protected member, so I made it friend!
	friend class OGL3_Shader;
	friend class GFXI_Draw_Resource;

	static vector<GFX_Shader*> ALL_SHADERs;
	GFX_Shader_Resource* RESOURCEs;
	string VERTEX_SOURCE, FRAGMENT_SOURCE;
	string NAME;

	//IDs of Shader Stages!
	unsigned int VERTEX_ID, FRAGMENT_ID, PROGRAM_ID;

	//Read the Shader Code File and Convert it to a String
	string ReadShader(const string &shaderPath_string);

public:
	GFX_Shader(string name, string vertex_shader_path, string fragment_shader_path)
		: NAME(name) {
		VERTEX_SOURCE = ReadShader(vertex_shader_path);
		FRAGMENT_SOURCE = ReadShader(fragment_shader_path);
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