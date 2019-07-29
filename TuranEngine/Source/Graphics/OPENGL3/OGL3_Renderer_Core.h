#pragma once
//OpenGL 3.0 Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Mesh Library

#include "Engine/Meshes/Mesh_HEADER.h"
#include "Engine/EngineComponents/EngineComponent.h"
#include "Engine/EngineComponents/Static_Model_Instance.h"

#include "Engine/Scene/Scene_Core.h"

//GFX related classes
#include "Graphics/GFX/GFX_ENUMs.h"
#include "Graphics/GFX/GFX_Monitor.h"
#include "Graphics/GFX/GFX_Window.h"
#include "Graphics/GFX/Renderer/GFX_Shader_Resource.h"
#include "Graphics/GFX/Renderer/GFX_Shader.h"
#include "Graphics/GFX/Renderer/GFX_Render_Target.h"
#include "Graphics/GFX/Renderer/GFX_Framebuffer.h"
#include "Graphics/GFX/Renderer/GFXI_Render_Node.h"
#include "Graphics/GFX/Renderer/GFXI_MESH_REPRESENTATION.h"
#include "Graphics/GFX/Renderer/GFXI_Draw_Resource.h"
#include "Graphics/GFX/Renderer/GFX_Draw_Pass.h"
#include "Graphics/GFX/Renderer/GFX_RenderGraph.h"
#include "Graphics/GFX/Renderer/GFX_Renderer.h"
#include "Graphics/GFX/GFX_Core.h"

//OpenGL 3.0 related classes
#include "OGL3_ENUMs.h"
#include "OGL3_Shader.h"
#include "OGL3_Mesh.h"
#include "OGL3_Draw_Pass.h"
#include "Renderer_Contexts/Draw_Passes/Draw_Passes.h"
#include "OGL3_RenderGraph.h"
#include "Graphics/OPENGL3/Renderer_Contexts/RenderGraphs/RenderGraphs.h"

class OGL3_Renderer : public GFX_Renderer {
protected:
	friend class OGL3_SYS;

	virtual void Start_Creation();
	virtual void New_Frame();
	void Send_Quad_to_GPU();

	//Functions to use only in OGL3_Renderer functions
	//static void Check_Framebuffer_Status(string framebuffer_name);
	//virtual void Send_Quad_to_GPU();
	void Create_RenderGraph(unsigned int RenderGraph_type_index, Scene* scene);
	OGL3_RenderGraph* Create_RenderGraph_byType(unsigned int RenderGraph_type_index);
};

void OGL3_Renderer::Start_Creation() {
	//Compile all shader at Creation() because we don't want to get OpenGL initialization errors
	OGL3_Shader::Compile_All_Shaders();
	cout << "Compiled all shaders!\n\n";

	//Create render source (Framebuffer etc.) of every draw pass for each scene!
	for (Scene* SCENE : Scene::ALL_SCENEs) {
		//Create RenderGraph of the Scene and give Scene* to RenderGraph because RenderGraph should access to Scene's MODELs, CAMERAs
		Create_RenderGraph(SCENE->Get_RenderGraph_type_Index(), SCENE);
		GFX_RenderGraph* RenderGraph = (GFX_RenderGraph*)SCENE->Return_RenderGraph();
		RenderGraph->Create_RenderGraph_Resources();
	}
	cout << "RenderGraph Creation and Start_Creation() is finished!\n";
}

//Note: To display someting on windows, we should MakeCurrentContext(window) and BindFramebuffer(0) for each one of them!
//Because a window's default display framebuffer is 0
//After BindFramebuffer(0), you should render a quad with sending the render target you want to display
//After rendering, you can continue by other window!
void OGL3_Renderer::New_Frame() {
	//Run each scene, this means run every scene's gameplay codes! These will probably update the render contexts, so run RenderGraphs later!
	for (Scene* SCENE : Scene::ALL_SCENEs) {
		SCENE->Run_Scene();
	}
	cout << "Runned the scenes!\n";
	//Run each scene's RenderGraph, but in final production: Only run the displaying scene's RenderGraph!
	for (Scene* SCENE : Scene::ALL_SCENEs) {
		GFX_RenderGraph* RenderGraph = (GFX_RenderGraph*)SCENE->Return_RenderGraph();
		RenderGraph->Run_RenderGraph();
	}
}

void OGL3_Renderer::Create_RenderGraph(unsigned int RenderGraph_type_index, Scene* scene) {
	//Note: In final production, each rendergraph will be read from a file
	//This is why we use RenderGraph_type_index
	//Create a RenderGraph according to type_index and set Scene's pointer to point the created RenderGraph!
	OGL3_RenderGraph* RenderGraph = Create_RenderGraph_byType(RenderGraph_type_index);
	RenderGraph->Set_Scene(scene);
	scene->Set_RenderGraph(RenderGraph);
}

OGL3_RenderGraph* OGL3_Renderer::Create_RenderGraph_byType(unsigned int RenderGraph_type_index) {
	switch (RenderGraph_type_index) {
	case 0:
		//Create Main RenderGraph!
		return new Main_RenderGraph;
	default:
		cout << "There is no RenderGraph type: " << RenderGraph_type_index << endl;
		return nullptr;
	}
	return nullptr;
}


void OGL3_Renderer::Send_Quad_to_GPU() {
	vec2 quadVertices[] = {
		// positions   // texCoords
		vec2(-1.0f, 1.0f),
		vec2(-1.0f, -1.0f),
		vec2(1.0f, -1.0f),

		vec2(-1.0f, 1.0f),
		vec2(1.0f, -1.0f),
		vec2(1.0f, 1.0f),
	};

	vec2 quadTextCoords[] = {
		vec2(0.0f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.0f, 1.0f),
		vec2(1.0f, 0.0f),
		vec2(1.0f, 1.0f)
	};

	//Load once!
	unsigned int position_buffer_size = 6 * sizeof(vec2);
	GLuint PostProcessQuad_VAO, PostProcessQuad_VBO;
	glGenVertexArrays(1, &PostProcessQuad_VAO);
	glGenBuffers(1, &PostProcessQuad_VBO);
	glBindVertexArray(PostProcessQuad_VAO);
	Check_OpenGL_Errors("Error after binding VAO");

	glBindBuffer(GL_ARRAY_BUFFER, PostProcessQuad_VBO);
	glBufferData(GL_ARRAY_BUFFER, position_buffer_size * 2, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, position_buffer_size, quadVertices);
	glBufferSubData(GL_ARRAY_BUFFER, position_buffer_size, position_buffer_size, quadTextCoords);
	Check_OpenGL_Errors("Error after glBufferSubDatas");


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)(position_buffer_size));
	Check_OpenGL_Errors("Error after attribute settings");

	glBindVertexArray(0);
	OGL3_Mesh* gpu_mesh = new OGL3_Mesh;
	gpu_mesh->Indices_Number = 6;
	gpu_mesh->VAO = PostProcessQuad_VAO;
	gpu_mesh->VBO = PostProcessQuad_VBO;
	cout << "Quad Mesh VAO: " << PostProcessQuad_VAO << endl;
}