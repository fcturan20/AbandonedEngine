#pragma once
#include "Includes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OGL3_ENUMs.h"
#include "Graphics/GFX/Renderer/GFX_Draw_Pass.h"

class OGL3_Draw_Pass : public GFX_Draw_Pass {
protected:
	virtual void Change_Resolution(unsigned int width, unsigned int height);
	virtual void Create_RenderTarget(unsigned int width, unsigned int height, TEXTURE_DIMENSION dimension, TEXTURE_FORMAT format, TEXTURE_ATTACHMENT attachment, TEXTURE_FORMAT_VALUETYPE value_type);
	virtual void Attach_RenderTargets_to_Framebuffer();
	virtual void Check_Framebuffer_Status();
	virtual void Set_Depth_and_StencilTest();

public:
	virtual void Creation(Scene* scene) = 0;
	virtual void Render_Loop() = 0;
};

void OGL3_Draw_Pass::Change_Resolution(unsigned int width, unsigned int height) {
	glBindFramebuffer(GL_FRAMEBUFFER, FRAMEBUFFER->ID);
	for (GFX_Render_Target* rt : FRAMEBUFFER->BOUND_RTs) {
		glBindTexture(GL_TEXTURE_2D, rt->ID);
		glTexImage2D(GL_TEXTURE_2D, 0, Find_Texture_Format(rt->FORMAT), width, height, 0, Find_Texture_Channel_Type(rt->FORMAT), Find_Texture_Value_Type(rt->FORMAT_VALUETYPE), NULL);
	}
	if (glGetError() != 0) {
		cout << "Error: When changing Framebuffer resolution!\n";
	}
	FRAMEBUFFER->WIDTH = width;
	FRAMEBUFFER->HEIGHT = height;
}

//Each Render Target Texture is in linear filter mode!
void OGL3_Draw_Pass::Create_RenderTarget(unsigned int width, unsigned int height, TEXTURE_DIMENSION dimension, TEXTURE_FORMAT format, TEXTURE_ATTACHMENT attachment, TEXTURE_FORMAT_VALUETYPE value_type) {
	GFX_Render_Target* gfx_rt = new GFX_Render_Target;
	//Note: Wrapping isn't supported for Render Target Textures
	gfx_rt->ATTACHMENT = attachment;
	gfx_rt->DIMENSION = dimension;
	gfx_rt->FORMAT = format;
	gfx_rt->FORMAT_VALUETYPE = value_type;

	int ATTACHMENT_TYPE = Find_Texture_Attachment_Type(attachment);
	int CHANNEL_TYPE = Find_Texture_Channel_Type(format);
	int FORMAT = Find_Texture_Format(format);
	int DIMENSION = Find_Texture_Dimension(dimension);
	int VALUE_TYPE = Find_Texture_Value_Type(value_type);

	unsigned int rt_id;
	glGenTextures(1, &rt_id);
	glBindTexture(GL_TEXTURE_2D, rt_id);
	glTexImage2D(GL_TEXTURE_2D, 0, FORMAT, width, height, 0, CHANNEL_TYPE, VALUE_TYPE, NULL);

	//Each Render Target Texture is in linear filter mode!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (glGetError() != 0) {
		cout << "Error: When creating Render Target!\n";
	}

	gfx_rt->ID = rt_id;
	FRAMEBUFFER->BOUND_RTs.push_back(gfx_rt);
}


void OGL3_Draw_Pass::Attach_RenderTargets_to_Framebuffer() {
	glBindFramebuffer(GL_FRAMEBUFFER, FRAMEBUFFER->ID);
	for (GFX_Render_Target* rt : FRAMEBUFFER->BOUND_RTs) {
		glBindTexture(GL_TEXTURE_2D, rt->ID);
		glFramebufferTexture2D(GL_FRAMEBUFFER, Find_Texture_Attachment_Type(rt->ATTACHMENT), GL_TEXTURE_2D, rt->ID, 0);
	}
	Check_Framebuffer_Status();
}

void OGL3_Draw_Pass::Check_Framebuffer_Status() {
	int status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status == GL_FRAMEBUFFER_COMPLETE) {
		cout << "Draw Pass: " << NAME << "'s framebuffer is successfully created!\n";
		return;
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) {
		cout << "Error: Draw Pass: " << NAME << "'s framebuffer has incomplete attachment!\n";
	}
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
		cout << "Error: Draw Pass: " << NAME << "'s framebuffer has incomplete missing attachment!\n";
	}
	if (status == GL_FRAMEBUFFER_UNSUPPORTED) {
		cout << "Error: Draw Pass: " << NAME << "'s framebuffer has unsupported type of attachment!\n";
	}
}

void OGL3_Draw_Pass::Set_Depth_and_StencilTest() {
	//Set Depth Func at start!
	glDepthFunc(Find_GFX_DepthTest_Mode(DEPTHTEST_MODE));
	if (DEPTHBUFFER_MODE == GFX_DEPTH_OFF) {
		cout << "Depth Test is closed!\n";
		glDisable(GL_DEPTH_TEST);
	}
	if (DEPTHBUFFER_MODE == GFX_DEPTH_READ_ONLY) {
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_FALSE);
	}
	if (DEPTHBUFFER_MODE == GFX_DEPTH_READ_WRITE) {
		glEnable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);
	}
}