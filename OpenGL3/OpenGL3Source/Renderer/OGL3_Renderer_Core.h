#pragma once
#include "OpenGL3Source/OpenGL3_Includes.h"

//OpenGL 3.0 related classes
#include "OGL3_Shader.h"
#include "OGL3_Material.h"
#include "OGL3_Texture.h"
#include "OGL3_Draw_Pass.h"
#include "OGL3_RenderGraph.h"

class OGL3_API OGL3_Renderer : public GFX_Renderer {
protected:
	friend class OGL3_SYS;

	virtual void Start_Creation();
	virtual void New_Frame();
	void Send_Quad_to_GPU();

	//Functions to use only in OGL3_Renderer functions
	//static void Check_Framebuffer_Status(string framebuffer_name);
	//virtual void Send_Quad_to_GPU();
};