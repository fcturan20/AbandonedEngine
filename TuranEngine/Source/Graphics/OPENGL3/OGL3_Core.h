#pragma once
#include <Includes.h>
#include "Engine/Controllers/Mouse_Controller.h"

//OpenGL3 Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphics/GFX/GFX_ENUMs.h"
#include "Graphics/GFX/GFX_Monitor.h"
#include "Graphics/GFX/GFX_Window.h"
#include "Graphics/GFX/GFX_Core.h"

//OpenGL3 related classes
#include "OGL3_ENUMs.h"
#include "OGL3_Shader.h"
#include "OGL3_Renderer_Core.h"

class OGL3_SYS : public GFX_API {
	friend class SYSTEM_INSPECTOR;

	OGL3_SYS() {
		Initialization();
		Save_Monitors();

		//Create renderer class and renderer window
		Create_Renderer();

		//Create main window for Turan Engine
		Create_Window("Turan Engine");

		//Set current context as main window (Turan Engine)!
		glfwMakeContextCurrent((GLFWwindow*)ONSCREEN_Windows[0]->Get_Window_ID());
	}

	virtual void Initialization();
	virtual void Save_Monitors();
	virtual void Create_Renderer();
	static void GFX_Error_Callback(int error_code, const char* description);

public:
	//Window Operations
	virtual void Create_Window(string name);
	virtual void Close_Window(GFX_WINDOW* window);
	virtual void Change_Window_Resolution(GFX_WINDOW* window, unsigned int width, unsigned int height){}
	virtual void Set_Window_Focus(GFX_WINDOW* window, bool is_focused){}

	//Renderer Operations
	virtual void Creation();
	virtual void New_Frame();
	virtual void Refresh_Windows();
	virtual void Swap_Buffers();

	//Input (Keyboard-Controller) Operations
	virtual void Take_Inputs();
	virtual void Set_Mouse_Mode(MOUSE_INPUT_MODE mode);

	//Resource Destroy Operations
	virtual void Destroy_GFX_Resources();

	~OGL3_SYS() {
		Destroy_GFX_Resources();
		glfwTerminate();
	}
};

void OGL3_SYS::GFX_Error_Callback(int error_code, const char* description) {
	cout << "\n\n\nERROR: CODE: " << error_code << endl;
	cout << "Description: " << description << endl;
	this_thread::sleep_for(chrono::seconds(10));
}

void OGL3_SYS::Initialization() {
	//Set error callback to handle all glfw errors (including initialization error)!
	glfwSetErrorCallback(OGL3_SYS::GFX_Error_Callback);

	//Initialize GLFW with OpenGL3
	int status = glfwInit();
	if (!status) {
		cout << "GLFW initialization error!\n";
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void OGL3_SYS::Save_Monitors() {
	int monitor_count;
	GLFWmonitor** monitors = glfwGetMonitors(&monitor_count);
	cout << "Detected monitors count: " << monitor_count << endl;
	for (unsigned int i = 0; i < monitor_count; i++) {
		GLFWmonitor* monitor = monitors[i];

		//Get monitor name provided by OS! It is a driver based name, so it maybe incorrect!
		string monitor_name = glfwGetMonitorName(monitor);
		GFX_MONITOR* gfx_monitor = new GFX_MONITOR(monitor, monitor_name);

		//Get videomode to detect at which resolution the OS is using the monitor
		const GLFWvidmode* monitor_vid_mode = glfwGetVideoMode(monitor);
		gfx_monitor->COLOR_BITES = monitor_vid_mode->blueBits;
		gfx_monitor->WIDTH = monitor_vid_mode->width;
		gfx_monitor->HEIGHT = monitor_vid_mode->height;
		gfx_monitor->REFRESH_RATE = monitor_vid_mode->refreshRate;

		//Get monitor's physical size, developer may want to use it!
		glfwGetMonitorPhysicalSize(monitor, &gfx_monitor->PHYSICAL_WIDTH, &gfx_monitor->PHYSICAL_HEIGHT);

		CONNECTED_Monitors.push_back(gfx_monitor);
	}
}

//Create window in windowed mode, in final production: A window context should be known (Which screen mode, which GUIs to render etc.) and create this window according to it!s
void OGL3_SYS::Create_Window(string name) {
	cout << "Creating Window: " << name << endl;

	//Create window as it will share resources with Renderer Context to get display texture!
	GLFWwindow* window_id = glfwCreateWindow(1280, 720, name.c_str(), NULL, (GLFWwindow*)RENDERER->Renderer_Context);
	GFX_WINDOW* gfx_window = new GFX_WINDOW(1280, 720, GFX_WINDOWED, CONNECTED_Monitors[0], CONNECTED_Monitors[0]->REFRESH_RATE, name, V_SYNC_OFF);
	gfx_window->WINDOW = window_id;
	glfwSetWindowMonitor(window_id, NULL, 0, 0, 1280, 720, 60);

	//Check and Report if GLFW fails
	if (window_id == NULL) {
		cout << "Error: We failed to create the window: " << name << " because of GLFW!\n";
		glfwTerminate();
	}
	
	glfwMakeContextCurrent(window_id);
	glfwSwapInterval(0);
	//GLAD is already loaded, so send Quad Mesh to context because we will render the texture given by Renderer in GFX->Refresh_Windows()!
	((OGL3_Renderer*)RENDERER)->Send_Quad_to_GPU();


	ONSCREEN_Windows.push_back(gfx_window);
}

void OGL3_SYS::Create_Renderer() {
	//Create renderer class!
	RENDERER = new OGL3_Renderer;

	//Create offscreen renderer window to render everything!
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	RENDERER->Renderer_Context = glfwCreateWindow(1920, 1080, "Offscreen_Renderer_Window", 0, 0);
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);

	//Check and Report if GLFW fails
	if (RENDERER->Renderer_Context == NULL) {
		cout << "We failed to create the window because of GLFW" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent((GLFWwindow*)RENDERER->Renderer_Context);
	glfwSwapInterval(0);

	//Check and Report if GLAD fails
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "We failed to create the window because of GLAD" << endl;
	}
}




		//RENDERING OPERATIONs

void OGL3_SYS::Creation() {
	glfwMakeContextCurrent((GLFWwindow*)RENDERER->Renderer_Context);
	//Start creation of Renderer resources (Draw Passes etc.)
	RENDERER->Start_Creation();
	glfwMakeContextCurrent((GLFWwindow*)ONSCREEN_Windows[0]->Get_Window_ID());
}
void OGL3_SYS::New_Frame() {
	GLFWwindow* focused_window = glfwGetCurrentContext();
	glfwMakeContextCurrent((GLFWwindow*)RENDERER->Renderer_Context);
	//Render new frame!
	RENDERER->New_Frame();
	glfwMakeContextCurrent(focused_window);
}

//Each window has Quad Mesh as VAO 1!
void OGL3_SYS::Refresh_Windows() {
	//Display G-Buffer Color Texture on focused window!
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		Check_OpenGL_Errors("Before Refreshing windows!");
		GFX_RenderGraph* Main_Scene_RenderGraph = (GFX_RenderGraph*)Scene::ALL_SCENEs[0]->Return_RenderGraph();
		GFX_Framebuffer* Framebuffer = ((OGL3_RenderGraph*)Main_Scene_RenderGraph)->DRAW_PASSes[0]->Get_Framebuffer();
		//We know that framebuffer's first RT is Color RT
		unsigned int Color_RT = Framebuffer->BOUND_RTs[0]->ID;

		GFX_Shader* PostProcessShader = GFX_Shader::Find_Shader_byName("PostProcess_Shader");
		glUseProgram(PostProcessShader->Return_Shader_ID());
		Check_OpenGL_Errors("After Binding Shader!");
		glBindTexture(GL_TEXTURE_2D, Color_RT);
		Check_OpenGL_Errors("After Binding Texture!");
		glBindVertexArray(1);
		Check_OpenGL_Errors("After Binding VAO!");
		glDrawArrays(GL_TRIANGLES, 0, 6);
		Check_OpenGL_Errors("After Refreshing windows!");
	}
}




