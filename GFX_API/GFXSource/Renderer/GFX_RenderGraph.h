#pragma once
#include "GFXSource/GFX_Includes.h"
#include "GFX_Draw_Pass.h"


class GFXAPI GFX_RenderGraph {
protected:

	vector<GFX_Draw_Pass*> DRAW_PASSes;

	//For now, just send static models to GPU!
	virtual void Update_GPU_Mesh_Buffers() = 0;
public:
	//Functions to define each RenderGraph!
	virtual void Create_RenderGraph_Resources() = 0;
	virtual void Run_RenderGraph() = 0;

	GFX_RenderGraph();

};
