#pragma once
#include "Engine_Includes.h"
#include "OpenGL3Source/OGL3_Core.h"

class Game_RenderGraph : public GFX_RenderGraph
{
public:
	virtual void Create_Resources() override;
	virtual void Update_Resources()  override;
	virtual void Run_RenderGraph() override;
};

