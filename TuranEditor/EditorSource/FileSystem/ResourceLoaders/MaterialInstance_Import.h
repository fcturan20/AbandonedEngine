#pragma once
#include "EditorSource/Editor_Includes.h"
#include "TuranAPI/IMGUI/IMGUI_WINDOW.h"
#include "TuranAPI/API_FileSystem.h"

class MaterialInstance_ImportWindow : public TuranAPI::IMGUI::IMGUI_WINDOW {
	TuranAPI::File_System::Material_Type_Resource* selected_materialtype = TuranAPI::File_System::Material_Type_Resource::ALL_MATERIAL_TYPEs[0];
	string OUTPUT_FOLDER, OUTPUT_NAME;
	TuranAPI::File_System::FileList_Resource* FILELIST;
public:
	MaterialInstance_ImportWindow(TuranAPI::File_System::FileList_Resource* filelist);
	virtual void Run_Window() override;
};

