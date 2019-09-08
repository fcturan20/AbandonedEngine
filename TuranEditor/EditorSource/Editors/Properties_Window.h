#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"
#include "TuranAPI/FileSystem/Resource_Types/Resource_Type.h"
#include "TuranAPI/FileSystem/Resource_Types/GameObjects/GameComponents/GameComponent.h"

class ResourceProperties_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
public:
	TuranAPI::File_System::Resource_Type* RESOURCE = nullptr;

	ResourceProperties_Window(TuranAPI::File_System::Resource_Type* resource);
	virtual void Run_Window();
};

class GameComponentProperties_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
	TuranAPI::Game_Object::GameComponent* GAMECOMPONENT;
public:
	GameComponentProperties_Window(TuranAPI::Game_Object::GameComponent* gamecomponent);
	virtual void Run_Window() override;
};