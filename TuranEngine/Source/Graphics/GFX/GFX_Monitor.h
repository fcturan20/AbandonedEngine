#pragma once
#include "Includes.h"
#include "GFX_ENUMs.h"


//I have no function to do something on monitor, so this is a storage struct
struct GFX_MONITOR {
	friend class GFX_API;
	friend class OGL3_SYS;
protected:
	void* ID;
	const string NAME;
	unsigned int WIDTH, HEIGHT, COLOR_BITES, REFRESH_RATE;
	int PHYSICAL_WIDTH, PHYSICAL_HEIGHT;	//milimeters
	GFX_ENUM DESKTOP_MODE;


	void Set_Physical_Size(unsigned int physical_width, unsigned int physical_height) {
		PHYSICAL_WIDTH = physical_width;
		PHYSICAL_HEIGHT = physical_height;
	}

public:
	GFX_MONITOR(void* monitor, string name) : ID(monitor), NAME(name) {
		
	}

	string Get_Monitor_Name() {
		return NAME;
	}

	//Return WIDTH (x), HEIGHT (y) and REFRESH_RATE (<) as one vec3
	vec3 Get_Monitor_VidMode() {
		return vec3(WIDTH, HEIGHT, REFRESH_RATE);
	}
};

