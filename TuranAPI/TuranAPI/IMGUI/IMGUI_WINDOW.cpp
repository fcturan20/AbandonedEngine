#include "IMGUI_WINDOW.h"
using namespace TuranAPI::IMGUI;

IMGUI_WindowManager::IMGUI_WINDOW::IMGUI_WINDOW(const char* name) : Window_Name(name) {
	for (unsigned int i = 0; i < IMGUI_WindowManager::SELF->ALL_IMGUI_WINDOWs.size(); i++) {
		IMGUI_WINDOW* WINDOW = IMGUI_WindowManager::SELF->ALL_IMGUI_WINDOWs[i];
		if (WINDOW->Window_Name == Window_Name) {
			Window_Name = Window_Name + "  ";
		}
	}
	IMGUI_WindowManager::SELF->ALL_IMGUI_WINDOWs.push_back(this);

	std::cout << "Editor Window created: " << name << std::endl;
}

IMGUI_WindowManager::IMGUI_WINDOW::~IMGUI_WINDOW() {
	std::cout << "Editor Window is closed: " << Window_Name << std::endl;
	unsigned int window_vector_index = 0;
	for (window_vector_index = 0; window_vector_index < IMGUI_WindowManager::SELF->ALL_IMGUI_WINDOWs.size(); window_vector_index++) {
		IMGUI_WINDOW* WINDOW = IMGUI_WindowManager::SELF->ALL_IMGUI_WINDOWs[window_vector_index];
		if (WINDOW == this) {
			break;
		}
	}
	IMGUI_WindowManager::SELF->ALL_IMGUI_WINDOWs.erase(window_vector_index);
}

bool IMGUI_WindowManager::IMGUI_WINDOW::Get_Is_Window_Open() {
	return Is_Window_Open;
}

IMGUI_WindowManager::IMGUI_WindowManager() : ALL_IMGUI_WINDOWs(LASTUSEDALLOCATOR, 1, 4){
	std::cout << "IMGUI WindowManager has started!\n";
}
IMGUI_WindowManager* IMGUI_WindowManager::SELF = nullptr;
void IMGUI_WindowManager::Run_IMGUI_WINDOWs() {
	/*
	for (unsigned int i = 0; i < ALL_IMGUI_WINDOWs.size(); i++) {
		ALL_IMGUI_WINDOWs[i]->Run_Window();
	}*/
}
