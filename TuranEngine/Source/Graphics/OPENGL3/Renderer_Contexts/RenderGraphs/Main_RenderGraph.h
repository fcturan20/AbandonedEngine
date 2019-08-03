#pragma once
#include "Includes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphics/GFX/Renderer/GFX_RenderGraph.h"

#include "Graphics/OPENGL3/OGL3_RenderGraph.h"

class Main_RenderGraph : public OGL3_RenderGraph {
	virtual void Create_RenderGraph_Resources();
	virtual void Run_RenderGraph();
};

void Main_RenderGraph::Create_RenderGraph_Resources() {
	Update_GPU_Mesh_Buffers();
	cout << "Created GPU Mesh Buffers!\n" << endl;

	DRAW_PASSes.push_back(new G_BUFFER_DrawPass);
	//We know here that 0 is G-Buffer pass!
	DRAW_PASSes[0]->Creation(SCENE);
	DRAW_PASSes[0]->Set_Camera(SCENE->Return_Active_Camera());

	cout << "Created RenderGraph Resources!\n";
}

void Main_RenderGraph::Run_RenderGraph() {
	cout << "Running the RenderGraph of the Scene: " << SCENE->Return_Name() << "!\n";

	//When Dynamic and Skeletal meshes are supported, update gpu mesh buffers every frame!
	//Update_GPU_Mesh_Buffers();

	//We know here that 0 is G-Buffer pass!
	DRAW_PASSes[0]->Render_Loop();
}