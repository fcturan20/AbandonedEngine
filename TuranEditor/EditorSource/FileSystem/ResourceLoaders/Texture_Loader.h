#pragma once
#include "EditorSource/Editor_Includes.h"


class Texture_Import_Window : public TuranAPI::IMGUI::IMGUI_WINDOW {
	String TEXTURE_PATH = "", OUTPUT_FOLDER = "", OUTPUT_NAME = "";
	//This is used to find which Content List we are importing the texture to! For example GFX_Contents, Engine_Contents, GameContents... 
	TuranAPI::File_System::FileSystem* FILESYSTEM;
public:
	Texture_Import_Window(TuranAPI::File_System::FileSystem* filesystem);
	virtual void Run_Window();
};


class Texture_Loader {
public:
	static TuranAPI::File_System::Resource_Type* Import_Texture(const char* PATH, const char* output_path, String* compilation_status, const bool& flip_vertically = false, const TuranAPI::File_System::Texture_Properties& Properties = TuranAPI::File_System::Texture_Properties());
};

