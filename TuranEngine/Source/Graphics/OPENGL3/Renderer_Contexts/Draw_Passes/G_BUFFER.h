#pragma once
#include "Includes.h"

#include "Engine/Meshes/Mesh_HEADER.h"

#include "Engine/EngineComponents/Static_Model_Instance.h"

#include "Graphics/GFX/Renderer/GFX_Shader.h"
#include "Graphics/GFX/Renderer/GFXI_Material.h"
#include "Graphics/GFX/Renderer/GFX_Draw_Pass.h"

#include "Graphics/OPENGL3/OGL3_ENUMs.h"
#include "Graphics/OPENGL3/OGL3_Mesh.h"
#include "Graphics/OPENGL3/OGL3_Shader.h"
#include "Graphics/OPENGL3/OGL3_Material.h"
#include "Graphics/OPENGL3/OGL3_Draw_Pass.h"

class G_BUFFER_DrawResource : public GFXI_Draw_Resource {
	friend class G_BUFFER_DrawPass;

	vector<unsigned int> Static_VAOs;
	vector<unsigned int> Static_Vertex_Numbers;
	vector<unsigned int> Static_Indice_Numbers;
	vector<int> Static_EBOs;
	vector<GFXI_Material*> Static_Materials;

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
			GFXI_MESH* mesh_data = (GFXI_MESH*)model->Access_Model()->Meshes_of_Model[mesh_index]->MESH_INFO->Get_GFXI_Mesh();
			
			//Find Shader ID for each mesh of the model and add it to IDs vector!
			//For now, a model only has one shader so this implementation is bad but I don't have time for that!
			//Because it is easy to access the vector with mesh index, in rendering!
			Static_Materials.push_back(
				//Access pattern is changed!
				model->Access_Model()->Meshes_of_Model[mesh_index]->MATERIAL
			);
			
			Static_VAOs.push_back(mesh_data->Return_VAO());
			Static_Vertex_Numbers.push_back(mesh_data->Return_Vertex_Number());
			Static_Indice_Numbers.push_back(mesh_data->Return_Indices_Number());
			Static_EBOs.push_back(mesh_data->Return_EBO());
		}
	}
};

class G_BUFFER_DrawPass : public OGL3_Draw_Pass {
	virtual void Creation(Scene* scene) {
		NAME = "G-Buffer";
		SCENE = scene;
		//Set depth modes!
		DEPTHBUFFER_MODE = GFX_DEPTH_READ_WRITE;
		DEPTHTEST_MODE = GFX_DEPTH_LESS;
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		FRAMEBUFFER->WIDTH = 1920;
		FRAMEBUFFER->HEIGHT = 1061;
		glGenFramebuffers(1, &FRAMEBUFFER->ID);

		glBindFramebuffer(GL_FRAMEBUFFER, FRAMEBUFFER->ID);
		//First Render Texture is Color
		Create_RenderTarget(FRAMEBUFFER->WIDTH, FRAMEBUFFER->HEIGHT, GFX_TEXTURE_2D, GFX_COLORTEXTURE_FORMAT, GFX_TEXTURE_COLOR0_ATTACHMENT, GFX_UNSIGNED_BYTE);
		//Second Render Texture is Depth
		Create_RenderTarget(FRAMEBUFFER->WIDTH, FRAMEBUFFER->HEIGHT, GFX_TEXTURE_2D, GFX_DEPTHTEXTURE_FORMAT, GFX_TEXTURE_DEPTH_ATTACHMENT, GFX_FLOAT);
		Attach_RenderTargets_to_Framebuffer();

		DRAW_RESOURCE = new G_BUFFER_DrawResource(SCENE);
		cout << NAME << " Draw Pass Creation is done!\n";
	}

	virtual void Render_Loop() {
		cout << "G-Buffer Render Loop is started to run!\n";

		Set_Depth_and_StencilTest();


		glBindFramebuffer(GL_FRAMEBUFFER, FRAMEBUFFER->ID);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearDepth(1.0f);

		//For each mesh in the Draw Pass!
		G_BUFFER_DrawResource* gbuffer_resource = (G_BUFFER_DrawResource*)DRAW_RESOURCE;
		unsigned int RenderMesh_Number = gbuffer_resource->Static_VAOs.size();
		for (unsigned int mesh_index = 0; mesh_index < RenderMesh_Number; mesh_index++) {
			//Find Material to bind!
			GFXI_Material* Material = gbuffer_resource->Static_Materials[mesh_index];

			//Shader is already compiled in Creation() and uniforms has defined (if they are not initialized, they will use default values. Not a debug value!).
			OGL3_Material::Bind_Material(Material);
			Check_OpenGL_Errors("After binding uniforms of a mesh in G-Buffer Draw Pass!");

			glBindVertexArray(gbuffer_resource->Static_VAOs[mesh_index]);
			Check_OpenGL_Errors("After binding VAO of a mesh in G-Buffer Draw Pass!");
			glDrawElements(GL_TRIANGLES, gbuffer_resource->Static_Indice_Numbers[mesh_index], GL_UNSIGNED_INT, 0);
			Check_OpenGL_Errors("After drawing a mesh in G-Buffer Draw Pass!");
		}

		cout << "G-Buffer Render Loop is finished!\n";
	}
};