#pragma once
#include "GFXSource/GFX_Includes.h"

#include "GFX_Draw_Pass.h"
#include "GFX_Framebuffer.h"
#include "GFX_Render_Target.h"
#include "GFX_Renderer.h"
#include "GFX_RenderGraph.h"
#include "GFX_Shader.h"
#include "GFX_Shader_Resource.h"
#include "GFX_Texture.h"
#include "GFXI_Draw_Resource.h"
#include "GFXI_Material.h"
#include "GFXI_MESH_REPRESENTATION.h"
#include "GFXI_Render_Node.h"

class GFXAPI GFX_Renderer {
protected:
	friend class OGL3_SYS;
	friend class GFX_API;

	void* Renderer_Context;

public:
	~GFX_Renderer();
};