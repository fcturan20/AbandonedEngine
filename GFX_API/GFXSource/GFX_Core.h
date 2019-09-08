#pragma once
#include "GFX_Includes.h"
#include "TuranAPI/API_FileSystem.h"

#include "GFX_FileSystem.h"
#include "GFX_Monitor.h"
#include "Renderer/GFX_Renderer.h"

class GFXAPI GFX_API {
protected:
	//RenderGraphs that created at run-time! For example, Main world RenderGraph and Object View RenderGraph!
	static vector<GFX_RenderGraph*> BOUND_RenderGraphs;

	static unsigned int FOCUSED_WINDOW_index;

	virtual void Initialization() = 0;
	virtual void Save_Monitors() = 0;
	virtual void Create_Renderer() = 0;


public:
	static GFX_API* GFX_API_OBJ;
	static GFX_Renderer* RENDERER;
	static GFX_FileSystem* FileSystem;

	//There will be only one GFX_API instance, so making vectors static allows us to use them in callbacks!
	static vector<GFX_WINDOW*> ONSCREEN_Windows;
	static vector<GFX_MONITOR*> CONNECTED_Monitors;

	//Window Operations
	virtual void Create_Window(string name) = 0;
	virtual void Close_Window(GFX_WINDOW* window) = 0;
	virtual void Change_Window_Resolution(GFX_WINDOW* window, unsigned int width, unsigned int height) = 0;
	virtual void Set_Window_Focus(GFX_WINDOW* window, bool is_focused) = 0;
	virtual void Set_Window_Callbacks() = 0;
	static vector<const GFX_WINDOW*> Get_Window_List();
	static GFX_WINDOW* Get_Window_byID(void* id);
	virtual void Bind_Window_Context(GFX_WINDOW* window) = 0;

	//Renderer Operations
	virtual void Bind_Renderer_Context() = 0;
	static void Bind_RenderGraph(GFX_RenderGraph* RenderGraph);
	static void Create_RenderGraph_Resources(GFX_RenderGraph* RenderGraph);
	//If you want to create render resources for all of RenderGraphs automatically, use this!
	//But, if you want to set a specific RenderGraph's resources, use Create_RenderGraph_Resources!
	static void Create_RenderGraphs();
	virtual void New_Frame() = 0;
	virtual void Render_RenderGraph(GFX_RenderGraph* RenderGraph) = 0;
	//If you want to render all of RenderGraphs automatically, use this!
	//But, if you want to render a specific RenderGraph, use Render_RenderGraph!
	//Please, be sure that resources are set to render!
	static void Render_ALL_RenderGraphs();
	virtual void Refresh_Windows() = 0;
	virtual void Swap_Buffers() = 0;
	virtual void Render_IMGUI() = 0;
	static const vector<GFX_RenderGraph*>* Get_Bound_RenderGraphs();
	virtual void Check_GL_Errors(const string& status) = 0;

	//Load default GFX_API needed contents (Like PostProccess material type)
	virtual void Load_GFX_Files() = 0;

	//Input (Keyboard-Controller) Operations
	virtual void Take_Inputs() = 0;
	virtual void Destroy_GFX_Resources() = 0;

};
