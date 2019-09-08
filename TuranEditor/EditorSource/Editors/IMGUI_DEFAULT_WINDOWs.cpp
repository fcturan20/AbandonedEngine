#include "IMGUI_DEFAULT_WINDOWs.h"
#include "TuranAPI/IMGUI/IMGUI_Core.h"

using namespace TuranAPI::IMGUI;

IMGUI_DemoWindow::IMGUI_DemoWindow() : IMGUI_WINDOW("Demo Window") {

}

void IMGUI_DemoWindow::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	else {
		Is_Window_Open = IMGUI::Show_DemoWindow();
	}
}


IMGUI_MetricsWindow::IMGUI_MetricsWindow() : IMGUI_WINDOW("Metrics Window") {

}

void IMGUI_MetricsWindow::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	else {
		Is_Window_Open = IMGUI::Show_MetricsWindow();
	}
}
