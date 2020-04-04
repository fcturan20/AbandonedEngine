#include "Status_Window.h"

using namespace TuranAPI::IMGUI;

Status_Window::Status_Window(const char* status) : IMGUI_WINDOW("Status Window") {
	STATUS = status;
}

void Status_Window::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window("Status Window", Is_Window_Open, false)) {
		std::cout << "Shader Editor couldn't open!\n";
		IMGUI::End_Window();
		return;
	}
	//Successfully created here!
	IMGUI::Text(STATUS);


	IMGUI::End_Window();
}