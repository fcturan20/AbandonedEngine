#pragma once
#include "OpenGL3Source/OpenGL3_Includes.h"

class OGL3_API OGL3_Draw_Pass : public GFX_Draw_Pass {
protected:
	virtual void Change_Resolution(unsigned int width, unsigned int height);
	virtual void Create_RenderTarget(unsigned int width, unsigned int height, GFX_ENUM dimension, GFX_ENUM format, GFX_ENUM attachment, GFX_ENUM value_type);
	virtual void Attach_RenderTargets_to_Framebuffer();
	virtual void Check_Framebuffer_Status();
	virtual void Set_Depth_and_StencilTest();

public:
	virtual void Creation() = 0;
	virtual void Render_Loop() = 0;
};