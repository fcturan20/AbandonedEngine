#include "Editor_Includes.h"

using namespace TuranEditor;

TE_DependentSystems::TE_DependentSystems() {
	TuranAPI::Start_TAPI_Systems(&TAPISystems);
	TMemoryManager::SELF = &TAPISystems.MemoryManager;
	TuranAPI::Logging::Logger::SELF = &TAPISystems.Log_Sys;
	TuranAPI::IMGUI::IMGUI_WindowManager::SELF = &TAPISystems.IMGUI_WindowSys;
	TuranAPI::LOG_STATUS("Systems are started, static data handling begins!\n");

	EngineSystems = Engine::Start_EngineDLL(&TAPISystems);
	Engine::TuranEngine_Core::SELF = EngineSystems;
	GFX = EngineSystems->Get_GFXSystems();
}