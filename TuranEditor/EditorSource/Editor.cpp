#include "Editor.h"



int main() {
	cout << "Editor is running!\n";

	TuranEngine::Start_Engine();

	/*
	Mesh_Loader::Load_All_Meshes();

	//Create resource creation process for Renderer!
	GameEngine.GFX->Creation();
	PostProcess_Material first_pp_material;

	//GameEngine.ShouldApplication_Close() doesn't work properly for now!
	while (!GameEngine.ShouldApplication_Close()) {
		cout << "\n\nNew Loop!\n";
		//Call all RenderGraphs to render!
		GameEngine.GFX->New_Frame();
		//Refresh window contents (Generally, render textures that provided by Renderer to windows' default framebuffers!)
		GameEngine.GFX->Refresh_Windows();
		//Swap buffers for all windows to display latest changes on windows!
		GameEngine.GFX->Swap_Buffers();


		//Take inputs by GFX API specific library that supports input (For now, just GLFW for OpenGL3) and send it to Engine!
		GameEngine.GFX->Take_Inputs();
	}

	cout << "Application exited from the frame loop, because: " << GameEngine.Why_Application_Closed() << "\n";
	cout << "Application is closing in 5 seconds!\n";
	this_thread::sleep_for(chrono::seconds(5));
	return 0;
	*/

	return 1;
}