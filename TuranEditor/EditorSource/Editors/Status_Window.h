#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"


class Status_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	Status_Window(string error);
	virtual void Run_Window();

	string STATUS;
};

