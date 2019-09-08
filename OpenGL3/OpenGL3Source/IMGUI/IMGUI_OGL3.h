#pragma once
#include "TuranAPI/API_includes.h"
#include "TuranAPI/API_IMGUI.h"

class IMGUI_OGL3 : public TuranAPI::IMGUI::IMGUI_GFX {
public:
	virtual void Initialize(void* Window_GPU_Context);
	virtual void Render_IMGUI(void* data);
	virtual void GFX_New_Frame();
	virtual void Destroy_IMGUI_GFX_Resources();
	virtual void Set_Platform_Settings();
};