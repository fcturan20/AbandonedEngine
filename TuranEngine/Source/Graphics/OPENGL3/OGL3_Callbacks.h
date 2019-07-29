/*	This header is included to project after SYSTEM_INSPECTOR.h, because I couldn't find a way to access GFX in callbacks
1)	This header includes callbacks of OpenGL 3




*/



#pragma once
#include "Includes.h"
#include "Engine/Controllers/Mouse_Controller.h"
#include "Graphics/SYSTEM_INSPECTOR.h"

//OpenGL 3.0 Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>


class OGL3_CALLBACKS {
private:

	//Set true if user uses window, otherwise false
	static void window_focus_callback(GLFWwindow* window, int focused) {
		GFX_WINDOW* WINDOW = GFX->Get_Window_byID(window);
		GFX->Set_Window_Focus(WINDOW, focused);
	}

	//Set window and framebuffer size when windowed window is resized
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		GFX_WINDOW* WINDOW = GFX->Get_Window_byID(window);
		GFX->Change_Window_Resolution(WINDOW, width, height);
		cout << "Callback Width: " << width << endl;
		cout << "Callback Height: " << height << endl;
	}

	static void window_close_callback(GLFWwindow* window) {
		cout << "Window close callback is called!\n";
		GFX_WINDOW* WINDOW = GFX->Get_Window_byID(window);
		GFX->Close_Window(WINDOW);
		//If there is a GLFW window!
		if (!ShouldApplication_Close) {
			Set_Callbacks();
		}
		cout << "Leaving close callback!\n";
	}

public:
	OGL3_CALLBACKS() {
		Set_Callbacks();
	}

	static void Set_Callbacks() {
		for (const GFX_WINDOW* WINDOW : GFX->Get_Window_List()) {
			GLFWwindow* window = (GLFWwindow*)(WINDOW->Get_Window_ID());

			glfwMakeContextCurrent(window);
			glfwSetFramebufferSizeCallback(window, OGL3_CALLBACKS::framebuffer_size_callback);
			glfwSetWindowFocusCallback(window, OGL3_CALLBACKS::window_focus_callback);
			glfwSetWindowCloseCallback(window, OGL3_CALLBACKS::window_close_callback);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			cout << "Callbacks set for window: " << WINDOW->Get_Window_Name() << endl;
		}
	}
};

OGL3_CALLBACKS OGL3_CALLBACK_OBJ;