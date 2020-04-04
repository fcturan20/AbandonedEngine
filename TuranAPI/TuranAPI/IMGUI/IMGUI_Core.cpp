#include "IMGUI_Core.h"
using namespace TuranAPI::IMGUI;

#include "Includes/imgui.h"
#include "Includes/imgui_stdlib.h"

#include "TuranAPI/FileSystem/Resource_Types/Texture_Resource.h"

IMGUI* IMGUI::SELF = nullptr;
bool IMGUI::Check_IMGUI_Version() {
	//Check version here, I don't care here for now!
	return IMGUI_CHECKVERSION();
}

void* IMGUI::Create_Context(void* gpu_window_context) {
	//Create Context here!
	void* Context = ImGui::CreateContext();
	if (Context == nullptr) {
		std::cout << "Error: Context is nullptr after creation!\n";
	}

	//Set Input Handling settings here! 
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


	//Set color style to dark by default for now!
	ImGui::StyleColorsDark();

	/*
	//Set context's GFX_API settings!
	if (GFX_IMGUI == nullptr) {
		std::cout << "GFX_IMGUI isn't initialized, initializing failed for IMGUI!\n";
		return nullptr;
	}
	GFX_IMGUI->Initialize(gpu_window_context);*/
	return Context;
}

void IMGUI::Set_as_MainViewport() {
	ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
	ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
}

void IMGUI::Set_Current_Context(void* context) {
	ImGui::SetCurrentContext((ImGuiContext*)context);
}

void IMGUI::Destroy_IMGUI_Resources() {
	std::cout << "IMGUI resources are being destroyed!\n";
	//GFX_IMGUI->Destroy_IMGUI_GFX_Resources();
	ImGui::DestroyContext();
	//Is_IMGUI_Open = false;
}

bool IMGUI::Show_DemoWindow() {
	bool x = true;
	ImGui::ShowDemoWindow(&x);
	return x;
}

bool IMGUI::Show_MetricsWindow() {
	bool x = true;
	ImGui::ShowMetricsWindow(&x);
	return x;
}

	//IMGUI FUNCTIONALITY!

void IMGUI::New_Frame() {
	//GFX_IMGUI->GFX_New_Frame();
	ImGui::NewFrame();
}

void IMGUI::Render_Frame() {
	ImGui::Render();
	//GFX_IMGUI->Render_IMGUI(ImGui::GetDrawData());
}

void IMGUI::Platform_Settings() {
	//GFX_IMGUI->Set_Platform_Settings();
}

bool IMGUI::Create_Window(const char* title, bool &should_close, const bool& has_menubar) {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= (has_menubar ? ImGuiWindowFlags_MenuBar : 0);
	return ImGui::Begin(title, &should_close, window_flags);
}

void IMGUI::End_Window() {
	ImGui::End();
}

void IMGUI::Text(const char* text) {
	ImGui::Text(text);
}

bool IMGUI::Button(const char* button_name) {
	return ImGui::Button(button_name);
}

bool IMGUI::Checkbox(const char* name, bool* variable) {
	return ImGui::Checkbox(name, variable);
}

bool IMGUI::Input_Text(const char* name, String* text) {
	const char* text_cstr = *text;
	std::string str(text_cstr);
	if (ImGui::InputText(name, &str, ImGuiInputTextFlags_EnterReturnsTrue)) {
		*text = str.c_str();
		return true;
	}
	return false;
}

bool IMGUI::Begin_Menubar() {
	return ImGui::BeginMenuBar();
}

void IMGUI::End_Menubar() {
	ImGui::EndMenuBar();
}

bool IMGUI::Begin_Menu(const char* name) {
	return ImGui::BeginMenu(name);
}

void IMGUI::End_Menu() {
	ImGui::EndMenu();
}

bool IMGUI::Menu_Item(const char* name, const char* shortcut) {
	return ImGui::MenuItem(name, shortcut);
}

void IMGUI::Paragraph_Text(const char* name, const char* text) {
	std::cout << "Nothing functional for now in Paragraph_Text!\n";
	std::this_thread::sleep_for(std::chrono::seconds(5));
}

bool IMGUI::Input_Paragraph_Text(const char* name, String* text) {
	const char* text_cstr = *text;
	std::string str(text_cstr);
	if (ImGui::InputTextMultiline(name, &str, ImVec2(0,0), ImGuiInputTextFlags_EnterReturnsTrue)) {
		*text = str.c_str();
		return true;
	}
	return false;
}

