#include "GFX_Monitor.h"


void GFX_MONITOR::Set_Physical_Size(unsigned int physical_width, unsigned int physical_height) {
	PHYSICAL_WIDTH = physical_width;
	PHYSICAL_HEIGHT = physical_height;
}

GFX_MONITOR::GFX_MONITOR(void* monitor, string name) : ID(monitor), NAME(name) {

}

string GFX_MONITOR::Get_Monitor_Name() {
	return NAME;
}

//Return WIDTH (x), HEIGHT (y) and REFRESH_RATE (<) as one vec3
vec3 GFX_MONITOR::Get_Monitor_VidMode() {
	return vec3(WIDTH, HEIGHT, REFRESH_RATE);
}