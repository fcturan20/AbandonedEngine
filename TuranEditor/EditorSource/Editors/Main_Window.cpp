#include "Main_Window.h"
#include "TuranAPI/API_FileSystem.h"
#include "TuranAPI/API_IMGUI.h"

#include "Content_Browser.h"
#include "IMGUI_DEFAULT_WINDOWs.h"
#include "Scene_Editor.h"

#include "GFXSource/GFX_Core.h"

using namespace TuranAPI::IMGUI;

Main_Window::Main_Window() : IMGUI_WINDOW("Main_Window") {

}

//Create main menubar for the Editor's main window!
void Main_Menubar_of_Editor();

void Main_Window::Run_Window() {
	if (!Is_Window_Open) {
		IMGUI::Is_IMGUI_Open = false;
		delete this;
		return;
	}
	if (!IMGUI::Create_Window("Main Window", Is_Window_Open, true)) {
		cout << "Main window is hidden or having problem at opening!\n";
		IMGUI::End_Window();
		return;
	}
	//Successfully created the window!
	Main_Menubar_of_Editor();

	unsigned int RT_ID = (*GFX_API::Get_Bound_RenderGraphs())[0]->Get_DrawPass_byName("G-Buffer")->Get_Framebuffer()->BOUND_RTs[0]->Get_ID();
	IMGUI::Display_Texture(&RT_ID, 960, 540, true);

	IMGUI::End_Window();
}

void Main_Menubar_of_Editor() {
	if (!IMGUI::Begin_Menubar()) {
		IMGUI::End_Menubar();
	}
	//Successfully created the main menu bar!

	if (IMGUI::Begin_Menu("View")) {
		if (IMGUI::Menu_Item("Game Content Browser")) { new GameContent_Browser; }
		if (IMGUI::Menu_Item("GFX Content Browser")) { new GFX_Content_Browser; }
		if (IMGUI::Menu_Item("Scene Editor")) { new Scene_Editor; }
		if (IMGUI::Menu_Item("Demo Window")) { new IMGUI_DemoWindow; }
		if (IMGUI::Menu_Item("Metrics Window")) { new IMGUI_MetricsWindow; }
		IMGUI::End_Menu();
	}


	//End Main Menubar operations!
	IMGUI::End_Menubar();
}