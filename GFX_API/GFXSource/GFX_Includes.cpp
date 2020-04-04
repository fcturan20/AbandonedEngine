#include "GFX_Includes.h"

namespace GFX_API {
	void Set_SystemPointers(TuranAPI::TAPI_Systems* Systems) {
		TuranAPI::MemoryManagement::TMemoryManager::SELF = &Systems->MemoryManager;
		TuranAPI::File_System::FileSystem::SELF = Systems->FileSys;
		TuranAPI::IMGUI::IMGUI_WindowManager::SELF = &Systems->IMGUI_WindowSys;
		TuranAPI::Logging::Logger::SELF = &Systems->Log_Sys;
	}
}