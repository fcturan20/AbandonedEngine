#include "TuranEngine.h"
#include <windows.h>

#include "GFXSource/GFX_Core.h"
#include "VulkanSource/Vulkan_Core.h"

namespace Engine {
	BOOL WINAPI ConsoleHandler(DWORD CEvent)
	{
		if (CEvent == CTRL_CLOSE_EVENT)
		{
			std::cout << "Naber?";
			if (TuranEngine->GetEngineClosing_Callback() != nullptr) {
				while (TuranEngine->GetEngineClosing_Callback()()) {

				}
			}
			else {
				std::cout << "Function pointer is nullptr!";
			}
			TuranEngine->Close_Engine("Console Application is closed!");
			TuranAPI::Breakpoint();
		}
		return TRUE;
	}


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
	TuranEngine_Core* TuranEngine_Core::SELF = nullptr;

	TuranEngine_Core::TuranEngine_Core(TuranAPI::TAPI_Systems* TAPISystems) {
		TuranEngine_Core::SELF = this;
		Start_GFX(TAPISystems);
		TuranAPI::LOG_STATUS("GFX systems finished starting for the TuranEngine");
		TuranAPI::WRITE_LOGs_toFILEs();
		while (!ShouldEngine_Close()) {
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
			GFX->Create_Window("First Custom Window");
			std::cout << "FRAME HAS ENDED!\n";
		}
		TuranAPI::LOG_STATUS(Why_Engine_Closed());
		TuranAPI::WRITE_LOGs_toFILEs();
		std::cout << "Application is closing in 1 seconds!\n";
		SLEEP_THREAD(1);

	}

	/*Progress:
	1) Detect Computer Specs (only Set OpenGL3 for now!)
	2) Start GFX_API to display something!
	3) Start File_System to find files!
	Note: Load resources later by another function!
	*/
	void TuranEngine_Core::Start_Engine() {
		TuranAPI::LOG_STATUS("Engine is starting!");
		TuranAPI::LOG_STATUS("Started the engine!");
	}

	void TuranEngine_Core::Start_GFX(TuranAPI::TAPI_Systems* TAPI_Systems) {
		GFX = Vulkan::Start_VulkanSystems(TAPI_Systems);
	}

	GFX_API::GFX_Core* TuranEngine_Core::Get_GFXSystems() {
		return GFX;
	}

	void TuranEngine_Core::Close_Engine(const char* reason) {
		SELF->ApplicationClose_Reason = reason;
		SELF->ShouldApplicationClose = true;
	}

	//In final product, Input Handling will use OS functionality, not GLFW!
	void TuranEngine_Core::Take_Inputs() {
		GFX_API::GFX_Core::SELF->Take_Inputs();
		if (GFX_API::GFX_Core::SELF->Get_Window_List()->size() == 0) {
			SELF->ShouldApplicationClose = true;
			SELF->ApplicationClose_Reason = "GFX_API is closed because of no window is active!\n";
		}
	}

	void Engine_Closing_Operations();

	//Check if something called to Close_Engine() or check predefined circumstances!
	bool TuranEngine_Core::ShouldEngine_Close() {
		if (!ShouldApplicationClose) {
			//There is no crashing error so far, so check all of the engine to see if there is an close event!
			//If close event, return true to close the app!
			/*
			if (!TuranAPI::IMGUI::IMGUI::SELF->Is_IMGUI_Open) {
				SELF->ShouldApplicationClose = true;
				SELF->ApplicationClose_Reason = "IMGUI main window is closed!";
				Engine_Closing_Operations();
				return true;
			}*/

			//If there isn't any window, close the application!
			if (GFX_API::GFX_Core::SELF->Get_Window_List()->size() == 0) {
				SELF->ApplicationClose_Reason = "All windows are closed!";
				Engine_Closing_Operations();
				return true;
			}

			//If there isn't any close event, return false;
			return false;
		}
		else {
			Engine_Closing_Operations();
			return true;
		}
	}

	const char* TuranEngine_Core::Why_Engine_Closed() {
		return ApplicationClose_Reason;
	}

	void TuranEngine_Core::SetEngineClosing_Callback(ShouldEngineWait_Callback Callback_Function) {
		Waiting_inClose_Callback = Callback_Function;
#ifdef TURAN_DEBUGGING
		if (SetConsoleCtrlHandler((PHANDLER_ROUTINE)ConsoleHandler, TRUE) == FALSE)
		{
			TuranAPI::LOG_ERROR("Closing callback failed to set on Console Application!");
		}
#endif
	}

	ShouldEngineWait_Callback TuranEngine_Core::GetEngineClosing_Callback() {
		return Waiting_inClose_Callback;
	}

	void Engine_Closing_Operations() {
		//IMGUI, GLFW and GLAD resources are destroyed by GFX!
		GFX->Destroy_GFX_Resources();

		TuranAPI::LOG_STATUS("Engine closing operations are done!");
		TuranAPI::WRITE_LOGs_toFILEs();
	}


	TuranEngine_Core* Start_EngineDLL(TuranAPI::TAPI_Systems* TAPISystems) {
		std::cout << "TuranEngine is being started!\n";
		TMemoryManager::SELF = &TAPISystems->MemoryManager;
		TuranAPI::Logging::Logger::SELF = &TAPISystems->Log_Sys;
		TuranAPI::IMGUI::IMGUI_WindowManager::SELF = &TAPISystems->IMGUI_WindowSys;
		TuranAPI::File_System::FileSystem::SELF = TAPISystems->FileSys;
		TuranAPI::LOG_STATUS("TuranAPI systems are set for the TuranEngine");
		return new TuranEngine_Core(TAPISystems);
	}
}