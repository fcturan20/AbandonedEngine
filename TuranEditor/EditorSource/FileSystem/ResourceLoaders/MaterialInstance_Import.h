#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"

class MaterialInstance_CreationWindow : public TuranAPI::IMGUI::IMGUI_WINDOW {
	TuranAPI::File_System::Material_Type_Resource* selected_materialtype = TuranAPI::File_System::Material_Type_Resource::ALL_MATERIALTYPEs[0];
	String OUTPUT_FOLDER, OUTPUT_NAME;
	TuranAPI::File_System::FileSystem* FILESYSTEM;
public:
	MaterialInstance_CreationWindow(TuranAPI::File_System::FileSystem* filesystem);
	virtual void Run_Window() override;
};

