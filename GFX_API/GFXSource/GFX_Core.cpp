#include "GFX_Core.h"

vector<GFX_WINDOW*> GFX_API::ONSCREEN_Windows = vector<GFX_WINDOW*>();
vector<GFX_MONITOR*> GFX_API::CONNECTED_Monitors = vector<GFX_MONITOR*>();

vector<GFX_RenderGraph*> GFX_API::BOUND_RenderGraphs;
GFX_API* GFX_API::GFX_API_OBJ = nullptr;
GFX_Renderer* GFX_API::RENDERER = nullptr;
unsigned int GFX_API::FOCUSED_WINDOW_index = 0;
GFX_FileSystem* GFX_API::FileSystem = nullptr;

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
		if (window->Get_Window_GPU_ContentID() == id) {
			return window;
		}
	}
	cout << "Error: Intended window couldn't be found!\n";
	return nullptr;
}

void GFX_API::Bind_RenderGraph(GFX_RenderGraph* RenderGraph) {
	BOUND_RenderGraphs.push_back(RenderGraph);
}

void GFX_API::Create_RenderGraph_Resources(GFX_RenderGraph* RenderGraph) {
	//This loop checks if the 
	for (GFX_RenderGraph* rendergraph : BOUND_RenderGraphs) {
		if (rendergraph == RenderGraph) {
			RenderGraph->Create_Resources();
			return;
		}
	}

	cout << "Did you forget to bind RenderGraph: " << RenderGraph->NAME << "?";
	SLEEP_THREAD(10);
}

void GFX_API::Render_ALL_RenderGraphs() {
	for (GFX_RenderGraph* RENDERGRAPH : BOUND_RenderGraphs) {
		RENDERGRAPH->Run_RenderGraph();
	}
}

void GFX_API::Create_RenderGraphs() {
	for (GFX_RenderGraph* RENDERGRAPH : BOUND_RenderGraphs) {
		RENDERGRAPH->Create_Resources();
	}
}

const vector<GFX_RenderGraph*>* GFX_API::Get_Bound_RenderGraphs() {
	return &BOUND_RenderGraphs;
}