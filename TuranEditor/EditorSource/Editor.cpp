#include "Editor.h"
#include "VulkanSource/Vulkan_Core.h"

int main() {
	TuranEditor::TE_DependentSystems DependentSystem_Creation;		//This class will hold up pointers to all of the system used in Turan Editor.
	
	TuranAPI::WRITE_LOGs_toFILEs();
	while (!TuranEngine->ShouldEngine_Close()) {
		TuranAPI::LOG_STATUS("New Loop!");
		TuranAPI::LOG_NOTCODED("Vulkan back-end is not coded for the Run Loop!", false);
		//Notify systems that we are in new Frame!
		//TuranAPI::IMGUI::IMGUI::New_Frame();
		GFX->New_Frame();

		//Editor is just a pack of IMGUI windows, so run them!
		//TuranAPI::IMGUI::IMGUI_WINDOW::Run_IMGUI_WINDOWs();

		//In Editor, the resources that are send to Renderer will be rendered! Renderer will gather the data and render.
		GFX->Render();
		//IMGUI can use main renderer's contents, so render IMGUI later!
		//TuranEngine::GFX->Render_IMGUI();

		//Swap buffers for all windows to display latest changes on windows (Geometry Viewports and IMGUIs)!
		GFX->Show_ThisFrame_onWindows();

		//Take inputs by GFX API specific library that supports input (For now, just GLFW for OpenGL3) and send it to Engine!
		//In final product, directly OS should be used to take inputs!
		((Vulkan::Vulkan_Core*)GFX)->Create_Window("First Custom Window");
		std::cout << "FRAME HAS ENDED!\n";
	}
	TuranAPI::LOG_STATUS(TuranEngine->Why_Engine_Closed());
	TuranAPI::WRITE_LOGs_toFILEs();
	std::cout << "Application is closing in 1 seconds!\n";
	SLEEP_THREAD(1);

	return 1;
}


/*
int main() {
	
	TuranAPI::LOG_STATUS("Editor is running!");
	TuranEngine::SetEngineClosing_Callback(Wait_whileClosing);
	EDITOR_FILESYSTEM->Start_EditorFileSystem();
	EDITOR_FILESYSTEM->Load_FileListContents_fromDisk();

	Main_Window* main_window = new Main_Window;

	//GameEngine.ShouldApplication_Close() doesn't work properly for now!
	while (!TuranEngine::ShouldEngine_Close()) {
		is_Frame_Finished = false;

		TuranAPI::LOG_STATUS("New Loop!");
		TuranAPI::LOG_NOTCODED("Vulkan back-end is not coded for the Run Loop!", false);
		//Notify systems that we are in new Frame!
		//TuranAPI::IMGUI::IMGUI::New_Frame();
		TuranEngine::GFX->New_Frame();

		//Editor is just a pack of IMGUI windows, so run them!
		//TuranAPI::IMGUI::IMGUI_WINDOW::Run_IMGUI_WINDOWs();

		//In Editor, the resources that are send to Renderer will be rendered! Renderer will gather the data and render.
		TuranEngine::GFX->Render();
		//IMGUI can use main renderer's contents, so render IMGUI later!
		//TuranEngine::GFX->Render_IMGUI();

		//Swap buffers for all windows to display latest changes on windows (Geometry Viewports and IMGUIs)!
		TuranEngine::GFX->Show_ThisFrame_onWindows();

		//Take inputs by GFX API specific library that supports input (For now, just GLFW for OpenGL3) and send it to Engine!
		//In final product, directly OS should be used to take inputs!
		TuranEngine::GFX->Take_Inputs();
		std::cout << "FRAME HAS ENDED!\n";
		is_Frame_Finished = true;
	}
	TuranAPI::LOG_STATUS("Application exited from the frame loop, because: " + TuranEngine::Why_Engine_Closed());
	TuranAPI::WRITE_LOGs_toFILEs();
	std::cout << "Application is closing in 1 seconds!\n";
	SLEEP_THREAD(1);
	
	return 1;
}*/