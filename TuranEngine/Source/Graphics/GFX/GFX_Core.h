#pragma once
#include <Includes.h>

#include "Graphics/GFX/GFX_ENUMs.h"
#include "Graphics/GFX/GFX_Monitor.h"
#include "Graphics/GFX/GFX_Window.h"
#include "Graphics/GFX/Renderer/GFX_Renderer.h"

class GFX_API {
protected:
	vector<GFX_WINDOW*> ONSCREEN_Windows;
	vector<GFX_MONITOR*> CONNECTED_Monitors;

	GFX_Renderer* RENDERER;

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
	vector<const GFX_WINDOW*> Get_Window_List();
	GFX_WINDOW* Get_Window_byID(void* id);

	//Renderer Operations
	virtual void Creation() = 0;
	virtual void New_Frame() = 0;
	virtual void Refresh_Windows() = 0;
	virtual void Swap_Buffers() = 0;

	//Input (Keyboard-Controller) Operations
	virtual void Take_Inputs() = 0;
};

		//WINDOW OPERATIONs

vector<const GFX_WINDOW*> GFX_API::Get_Window_List() {
	vector<const GFX_WINDOW*> const_window_list;
	for (GFX_WINDOW* window : ONSCREEN_Windows) {
		const GFX_WINDOW* const_window = window;
		const_window_list.push_back(const_window);
	}
	return const_window_list;
}

GFX_WINDOW* GFX_API::Get_Window_byID(void* id) {
	for (GFX_WINDOW* window : ONSCREEN_Windows) {
		if (window->Get_Window_ID() == id) {
			return window;
		}
	}
	cout << "Error: Intended window couldn't be found!\n";
	return nullptr;
}
