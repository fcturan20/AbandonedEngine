#pragma once
#include <Includes.h>

#include "GRAPHICS_HEADER.h"

class SYSTEM_INSPECTOR {
	GFX_API* GFX;

public:
	GFX_API* Get_GFX() {
		return GFX;
	}

	SYSTEM_INSPECTOR() {
		GFX = new OGL3_SYS;
	}
};

//Please don't use this, because class isn't coded yet!
SYSTEM_INSPECTOR SYSTEM_DETECTOR;


GFX_API* GFX{ SYSTEM_DETECTOR.Get_GFX() };

#include "OPENGL3/OGL3_Callbacks.h"