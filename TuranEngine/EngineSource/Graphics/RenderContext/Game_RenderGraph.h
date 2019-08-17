#pragma once
#include "Engine_Includes.h"

class Game_RenderGraph : public GFX_RenderGraph
{
public:
	virtual void Create_RenderGraph_Resources();
	virtual void Run_RenderGraph();
};

