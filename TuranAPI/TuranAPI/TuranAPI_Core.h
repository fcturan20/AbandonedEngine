#pragma once
#include "API_includes.h"
#include "MemoryManager/MemoryManager_Core.h"
#include "TSTL/TSTL_Core.h"
#include "FileSystem/Profiler/Profiler_Core.h"
#include "FileSystem/Logger/Logger_Core.h"
#include "FileSystem/FileSystem_Core.h"
#include "IMGUI/IMGUI_Core.h"
#include "IMGUI/IMGUI_WINDOW.h"

#include "FileSystem/Resource_Types/GameObjects/GameComponents/GameComponent.h"
#include "FileSystem/Resource_Types/GameObjects/GameComponents/Camera_Component.h"
#include "FileSystem/Resource_Types/GameObjects/GameComponents/StaticModel_Component.h"

#include "FileSystem/Resource_Types/FileList_Resource.h"
#include "FileSystem/Resource_Types/Material_Type_Resource.h"
#include "FileSystem/Resource_Types/Model_Resource.h"
#include "FileSystem/Resource_Types/Resource_Type.h"
#include "FileSystem/Resource_Types/Scene_Resource.h"
#include "FileSystem/Resource_Types/Texture_Resource.h"


namespace TuranAPI {
	class TURANAPI TAPI_Systems {
	public:
		TMemoryManager MemoryManager;
		File_System::FileSystem* FileSys;
		Logging::Logger Log_Sys;
		IMGUI::IMGUI_WindowManager IMGUI_WindowSys;
		TAPI_Systems();
	};
	void TURANAPI Start_TAPI_Systems(TAPI_Systems* InitializedSystems);
}