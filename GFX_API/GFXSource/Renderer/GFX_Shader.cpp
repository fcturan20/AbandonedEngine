#include "GFX_Shader.h"

vector<GFX_Shader*> GFX_Shader::ALL_SHADERs = vector<GFX_Shader*>();


string GFX_Shader::ReadShader(const string& shaderPath_string) {
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


GFX_Shader::GFX_Shader(string name, TuranAPI_ENUMs gfx_api_type, string vertex_shader_path, string fragment_shader_path)
	: NAME(name) {
	VERTEX_SOURCE = ReadShader(vertex_shader_path);
	FRAGMENT_SOURCE = ReadShader(fragment_shader_path);

	VERTEX_DISK_PATH = vertex_shader_path;
	FRAGMENT_DISK_PATH = fragment_shader_path;
	if (gfx_api_type == OPENGL3) {
		TYPE = OPENGL3;
	}
	ALL_SHADERs.push_back(this);
}

//Global Functions to find Shaders!
GFX_Shader* GFX_Shader::Find_Shader_byName(string name) {
	for (GFX_Shader* shader : ALL_SHADERs) {
		if (shader->NAME == name) {
			return shader;
		}
	}

	cout << "Error: Intended shader isn't found! Name: " << name << endl;
	return nullptr;
}

unsigned int GFX_Shader::Return_Shader_ID() {
	return PROGRAM_ID;
}

string GFX_Shader::Return_Name() {
	return NAME;
}