//Puts the next item to the same line with last created item
//Use between after last item's end - before next item's begin!
void IMGUI::Same_Line() {
	ImGui::SameLine();
}

bool IMGUI::Begin_Tree(const char* name) {
	return ImGui::TreeNode(name);
}

void IMGUI::End_Tree() {
	ImGui::TreePop();
}

bool IMGUI::SelectList_OneLine(const char* name, std::size_t* selected_index, const Vector<String>* item_names) {
	bool is_new_item_selected = false;
	const String& preview_str = (*item_names)[*selected_index];
	if (ImGui::BeginCombo(name, preview_str.c_str()))	// The second parameter is the index of the label previewed before opening the combo.
	{
		for (std::size_t n = 0; n < item_names->size(); n++)
		{
			String item_name = (*item_names)[n];
			bool is_selected = (*selected_index == n);
			if (ImGui::Selectable((*item_names)[n], is_selected)) {
				*selected_index = n;
				is_new_item_selected = true;
			}
		}
		ImGui::EndCombo();
	}
	return is_new_item_selected;
}
bool IMGUI::SelectList_OneLine(const char* name, std::size_t* selected_index, const Vector<const char*>* item_names) {
	bool is_new_item_selected = false;
	const char* preview_str = (*item_names)[*selected_index];
	if (ImGui::BeginCombo(name, preview_str))	// The second parameter is the index of the label previewed before opening the combo.
	{
		for (std::size_t n = 0; n < item_names->size(); n++)
		{
			String item_name = (*item_names)[n];
			bool is_selected = (*selected_index == n);
			if (ImGui::Selectable((*item_names)[n], is_selected)) {
				*selected_index = n;
				is_new_item_selected = true;
			}
		}
		ImGui::EndCombo();
	}
	return is_new_item_selected;
}

//If selected, argument "is_selected" is set to its opposite!
void IMGUI::Selectable(const char* name, bool* is_selected){
	ImGui::Selectable(name, is_selected);
}

bool IMGUI::Selectable_ListBox(const char* name, int* selected_index, Vector<String>* item_names) {
	int already_selected_index = *selected_index;
	bool is_new_selected = false;
	if (ImGui::ListBoxHeader(name)) {
		for (unsigned int i = 0; i < item_names->size(); i++) {
			bool is_selected = false;
			String item_name = (*item_names)[i];
			Selectable(item_name, &is_selected);
			if (is_selected && (already_selected_index != i)) {
				*selected_index = i;
				is_new_selected = true;
			}
		}

		ImGui::ListBoxFooter();
	}
	return is_new_selected;
}

void IMGUI::CheckListBox(const char* name, Vector<bool>* items_status, Vector<String>* item_names) {
	if (ImGui::ListBoxHeader(name)) {
		for (unsigned int i = 0; i < item_names->size(); i++) {
			std::cout << "Current Index: " << i << std::endl;
			bool x = (*items_status)[i];
			Checkbox((*item_names)[i], &x);
			((*items_status)[i]) = x;
		}
		ImGui::ListBoxFooter();
	}
}

void IMGUI::Display_Texture(void* TEXTURE_GL_ID, const unsigned int& Display_WIDTH, const unsigned int& Display_HEIGHT, bool should_Flip_Vertically) {
	unsigned int data = *(unsigned int*)TEXTURE_GL_ID;
	if (should_Flip_Vertically) {
		ImGui::Image((void*)(intptr_t)data, ImVec2(Display_WIDTH, Display_HEIGHT), ImVec2(0, 1), ImVec2(1, 0));
	}
	else {
		ImGui::Image((void*)(intptr_t)data, ImVec2(Display_WIDTH, Display_HEIGHT));
	}
}


bool IMGUI::Slider_Int(const char* name, int* data, int min, int max) { return ImGui::SliderInt(name, data, min, max); }
bool IMGUI::Slider_Float(const char* name, float* data, float min, float max) { return ImGui::SliderFloat(name, data, min, max); }
bool IMGUI::Slider_Vec2(const char* name, vec2* data, float min, float max) { return ImGui::SliderFloat2(name, (float*)data, min, max); }
bool IMGUI::Slider_Vec3(const char* name, vec3* data, float min, float max) { return ImGui::SliderFloat3(name, (float*)data, min, max); }
bool IMGUI::Slider_Vec4(const char* name, vec4* data, float min, float max) { return ImGui::SliderFloat4(name, (float*)data, min, max); }