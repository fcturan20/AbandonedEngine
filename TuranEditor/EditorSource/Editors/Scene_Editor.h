#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"
#include "TuranAPI/FileSystem/Resource_Types/Resource_Type.h"
#include "TuranAPI/FileSystem/Resource_Types/FileList_Resource.h"

class Scene_Editor : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	Scene_Editor();
	virtual void Run_Window() override;
};

class Scene_Create_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
	string Scene_NAME, Scene_Folder;
	TuranAPI::File_System::FileList_Resource* FILE_LIST;


public:
	Scene_Create_Window(TuranAPI::File_System::FileList_Resource* filelist);
	virtual void Run_Window() override;
};