#pragma once
#include "TuranAPI/TuranAPI_Core.h"
#include "EngineSource/TuranEngine.h"

namespace TuranEditor {
	class TE_DependentSystems {
		TuranAPI::TAPI_Systems TAPISystems;
		Engine::TuranEngine_Core* EngineSystems;
	public:
		TE_DependentSystems();
	};
}