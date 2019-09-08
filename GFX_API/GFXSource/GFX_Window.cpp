#include "GFX_Window.h"

GFX_WINDOW::GFX_WINDOW(unsigned int width, unsigned int height, GFX_ENUM display_mode, GFX_MONITOR* display_monitor, unsigned int refresh_rate, string window_name, GFX_ENUM v_sync)
	: WIDTH(width), HEIGHT(height), DISPLAY_MODE(display_mode), REFRESH_RATE(refresh_rate), DISPLAY_MONITOR(display_monitor), WINDOW_NAME(window_name), VSYNC_MODE(v_sync)
{}


string GFX_WINDOW::Get_Window_Name() const {
	return WINDOW_NAME;
}

//Return WIDTH (x), HEIGHT (y) and REFRESH_RATE (<) as one vec3
vec3 GFX_WINDOW::Get_Window_Mode() {
	return vec3(WIDTH, HEIGHT, REFRESH_RATE);
}

//	1) Change the window's display mode (Fullscreen, Windowed, Borderless Window etc.)
//	2) Or change to intended refresh rate or monitor
//	3) No resolution changing in this function, window's active resolution is used
void GFX_WINDOW::Change_DisplayMode(GFX_ENUM display_mode, const GFX_MONITOR* display_monitor, unsigned int refresh_rate) {}

void GFX_WINDOW::Set_Focus(bool focus_active) {
	cout << "Error: Set focus isn't coded, don't use it!\n";
}

//Settings of window
void GFX_WINDOW::Window_Settings(GFX_ENUM vsync_type, bool window_resizable) {}

void* GFX_WINDOW::Get_Window_GPU_ContentID() const {
	return GPU_CONTEXT;
}
