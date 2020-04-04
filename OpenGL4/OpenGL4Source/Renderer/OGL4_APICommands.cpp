#include "OGL4_APICommands.h"

namespace OpenGL4 {
	void APICommander::Swap_WindowBuffers_Immediately(GFX_API::WINDOW* window) {
		GLFWwindow* Window_Context = (GLFWwindow*)GFX_API::GFX_Core::Get_Window_EditableGLSTRUCT(window);
		glfwSwapBuffers(Window_Context);
		#ifdef TURAN_DEBUGGING
			TuranAPI::LOG_STATUS("Window: " + window->Get_Window_Name() + "'s back-front buffers is swapped!");
		#endif
	}

	void APICommander::Clear_WindowBuffer_Immediately(GFX_API::WINDOW* window, vec3 Clear_Color) {
		GLFWwindow* Window_Context = (GLFWwindow*)GFX_API::GFX_Core::Get_Window_EditableGLSTRUCT(window);
		glfwMakeContextCurrent(Window_Context);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(Clear_Color.x, Clear_Color.y, Clear_Color.z, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
}