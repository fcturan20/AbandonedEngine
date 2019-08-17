#pragma once
#include "GFX_Includes.h"

#include "GFX_Monitor.h"
#include "GFX_Window.h"
#include "Renderer/GFX_Renderer.h"

class GFXAPI GFX_API {
protected:
	//There will be only one GFX_API instance, so making vectors static allows us to use them in callbacks!
	static vector<GFX_WINDOW*> ONSCREEN_Windows;
	static vector<GFX_MONITOR*> CONNECTED_Monitors;

	static GFX_API* GFX_API_OBJ;
	static GFX_Renderer* RENDERER;
	static unsigned int FOCUSED_WINDOW_index;

	virtual void Initialization() = 0;
	virtual void Save_Monitors() = 0;
	virtual void Create_Renderer() = 0;

	virtual void Destroy_GFX_Resources() = 0;

public:

	//Window Operations
	virtual void Create_Window(string name) = 0;
	virtual void Close_Window(GFX_WINDOW* window) = 0;
	virtual void Change_Window_Resolution(GFX_WINDOW* window, unsigned int width, unsigned int height) = 0;
	virtual void Set_Window_Focus(GFX_WINDOW* window, bool is_focused) = 0;
	virtual void Set_Window_Callbacks() = 0;
	static vector<const GFX_WINDOW*> Get_Window_List();
	static GFX_WINDOW* Get_Window_byID(void* id);

	//Renderer Operations
	virtual void Creation() = 0;
	virtual void New_Frame() = 0;
	virtual void Refresh_Windows() = 0;
	virtual void Swap_Buffers() = 0;

	//Input (Keyboard-Controller) Operations
	virtual void Take_Inputs() = 0;
};
