#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"


class Status_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	Status_Window(const char* error);
	virtual void Run_Window();

	String STATUS;
};

