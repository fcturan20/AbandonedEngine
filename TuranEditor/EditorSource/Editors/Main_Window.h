#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"


class Main_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	Main_Window();
	virtual void Run_Window();
};

