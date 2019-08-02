#include "Main.h"

/*Turan Engine Running Process:
	1) Load Model_Files when Model_Loader_OBJ is created!
	2) For now: Create a Static_Model_Instance from first loaded Model!
	3) For now: Create a Scene and Add every Static_Model_Instance to Scene, no Camera!
	4) Create OGL3_SYS to initialize GLFW and OpenGL and create an offscreen and an onscreen window!
	5) For now: Call GFX->Creation() -> Create a Main_RenderGraph and give its pointer to Scene!
	6) For now: Create resources of Main_RenderGraph of the Scene! This means: Send Models to GPU, Create Draw Passes (Framebuffers etc.) -Only G-Buffer for now!-
	7) 
*/

int main() {
	cout << "Main() is started!\n" << endl;

	//Create resource creation process for Renderer!
	GFX->Creation();

	while (!ShouldApplication_Close) {
		double time = glfwGetTime();
		cout << "\n\nNew Loop!\n";
		//Call all RenderGraphs to render!
		GFX->New_Frame();
		//Refresh window contents (Generally, render textures that provided by Renderer to windows' default framebuffers!)
		GFX->Refresh_Windows();
		//Swap buffers for all windows to display latest changes on windows!
		GFX->Swap_Buffers();

		//Calculate how much milliseconds the frame is finished in!
		double timing_in_ms = glfwGetTime() - time;
		cout << "Frame is: " << timing_in_ms * 1000 << " ms!" << endl;


		while ((glfwGetTime() - time) * 1000 < 15) {
			//Do an infinity loop to wait for the next frame!
		}
		

		//Take inputs by GFX API specific library that supports input (For now, just GLFW for OpenGL3) and send it to Engine!
		GFX->Take_Inputs();
	}

	cout << "Application exited from the frame loop\n";
	cout << "Application is closing in 10 seconds!\n";
	this_thread::sleep_for(chrono::seconds(10));
	return 0;
}