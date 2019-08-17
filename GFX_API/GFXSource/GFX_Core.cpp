#include "GFX_Core.h"

vector<GFX_WINDOW*> GFX_API::ONSCREEN_Windows = vector<GFX_WINDOW*>();
vector<GFX_MONITOR*> GFX_API::CONNECTED_Monitors = vector<GFX_MONITOR*>();

GFX_API* GFX_API::GFX_API_OBJ = nullptr;
GFX_Renderer* GFX_API::RENDERER = nullptr;
unsigned int GFX_API::FOCUSED_WINDOW_index = 0;

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
