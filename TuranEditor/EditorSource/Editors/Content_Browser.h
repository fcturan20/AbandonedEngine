#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"


class GameContent_Browser : public TuranAPI::IMGUI::IMGUI_WINDOW{
	Vector<bool> GameContentList_CheckList;
	bool GameContent_EditMode = false;
public:
	GameContent_Browser();
	virtual void Run_Window();
};

class GFX_Content_Browser : public TuranAPI::IMGUI::IMGUI_WINDOW {
	Vector<bool> GFXContentList_CheckList;
	bool GFXContent_EditMode = false;
public:
	GFX_Content_Browser();
	virtual void Run_Window();
};