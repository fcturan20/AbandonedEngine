#include "SYSTEM_INSPECTOR.h"

TuranAPI_ENUMs SYSTEM_INSPECTOR::BEST_GFX_API;

void SYSTEM_INSPECTOR::Detect_Computer_Specs() {
	cout << "Detected computer specs!\n";
	BEST_GFX_API = OPENGL3;
}

TuranAPI_ENUMs SYSTEM_INSPECTOR::Return_best_GFX_API() {
	return BEST_GFX_API;
}