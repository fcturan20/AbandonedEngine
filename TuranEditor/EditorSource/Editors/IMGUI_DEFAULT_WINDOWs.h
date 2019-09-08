#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"
#include "TuranAPI/FileSystem/Resource_Types/Resource_Type.h"
class IMGUI_DemoWindow : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	IMGUI_DemoWindow();
	virtual void Run_Window() override;
};

class IMGUI_MetricsWindow : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	IMGUI_MetricsWindow();
	virtual void Run_Window() override;
};


