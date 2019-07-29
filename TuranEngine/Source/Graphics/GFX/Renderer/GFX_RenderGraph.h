#pragma once
#include "Includes.h"

#include "Engine/Meshes/Mesh_HEADER.h"

#include "GFX_Draw_Pass.h"

#include "Engine/Scene/Scene_Core.h"

class GFX_RenderGraph {
protected:
	static vector<GFX_RenderGraph*> ALL_RenderGraphs;

	vector<GFX_Draw_Pass*> DRAW_PASSes;
	Scene* SCENE;

	//For now, just send static models to GPU!
	virtual void Update_GPU_Mesh_Buffers() = 0;
public:
	//Functions to define each RenderGraph!
	virtual void Create_RenderGraph_Resources() = 0;
	virtual void Run_RenderGraph() = 0;

	GFX_RenderGraph() {
		ALL_RenderGraphs.push_back(this);
	}

	void Set_Scene(Scene* scene) {
		SCENE = scene;
	}
};


vector<GFX_RenderGraph*> GFX_RenderGraph::ALL_RenderGraphs = vector<GFX_RenderGraph*>();
