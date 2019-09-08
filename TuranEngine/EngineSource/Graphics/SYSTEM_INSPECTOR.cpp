#include "SYSTEM_INSPECTOR.h"
#include "OpenGL3Source/OGL3_Core.h"

TuranAPI::TuranAPI_ENUMs SYSTEM_INSPECTOR::BEST_GFX_API;

void SYSTEM_INSPECTOR::Detect_Computer_Specs() {
	BEST_GFX_API = TuranAPI::OPENGL3;
}

GFX_API* SYSTEM_INSPECTOR::Create_Best_GFX_API() {
	return new OGL3_SYS;
}