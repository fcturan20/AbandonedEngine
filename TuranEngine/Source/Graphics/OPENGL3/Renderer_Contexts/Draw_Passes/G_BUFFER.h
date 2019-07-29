#pragma once
#include "Includes.h"

#include "Engine/Meshes/Mesh_HEADER.h"

#include "Engine/EngineComponents/Static_Model_Instance.h"

#include "Graphics/GFX/Renderer/GFX_Shader.h"
#include "Graphics/GFX/Renderer/GFX_Draw_Pass.h"

#include "Graphics/OPENGL3/OGL3_ENUMs.h"
#include "Graphics/OPENGL3/OGL3_Mesh.h"
#include "Graphics/OPENGL3/OGL3_Shader.h"
#include "Graphics/OPENGL3/OGL3_Draw_Pass.h"

class G_BUFFER_DrawResource : public GFXI_Draw_Resource {
	friend class G_BUFFER_DrawPass;

	vector<unsigned int> Static_VAOs;
	vector<unsigned int> Static_Vertex_Numbers;
	vector<unsigned int> Static_Indice_Numbers;
	vector<int> Static_EBOs;
	vector<GFX_Shader*> Static_Shaders;
	vector<mat4> Static_World_Transforms;

	G_BUFFER_DrawResource(Scene* scene) {
		SCENE = scene;
		//Search Static Models of all Scene and for each model, if one of draw pass names that is in the model is G-Buffer then add it to vector
		vector<Static_Model_Instance*> models_in_drawpass;
		for (Static_Model_Instance* model_in_scene : *SCENE->Access_Static_MODELs()) {
			for (string draw_pass_name : model_in_scene->Get_Draw_Pass_Names()) {
				if (draw_pass_name == "G-Buffer") {
					models_in_drawpass.push_back(model_in_scene);
				}
			}
		}

		for (Static_Model_Instance* model : models_in_drawpass) {
			Add_Static_Model(model);
		}
	}

	void Add_Static_Model(Static_Model_Instance* model) {
		unsigned int mesh_number = model->Access_Model()->Meshes_of_Model.size();
		for (unsigned int mesh_index = 0; mesh_index < mesh_number; mesh_index++) {
			GFXI_MESH* mesh_data = (GFXI_MESH*)model->Access_Model()->Meshes_of_Model[mesh_index]->Get_GFXI_Mesh();

			//Find Shader ID for each mesh of the model and add it to IDs vector!
			//For now, a model only has one shader so this implementation is bad but I don't have time for that!
			//Because it is easy to access the vector with mesh index, in rendering!
			Static_Shaders.push_back(
				GFX_Shader::Find_Shader_byName(model->Return_Shader_Name())
			);
			
			Static_VAOs.push_back(mesh_data->Return_VAO());
			Static_Vertex_Numbers.push_back(mesh_data->Return_Vertex_Number());
			Static_Indice_Numbers.push_back(mesh_data->Return_Indices_Number());
			Static_World_Transforms.push_back(model->Return_World_Transform());
			Static_EBOs.push_back(mesh_data->Return_EBO());
		}
	}
};

class G_BUFFER_DrawPass : public OGL3_Draw_Pass {
	virtual void Creation(Scene* scene) {
		NAME = "G-Buffer";
		SCENE = scene;

		FRAMEBUFFER->WIDTH = 1280;
		FRAMEBUFFER->HEIGHT = 720;
		glGenFramebuffers(1, &FRAMEBUFFER->ID);

		//First Render Texture is Color
		Create_RenderTarget(1280, 720, GFX_TEXTURE_2D, GFX_COLORTEXTURE_FORMAT, GFX_TEXTURE_COLOR0_ATTACHMENT, GFX_UNSIGNED_BYTE);
		//Second Render Texture is Depth
		Create_RenderTarget(1280, 720, GFX_TEXTURE_2D, GFX_DEPTHTEXTURE_FORMAT, GFX_TEXTURE_DEPTH_ATTACHMENT, GFX_FLOAT);
		Attach_RenderTargets_to_Framebuffer();

		DRAW_RESOURCE = new G_BUFFER_DrawResource(SCENE);
		cout << NAME << " Draw Pass Creation is done!\n";
	}

	virtual void Render_Loop() {
		cout << "G-Buffer Render Loop is started to run!\n";

		mat4 view_matrix = CAMERA->Return_View_Matrix();
		mat4 projection_matrix = CAMERA->Return_Projection_Matrix();

		glBindFramebuffer(GL_FRAMEBUFFER, FRAMEBUFFER->ID);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//For each mesh in the Draw Pass!
		G_BUFFER_DrawResource* gbuffer_resource = (G_BUFFER_DrawResource*)DRAW_RESOURCE;
		unsigned int RenderMesh_Number = gbuffer_resource->Static_VAOs.size();
		for (unsigned int mesh_index = 0; mesh_index < RenderMesh_Number; mesh_index++) {
			//Find shader ID to bind!
			GFX_Shader* Shader = gbuffer_resource->Static_Shaders[mesh_index];
			unsigned int SHADER_ID = Shader->Return_Shader_ID();
			glUseProgram(SHADER_ID);
			Check_OpenGL_Errors("After binding mesh's shader in G-Buffer Draw Pass!");

			//Send Transform Matrixes!
			glUniformMatrix4fv(glGetUniformLocation(SHADER_ID, "projection_matrix"), 1, GL_FALSE, value_ptr(projection_matrix));
			glUniformMatrix4fv(glGetUniformLocation(SHADER_ID, "view_matrix"), 1, GL_FALSE, value_ptr(view_matrix));
			Check_OpenGL_Errors("After binding uniforms of a mesh in G-Buffer Draw Pass!");

			glBindVertexArray(gbuffer_resource->Static_VAOs[mesh_index]);
			Check_OpenGL_Errors("After binding VAO of a mesh in G-Buffer Draw Pass!");
			glDrawElements(GL_TRIANGLES, gbuffer_resource->Static_Indice_Numbers[mesh_index], GL_UNSIGNED_INT, 0);
			Check_OpenGL_Errors("After drawing a mesh in G-Buffer Draw Pass!");
		}

		cout << "G-Buffer Render Loop is finished!\n";
	}
};