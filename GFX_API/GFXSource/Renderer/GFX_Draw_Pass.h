#pragma once
#include "GFXSource/GFX_Includes.h"

//Mesh Library
//#include "Graphics/Meshes/Mesh_HEADER.h"

#include "GFX_Render_Target.h"
#include "GFX_Framebuffer.h"
#include "GFXI_Render_Node.h"
//#include "GFXI_MESH_REPRESENTATION.h"
#include "GFXI_Draw_Resource.h"


	//If you want to create a Draw Pass:
	//1) You should create a class inherited from this
	//2) Include the class header in GFX API specific header (For example: OGL3_Core)
	//3) Create an object as "new" in GFX API specfic class's Start_Creation()
	//4) Don't forget to give a name to the draw pass! It will show up in Framegraph, Debugging and Profiling!
class GFXAPI GFX_Draw_Pass : public GFXI_Render_Node {
	friend class GFX_Renderer;
	friend class OGL3_Renderer;

protected:
	GFX_Draw_Pass();

	//Store each Draw Pass!
	static vector<GFX_Draw_Pass*> Draw_Passes;


	//Framebuffer stores render targets too, see the code
	GFX_Framebuffer* FRAMEBUFFER;
	string NAME;
	GFX_ENUM DEPTHTEST_MODE;
	GFX_ENUM DEPTHBUFFER_MODE;


	//Every Draw_Pass should store a Draw_Resource!
	GFXI_Draw_Resource* DRAW_RESOURCE;


	//FUNCTIONALITIES TO DEFINE FOR EACH GFX API DRAW PASS! 

	//Set every render target (That means, framebuffer resolution will change) to same resolution
	virtual void Change_Resolution(unsigned int width, unsigned int height) = 0;
	virtual void Create_RenderTarget(unsigned int width, unsigned int height, GFX_ENUM dimension, GFX_ENUM format, GFX_ENUM attachment, GFX_ENUM value_type) = 0;
	virtual void Attach_RenderTargets_to_Framebuffer() = 0;
	virtual void Check_Framebuffer_Status() = 0;
	virtual void Set_Depth_and_StencilTest() = 0;

public:

	//Update Draw Resources of Draw Pass!
	//void Update_Resources(vector<GFXI_MESH*> Mesh_List);


	//FUNCTIONs TO FIND/IDENTIFY DRAW PASS!
	static GFX_Draw_Pass* Find_Draw_Pass_byName(string name);
	static vector<GFX_Draw_Pass*> Get_Draw_Passes();

	//FUNCTIONALITIES FOR EACH DRAW PASS!
	virtual void Creation() = 0;
	virtual void Render_Loop() = 0;

	//Getter-Setters
	GFX_Framebuffer* Get_Framebuffer();
	string Get_Name();
};