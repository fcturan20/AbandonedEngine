#pragma once
#include "GFXSource/GFX_Includes.h"
#include "TuranAPI/API_FileSystem.h"

#include "GFXSource/GFX_Window.h"
#include "GFX_Draw_Pass.h"
#include "GFX_Framebuffer.h"
#include "GFX_Render_Target.h"
#include "GFX_Renderer.h"
#include "GFX_RenderGraph.h"
#include "GFX_Shader_Resource.h"
#include "GFXI_Draw_Resource.h"
#include "GFXI_MESH_REPRESENTATION.h"
#include "GFXI_Render_Node.h"

class GFXAPI GFX_Renderer {
protected:
	friend class GFX_API;


public:
	~GFX_Renderer();
	void* Renderer_Context;
	static GFX_Renderer* Renderer_OBJ;

		//Render States to avoid unneccessary calls!

	GFX_Framebuffer* Active_Framebuffer;
	TuranAPI::File_System::Material_Type_Resource* Active_ShaderProgram;


		//RENDERER FUNCTIONs

	//Bindings

	virtual void Bind_Framebuffer(GFX_Framebuffer* FRAMEBUFFER) = 0;
	virtual void Attach_RenderTargets_to_Framebuffer(GFX_Framebuffer* FRAMEBUFFER) = 0;
	virtual void Bind_Material_Instance(TuranAPI::File_System::Material_Instance* Material_Instance) = 0;
	virtual void Show_RenderTarget_onWindow(GFX_WINDOW* WINDOW_to_Display, GFX_Render_Target* RenderTarget_to_Show) = 0;
	//Resource Creation

	virtual GFX_Framebuffer* Create_Framebuffer(unsigned int width, unsigned int height) = 0;
	virtual void Create_RenderTarget(GFX_Framebuffer* FRAMEBUFFER, unsigned int width, unsigned int height, TuranAPI::TuranAPI_ENUMs dimension, GFX_ENUM format, GFX_ENUM attachment, TuranAPI::TuranAPI_ENUMs value_type) = 0;
	virtual void Compile_MaterialType(string* compilation_status, const string* vertex_source, const string* fragment_source, unsigned int* program_id = nullptr, unsigned int* vertex_id = nullptr, unsigned int* fragment_id = nullptr) = 0;
	static void Compile_All_MaterialTypes();
	//Resource Clear/Destroy (Add here shader, model, texture destructions!)

	virtual void Clear_RenderTarget(GFX_Framebuffer* FRAMEBUFFER, GFX_ENUM ATTACHMENT, vec3 CLEAR_COLOR) = 0;
	//Resource Setting (Add here texture type changes etc)

	virtual void Change_Framebuffer_Resolution(GFX_Framebuffer* FRAMEBUFFER, unsigned int width, unsigned int height) = 0;
	//Render State

	virtual void Set_Depth_Test(GFX_ENUM DEPTH_TEST_MODE, GFX_ENUM DEPTH_BUFFER_MODE) = 0;
	virtual void Check_ActiveFramebuffer_Status(string name_of_framebuffer) = 0;
	//Sending data to GPU

	virtual void Send_Textures_to_GPU(vector<TuranAPI::File_System::Texture_Resource*>* Textures) = 0;
	virtual void Send_StaticModelDatas_to_GPU(vector<TuranAPI::File_System::Static_Model_Data*>* StaticModel_Datas) = 0;
	//Draw Polygon

	virtual void Draw_Indexed_Objects(vector<void*> Vertex_Attributes, vector<unsigned int> Indice_Numbers) = 0;


};