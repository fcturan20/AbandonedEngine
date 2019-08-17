#include "OGL3_Material.h"

void OGL3_Material::Bind_Material(GFX_Material* material) {
	/*
	if (OGL3_Shader::Find_Shader_Type(material->SHADER) != OPENGL3) {
		cout << "Error: Bound Material isn't type of OpenGL3 Shader!\n";
		return;
	}

	//Bind Shader!
	glUseProgram(material->SHADER->Return_Shader_ID());

	//Bind each uniform!
	for (unsigned int i = 0; i < material->UNIFORM_LIST.size(); i++) {
		Bind_Uniform(material, i);
	}
	*/
}

void OGL3_Material::Bind_Uniform(GFX_Material* material, unsigned int uniform_list_index) {
	/*
	//The uniform we will bind!
	Material_Uniform* uniform = &material->UNIFORM_LIST[uniform_list_index];

	//Get Uniform Location!
	int location = glGetUniformLocation(material->SHADER->Return_Shader_ID(), uniform->VARIABLE_NAME.c_str());
	if (location == -1) {
		cout << "Error: Intended uniform: " << uniform->VARIABLE_NAME << " can't be found by OGL3_Material::Send_Uniform!\n";
		return;
	}
	if (uniform->DATA == nullptr) {
		cout << "Error: Uniform: " << uniform->VARIABLE_NAME << " data isn't set!\n";
		return;
	}

	unsigned int texture_id = *(unsigned int*)uniform->DATA;
	switch (uniform->VARIABLE_TYPE) {
	case GFX_MAT4x4:
		glUniformMatrix4fv(location, 1, GL_FALSE, (const float*)uniform->DATA);
		break;

	case GFX_TEXTURE_2D:
		//cout << "Texture ID: " << texture_id << endl;
		glActiveTexture(GL_TEXTURE0);
		Check_OpenGL_Errors("After activating texture!\n");
		glBindTexture(GL_TEXTURE_2D, texture_id);
		Check_OpenGL_Errors("After binding texture!\n");
		break;

	default:
		cout << "Error: Sending an unsupported uniform type! Nothing happened!\n";
		return;
	}
	*/
}