#pragma once
#include "Engine_Includes.h"
#include "GFXSource/GFX_Core.h"

class ENGINE SYSTEM_INSPECTOR {
	//Some hardware, software and driver related variables
	//For example, I want to return OpenGL3 as best GFX API option! Because we only have this option for now!
	static TuranAPI::TuranAPI_ENUMs BEST_GFX_API;

public:
	//For now, just set OPENGL3 as best GFX_API!
	static void Detect_Computer_Specs();
	static GFX_API* Create_Best_GFX_API();
};