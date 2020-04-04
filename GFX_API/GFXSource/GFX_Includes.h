#pragma once
#include "TuranAPI/TuranAPI_Core.h"
#include "GFX_ENUMs.h"

#ifdef WINDOWS10_FORENGINE
	#ifdef GFX_BUILD
		#define GFXAPI __declspec(dllexport)
	#else
		#define GFXAPI __declspec(dllimport)
	#endif // GFX_API
#else
	#error GFX_API only support Windows 10 for now!
#endif

namespace GFX_API {
	void GFXAPI Set_SystemPointers(TuranAPI::TAPI_Systems* Systems);
}