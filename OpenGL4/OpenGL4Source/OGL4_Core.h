#pragma once
#include "OGL4_ENUMs.h"
#include "Renderer/OGL4_Renderer_Core.h"

namespace OpenGL4 {
	class OGL4_API OpenGL4_Core : public GFX_API::GFX_Core {
		friend class TuranEngine;
		friend class SYSTEM_INSPECTOR;

		OpenGL4_Core();

		virtual void Initialization() override;
		virtual void Check_Computer_Specs() override;
		virtual void Save_Monitors() override;
		virtual void Create_Renderer() override;
		static void GFX_Error_Callback(int error_code, const char* description);
		static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

	public:
		//Window Operations
		virtual void Create_Window(string name) override;
		virtual void Close_Window(GFX_API::WINDOW* window) override;
		virtual void Change_Window_Resolution(GFX_API::WINDOW* window, unsigned int width, unsigned int height) override;
		virtual void Set_Window_Focus(GFX_API::WINDOW* window, bool is_focused) override;
		virtual void Bind_Window_Context(GFX_API::WINDOW* window) override;

		//Window Callbacks
		static void window_focus_callback(GLFWwindow* window, int focused);
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
		static void window_close_callback(GLFWwindow* window);

		//Renderer Operations
		virtual void Render_IMGUI() override;
		static void Show_Texture_on_Window(TuranAPI::File_System::Texture_Resource* TEXTURE);
		static void Check_GL_Errors(const string& status);
		virtual void Load_GFX_Files() override;

		//Input (Keyboard-Controller) Operations
		virtual void Take_Inputs() override;

		//Resource Destroy Operations
		virtual void Destroy_GFX_Resources() override;
	};
}