#include "TuranAPI_Core.h"

namespace TuranAPI {
	TAPI_Systems::TAPI_Systems() : MemoryManager(1024 * 1024 * 100), IMGUI_WindowSys() {

	}
	void Start_TAPI_Systems(TAPI_Systems* InitializedSystems) {
		MemoryManagement::TMemoryManager::SELF = &(InitializedSystems->MemoryManager);
		TuranAPI::File_System::FileSystem::SELF = InitializedSystems->FileSys;
		TuranAPI::Logging::Logger::SELF = &(InitializedSystems->Log_Sys);
		IMGUI::IMGUI_WindowManager::SELF = &(InitializedSystems->IMGUI_WindowSys);
		TuranAPI::LOG_STATUS("TuranAPI DLL got the pointers!\n");
	}
}