void OGL3_SYS::Close_Window(GFX_WINDOW* window) {
	//First, destroy window and its resources with glfwDestroyWindow
	glfwDestroyWindow((GLFWwindow*)window->WINDOW);

	//Then delete it from global GFX_WINDOW vector
	int window_list_index;
	for (int i = 0; i < ONSCREEN_Windows.size(); i++) {
		if (window == ONSCREEN_Windows[i])
			window_list_index = i;
	}
	ONSCREEN_Windows.erase(ONSCREEN_Windows.begin() + window_list_index);

	//If there is no window, close application
	if (ONSCREEN_Windows.size() == 0) {
		cout << "This was last window, so application is closing!\n";
		Destroy_GFX_Resources();
		glfwTerminate();
		ShouldApplication_Close = true;
	}
}


		//Renderer Operations
void OGL3_SYS::Swap_Buffers() {
	for (GFX_WINDOW* window : ONSCREEN_Windows) {
		GLFWwindow* window_id = (GLFWwindow*)window->WINDOW;
		glfwSwapBuffers(window_id);
	}
}

		//Input (Keyboard-Controller) Operations
void OGL3_SYS::Take_Inputs() {
	glfwPollEvents();

	if(!ShouldApplication_Close)
	//For each key, set key pressed status with GLFW check!
	{
		for (KEYBOARD_KEYs key : Keyboard_Controller::Return_ALL_Keys()) {
			if (glfwGetKey(glfwGetCurrentContext(), Convert_Key_to_GLFW_Key(key)) == GLFW_PRESS) {
				Keyboard_Controller::Set_Key_is_Pressed(key, true);
				cout << "Key: " << key << " is pressed!\n";
			}
			//If Key isn't pressed this frame, set it as false because Maybe at previous frame it was pressed!
			else {
				Keyboard_Controller::Set_Key_is_Pressed(key, false);
			}
		}

		for (MOUSE_BUTTONs button : Mouse_Controller::Return_ALL_Buttons()) {
			if (glfwGetMouseButton(glfwGetCurrentContext(), Convert_MouseButton_to_GLFW_Key(button)) == GLFW_PRESS) {
				Mouse_Controller::Set_Button_is_Pressed(button, true);
				cout << "Mouse button: " << button << " is pressed!\n";
			}
			//If Mouse button isn't pressed this frame, set it as false because maybe at previous frame it was pressed!
			else {
				Mouse_Controller::Set_Button_is_Pressed(button, false);
			}
		}

		double xpos, ypos;
		glfwGetCursorPos(glfwGetCurrentContext(), &xpos, &ypos);
		Mouse_Controller::mouse_current_position = vec2(xpos, ypos);
	}
}

//Set mouse mode for current window!
void OGL3_SYS::Set_Mouse_Mode(MOUSE_INPUT_MODE mode) {
	if (mode == MOUSE_INPUT_UNLIMITED) {
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	if (mode == MOUSE_INPUT_HIDDEN) {
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	}
	if (mode == MOUSE_INPUT_NORMAL) {
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

		//GFX Resource Destroy Operations
void OGL3_SYS::Destroy_GFX_Resources() {
	for (GFX_MONITOR* monitor : CONNECTED_Monitors) {
		delete monitor;
	}
	for (GFX_WINDOW* window : ONSCREEN_Windows) {
		delete window;
	}
}