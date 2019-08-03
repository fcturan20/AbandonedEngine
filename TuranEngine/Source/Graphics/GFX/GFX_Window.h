#pragma once
#include "Includes.h"

#include "GFX_ENUMs.h"
#include "GFX_Monitor.h"


//Note: Window ID created by GFX API specific library stored as void* WINDOW
//If you want to access it, you want to access it with equal library class
//Window resolution is independent from render resolution
//After rendering has done, render resolution
class GFX_WINDOW {
private:
	friend class OGL3_SYS;

	unsigned int WIDTH, HEIGHT, REFRESH_RATE;
	GFX_MONITOR* DISPLAY_MONITOR;
	GFX_ENUM DISPLAY_MODE;
	string WINDOW_NAME;
	GFX_ENUM VSYNC_MODE;
	void* WINDOW;

	GFX_WINDOW(unsigned int width, unsigned int height, GFX_ENUM display_mode, GFX_MONITOR* display_monitor, unsigned int refresh_rate, string window_name, GFX_ENUM v_sync)
		: WIDTH(width), HEIGHT(height), DISPLAY_MODE(display_mode), REFRESH_RATE(refresh_rate), DISPLAY_MONITOR(display_monitor), WINDOW_NAME(window_name), VSYNC_MODE(v_sync)
	{}

public:


	string Get_Window_Name() const {
		return WINDOW_NAME;
	}

	//Return WIDTH (x), HEIGHT (y) and REFRESH_RATE (<) as one vec3
	vec3 Get_Window_Mode() {
		return vec3(WIDTH, HEIGHT, REFRESH_RATE);
	}

	//	1) Change the window's display mode (Fullscreen, Windowed, Borderless Window etc.)
	//	2) Or change to intended refresh rate or monitor
	//	3) No resolution changing in this function, window's active resolution is used
	void Change_DisplayMode(GFX_ENUM display_mode, const GFX_MONITOR* display_monitor, unsigned int refresh_rate) {}

	void Set_Focus(bool focus_active) {
		cout << "Error: Set focus isn't coded, don't use it!\n";
	}
	
	//Settings of window
	void Window_Settings(GFX_ENUM vsync_type, bool window_resizable) {}

	void* Get_Window_ID() const {
		return WINDOW;
	}


};
