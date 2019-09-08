#pragma once
#include "GFXSource/GFX_Includes.h"
#include "GFX_Draw_Pass.h"


class GFXAPI GFX_RenderGraph {
protected:

	vector<GFX_Draw_Pass*> DRAW_PASSes;
public:
	string NAME;

	//Functions to define each RenderGraph!
	virtual void Create_Resources() = 0;
	virtual void Update_Resources() = 0;
	virtual void Run_RenderGraph() = 0;

	GFX_Draw_Pass* Get_DrawPass_byName(const string& NAME);

	GFX_RenderGraph();

};
