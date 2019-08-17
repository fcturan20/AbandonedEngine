#include "TuranEngine.h"
#include "TuranAPI/API_FileSystem.h"

/*
		Turan Engine Running Process:
	1) Load Model_Files when Model_Loader_OBJ is created!
	2) For now: Create a Static_Model_Instance from first loaded Model!
	3) For now: Create a Scene and Add every Static_Model_Instance to Scene, no Camera!
	4) Create OGL3_SYS to initialize GLFW and OpenGL and create an offscreen and an onscreen window!
	5) For now: Call GFX->Creation() -> Create a Main_RenderGraph and give its pointer to Scene!
	6) For now: Create resources of Main_RenderGraph of the Scene! This means: Send Models to GPU, Create Draw Passes (Framebuffers etc.) -Only G-Buffer for now!-
	7) 
*/

bool TuranEngine::ShouldApplicationClose = false;
string TuranEngine::ApplicationClose_Reason = "";
GFX_API* TuranEngine::GFX = nullptr;

TuranEngine::TuranEngine() {
	cout << "Turan Engine doesn't work as object, please don't instantinate! Nothing happened!\n";
}

/*Progress:
1) Detect Computer Specs (only Set OpenGL3 for now!)
2) Start GFX_API to display something!
3) Start File_System to find files!
Note: Load resources later by another function!
*/
void TuranEngine::Start_Engine() {
	cout << "Engine is starting!\n";
	SYSTEM_INSPECTOR::Detect_Computer_Specs();
	
	File_System::FileSystem::Start_FileSystem();
}

void TuranEngine::Start_GFX() {
	TuranAPI_ENUMs Best_GFX_API = SYSTEM_INSPECTOR::Return_best_GFX_API();
	switch (Best_GFX_API) {
	case OPENGL3:
		GFX = new OGL3_SYS;
		break;
	default:
		cout << "Best GFX_API isn't supported or returned ENGINE_ENUMs is wrong! GFX_API's value is: << " << Best_GFX_API << "\n";
	}
}

void TuranEngine::Close_Engine(string reason) {
	ApplicationClose_Reason = reason;
	ShouldApplicationClose = true;
}

bool TuranEngine::ShouldEngine_Close() {
	if (!ShouldApplicationClose) {
		//There is no crashing error so far, so check all of the engine to see if there is an close event!
		//If close event, return true to close the app!

		//If there isn't any window, close the application!
		if (GFX->Get_Window_List().size() == 0) {
			ApplicationClose_Reason = "All windows are closed!";
			return true;
		}

		//If there isn't any close event, return false;
		return false;
	}
	else {
		return true;
	}
}

string TuranEngine::Why_Engine_Closed() {
	return ApplicationClose_Reason;
}