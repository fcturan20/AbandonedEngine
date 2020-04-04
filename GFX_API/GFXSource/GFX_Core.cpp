#include "GFX_Core.h"

#include "Renderer/GFX_APICommands.h"
#include "GFX_FileSystem.h"

namespace GFX_API {

	GFX_Core* GFX_Core::SELF = nullptr;
	GFX_Core::GFX_Core() : ONSCREEN_Windows(LASTUSEDALLOCATOR, 1, 1), CONNECTED_Monitors(LASTUSEDALLOCATOR, 1, 1), RENDERER(nullptr), FOCUSED_WINDOW_index(0), DEVICE_GPUs(LASTUSEDALLOCATOR, 1, 1), GPU_TO_RENDER(nullptr) {
		TuranAPI::LOG_STATUS("GFX Core systems are starting!");

		GFX = this;

		TuranAPI::LOG_STATUS("GFX Core systems are started!");
	}
	//WINDOW OPERATIONs

	const Vector<WINDOW*>* GFX_Core::Get_Window_List() {
		return &SELF->ONSCREEN_Windows;
	}

	MONITOR* GFX_Core::Create_MonitorOBJ(void* monitor, const char* name) { return new MONITOR(monitor, name); TuranAPI::LOG_STATUS("A monitor is added"); }
	WINDOW* GFX_Core::Create_WindowOBJ(unsigned int width, unsigned int height, GFX_ENUM display_mode, MONITOR* display_monitor, unsigned int refresh_rate, const char* window_name, GFX_ENUM v_sync) {
		return new WINDOW(width, height, display_mode, display_monitor, refresh_rate, window_name, v_sync); TuranAPI::LOG_STATUS("Window: ");
	}

	//RENDER OPERATIONs

	//Start to record new frame's render calls, handle current resources and rendergraphs for new frame!
	void GFX_Core::New_Frame() {
		for (unsigned int i = 0; i < SELF->ONSCREEN_Windows.size(); i++) {
			WINDOW* window = SELF->ONSCREEN_Windows[i];
			//APICommander::SELF->Clear_WindowBuffer_Immediately(window, vec3(1));
		}

		SELF->RENDERER->New_Frame();
	}
	//Render the recorded render calls!
	void GFX_Core::Render() { TuranAPI::LOG_NOTCODED("GFX_API::Render() isn't coded!", false); }
	//Swap buffers of all windows to see latest changes of window contents!
	void GFX_Core::Show_ThisFrame_onWindows() {
		TuranAPI::LOG_NOTCODED("GFX_API::Render() isn't coded!", false);
	}


	void Start_GFXDLL(TuranAPI::TAPI_Systems* TAPISystems) {
		TuranAPI::MemoryManagement::TMemoryManager::SELF = &TAPISystems->MemoryManager;
		TuranAPI::IMGUI::IMGUI_WindowManager::SELF = &TAPISystems->IMGUI_WindowSys;
		TuranAPI::Logging::Logger::SELF = &TAPISystems->Log_Sys;
		TuranAPI::File_System::FileSystem::SELF = TAPISystems->FileSys;
	}
}
