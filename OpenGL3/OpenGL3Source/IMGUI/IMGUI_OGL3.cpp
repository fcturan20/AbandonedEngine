#include "IMGUI_OGL3.h"

#include "TuranAPI/IMGUI/Includes/imgui.h"
#include "imgui_impl_glfw.h"
//We are using our own OpenGL loading function in OGL3_SYS
#define IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


//Give GLFW callbacks and OpenGL3 to IMGUI!
//This is to make IMGUI manage all of the inputs and render itself!
void IMGUI_OGL3::Initialize(void* gpu_window_context) {
	ImGui_ImplOpenGL3_Init("#version 330");
	ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)gpu_window_context, true);
	cout << "IMGUI's GFX part is initialized successfully!\n";
}

void IMGUI_OGL3::Render_IMGUI(void* data) {
	ImGui_ImplOpenGL3_RenderDrawData((ImDrawData*)data);
}

void IMGUI_OGL3::GFX_New_Frame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
}

void IMGUI_OGL3::Destroy_IMGUI_GFX_Resources() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
}

void IMGUI_OGL3::Set_Platform_Settings() {
	auto io = ImGui::GetIO();
	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

}