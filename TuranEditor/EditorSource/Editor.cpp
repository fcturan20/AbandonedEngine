#include "Editor.h"


int main() {
	cout << "Editor is running!\n";
	TuranEngine::Start_Engine();
	cout << "Started the engine!\n\n\n";
	Editor::File_System::Editor_FileSystem::Start_EditorFileSystem();
	Editor::File_System::Editor_FileSystem::Load_GameContents_fromDisk();


	//Create resource creation process for main RenderGraph!
	TuranEngine::GFX->Bind_Renderer_Context();
	TuranEngine::GFX->RENDERER->Compile_All_MaterialTypes();
	TuranEngine::GFX->RENDERER->Send_StaticModelDatas_to_GPU(&TuranAPI::File_System::Static_Model_Data::ALL_MODEL_DATAs);
	TuranEngine::GFX->RENDERER->Send_Textures_to_GPU(&TuranAPI::File_System::Texture_Resource::ALL_TEXTUREs);
	TuranEngine::GFX->Create_RenderGraphs();

	Main_Window* main_window = new Main_Window;

	//GameEngine.ShouldApplication_Close() doesn't work properly for now!
	while (!TuranEngine::ShouldEngine_Close()) {
		cout << "\n\nNew Loop!\n";

		TuranEngine::GFX->Bind_Renderer_Context();
		//We are using these here, because we can import new resources to application in run loop!
		TuranEngine::GFX->RENDERER->Compile_All_MaterialTypes();
		TuranEngine::GFX->RENDERER->Send_StaticModelDatas_to_GPU(&TuranAPI::File_System::Static_Model_Data::ALL_MODEL_DATAs);
		TuranEngine::GFX->RENDERER->Send_Textures_to_GPU(&TuranAPI::File_System::Texture_Resource::ALL_TEXTUREs);

		TuranEngine::GFX->New_Frame();						//Prepare all resources to new frame! (Do the cleaning and stuff like that for and RenderGraphs)
		TuranEngine::GFX->Render_ALL_RenderGraphs();		//Render scene geometries!

		//Note: GFX backend already sets context to Main Window to render IMGUI. To run IMGUI, Only you have to do is call these functions!
		TuranAPI::IMGUI::IMGUI::New_Frame();
		TuranAPI::IMGUI::IMGUI_WINDOW::Run_IMGUI_WINDOWs();	//Run all of the active IMGUI Windows!
		TuranEngine::GFX->Render_IMGUI();					//Only renders IMGUI for now!


		//Swap buffers for all windows to display latest changes on windows (Geometry Viewports and IMGUIs)!
		TuranEngine::GFX->Swap_Buffers();

		//Take inputs by GFX API specific library that supports input (For now, just GLFW for OpenGL3) and send it to Engine!
		//In final product, directly OS should be used to take inputs!
		TuranEngine::GFX->Take_Inputs();
	}

	cout << "Application exited from the frame loop, because: " << TuranEngine::Why_Engine_Closed() << "\n";
	cout << "Application is closing in 1 seconds!\n";
	this_thread::sleep_for(chrono::seconds(1));
	
	return 1;
}