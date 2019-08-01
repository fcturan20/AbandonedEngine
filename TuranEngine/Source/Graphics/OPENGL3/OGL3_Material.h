#pragma once
#include "Includes.h"

#include "Graphics/GFX/Renderer/GFX_Shader.h"
#include "Graphics/GFX/Renderer/GFXI_Material.h"

#include "Graphics/OPENGL3/OGL3_Shader.h"

//This class is to send uniforms to shader with GFX API specific way! I mean, this class handles OpenGL3 calls to send uniforms
class OGL3_Material {
private:
	static void Bind_Uniform(GFXI_Material* material, unsigned int uniform_list_index);
public:
	static void Bind_Material(GFXI_Material* material);
};

void OGL3_Material::Bind_Material(GFXI_Material* material) {
	if (OGL3_Shader::Find_Shader_Type(material->SHADER) != OPENGL_3) {
		cout << "Error: Bound Material isn't type of OpenGL3 Shader!\n";
		return;
	}

	//Bind Shader!
	glUseProgram(material->SHADER->Return_Shader_ID());

	//Bind each uniform!
	for (unsigned int i = 0; i < material->UNIFORM_LIST.size(); i++) {
		Bind_Uniform(material, i);
	}
}

void OGL3_Material::Bind_Uniform(GFXI_Material* material, unsigned int uniform_list_index) {
	//The uniform we will bind!
	Material_Uniform* uniform = &material->UNIFORM_LIST[uniform_list_index];

	//Get Uniform Location!
	int location = glGetUniformLocation(material->SHADER->Return_Shader_ID(), uniform->VARIABLE_NAME.c_str());
	if (location == -1) {
		cout << "Error: Intended uniform can't be found by OGL3_Material::Send_Uniform!\n";
		return;
	}

	switch (uniform->VARIABLE_TYPE) {
	case GFX_MAT4x4:
		glUniformMatrix4fv(location, 1, GL_FALSE, uniform->DATA);
		break;

	default:
		cout << "Error: Sending an unsupported uniform type! Nothing happened!\n";
		return;
	}
}