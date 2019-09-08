#include "OGL3_Core.h"
#include "IMGUI/IMGUI_OGL3.h"
using namespace TuranAPI::IMGUI;

OGL3_SYS::OGL3_SYS() {
	//Set static GFX_API variable to created OGL3_SYS, because there will only one GFX_API in run-time
	//And we will use this GFX_API_OBJ to give commands to GFX_API in window callbacks
	GFX_API_OBJ = this;

	Initialization();
	Save_Monitors();

	//Create renderer class and renderer window
	Create_Renderer();

	//Create main window for Turan Engine
	Create_Window("Turan Engine");

	FileSystem = new OGL3_FileSystem;
	FileSystem->Load_GFX_Contents_fromDisk();

	IMGUI::GFX_IMGUI = new IMGUI_OGL3;
	IMGUI::Create_Context(ONSCREEN_Windows[0]->GPU_CONTEXT);
}


	//WINDOW OPERATIONs

void OGL3_SYS::Change_Window_Resolution(GFX_WINDOW* window, unsigned int width, unsigned int height) {
	window->WIDTH = width;
	window->HEIGHT = height;
	glViewport(0, 0, width, height);
}

void OGL3_SYS::Set_Window_Focus(GFX_WINDOW* window, bool is_focused) {
	if (is_focused) {
		for (unsigned int i = 0; i < ONSCREEN_Windows.size(); i++) {
			if (window->Get_Window_GPU_ContentID() == ONSCREEN_Windows[i]->Get_Window_GPU_ContentID()) {
				FOCUSED_WINDOW_index = i;
				return;
			}
		}
		cout << "Error: Intended focus window can't be found! That means there is a bug in the system!\n";
	}
	else {

	}
}

void OGL3_SYS::Close_Window(GFX_WINDOW* window) {
	//First, destroy window and its resources with glfwDestroyWindow
	glfwDestroyWindow((GLFWwindow*)window->GPU_CONTEXT);

	//Then delete it from global GFX_WINDOW vector
	int window_list_index;
	for (int i = 0; i < ONSCREEN_Windows.size(); i++) {
		if (window == ONSCREEN_Windows[i])
			window_list_index = i;
	}
	ONSCREEN_Windows.erase(ONSCREEN_Windows.begin() + window_list_index);
}

void OGL3_SYS::GFX_Error_Callback(int error_code, const char* description) {
	cout << "\n\n\nGLFW ERROR: CODE: " << error_code << endl;
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
	gfx_window->GPU_CONTEXT = window_id;
	glfwSetWindowMonitor(window_id, NULL, 100, 100, gfx_window->WIDTH, gfx_window->HEIGHT, 60);

	//Check and Report if GLFW fails
	if (window_id == NULL) {
		cout << "Error: We failed to create the window: " << name << " because of GLFW!\n";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window_id);
	glfwSwapInterval(1);
	//GLAD is already loaded, so send Quad Mesh to context because we will render the texture given by Renderer in GFX->Refresh_Windows()!
	((OGL3_Renderer*)RENDERER)->Send_Quad_to_GPU();

	ONSCREEN_Windows.push_back(gfx_window);
}

void OGL3_SYS::Create_Renderer() {
	//Create renderer class!
	RENDERER = new OGL3_Renderer;
	RENDERER->Renderer_OBJ = RENDERER;

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

	//Set IMGUI's main renderer to IMGUI_OGL3!
	//All of the IMGUI contexts will use IMGUI's functionality to specify their rendering data!
	//But IMGUI will always use this class to render these datas!
	//So, GFX_IMGUI shouldn't be Window Context specific!
	IMGUI::IMGUI::GFX_IMGUI = new IMGUI_OGL3;
	if (!IMGUI::IMGUI::Check_IMGUI_Version()) {
		cout << "Error: IMGUI version check error!\n";
	}
}

//Delete this function!
void OGL3_SYS::Set_Window_Callbacks() {
	
	for (const GFX_WINDOW* WINDOW : Get_Window_List()) {
		GLFWwindow* window = (GLFWwindow*)(WINDOW->Get_Window_GPU_ContentID());

		glfwMakeContextCurrent(window);
		//glfwSetFramebufferSizeCallback(window, OGL3_SYS::framebuffer_size_callback);
		//glfwSetWindowFocusCallback(window, OGL3_SYS::window_focus_callback);
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		cout << "Callbacks set for window: " << WINDOW->Get_Window_Name() << endl;
	}
	
}


//WINDOW CALLBACKs

//Set true if user uses window, otherwise false
void OGL3_SYS::window_focus_callback(GLFWwindow* window, int focused) {
	GFX_WINDOW* WINDOW = Get_Window_byID(window);
	GFX_API_OBJ->Set_Window_Focus(WINDOW, focused);
}

//Set window and framebuffer size when windowed window is resized
void OGL3_SYS::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	GFX_WINDOW* WINDOW = Get_Window_byID(window);
	GFX_API_OBJ->Change_Window_Resolution(WINDOW, width, height);
	cout << "Callback Width: " << width << endl;
	cout << "Callback Height: " << height << endl;
}

void OGL3_SYS::window_close_callback(GLFWwindow* window) {
	cout << "Window close callback is called!\n";
	GFX_WINDOW* WINDOW = Get_Window_byID(window);
	GFX_API_OBJ->Close_Window(WINDOW);
	cout << "Leaving close callback!\n";
}
void OGL3_SYS::Bind_Window_Context(GFX_WINDOW* window) {
	glfwMakeContextCurrent((GLFWwindow*)window->GPU_CONTEXT);
}


	//RENDERING OPERATIONs
void OGL3_SYS::Bind_Renderer_Context() {
	glfwMakeContextCurrent((GLFWwindow*)RENDERER->Renderer_Context);
}

void OGL3_SYS::New_Frame() {
	for (GFX_RenderGraph* RENDERGRAPH : BOUND_RenderGraphs) {
		RENDERGRAPH->Update_Resources();
	}
	cout << "New frame resources set for bound RenderGraphs!\n";
}

void OGL3_SYS::Render_RenderGraph(GFX_RenderGraph* RenderGraph) {
	RenderGraph->Run_RenderGraph();
}

//Add this code to RenderGraph!
//Each window has Quad Mesh as VAO 1!
void OGL3_SYS::Refresh_Windows() {
	//Display G-Buffer Color Texture on focused window!
	{
		/*
		Check_OpenGL_Errors("Before Refreshing windows!");
		if ((GFX_RenderGraph*)Scene::ALL_SCENEs.size() == 0) {
			cout << "There is no Scene!\n";
			return;
		}
		GFX_RenderGraph* Main_Scene_RenderGraph = (GFX_RenderGraph*)Scene::ALL_SCENEs[0]->Return_RenderGraph();
		if (((OGL3_RenderGraph*)Main_Scene_RenderGraph)->DRAW_PASSes.size() == 0) {
			cout << "There is no Draw Pass!\n";
			return;
		}
		glDisable(GL_DEPTH_TEST);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GFX_Framebuffer* Framebuffer = ((OGL3_RenderGraph*)Main_Scene_RenderGraph)->DRAW_PASSes[0]->Get_Framebuffer();
		//We know that framebuffer's first RT is Color RT
		unsigned int Color_RT;
		Color_RT = Framebuffer->BOUND_RTs[0]->ID;

		GFX_Shader* PostProcessShader = GFX_Shader::Find_Shader_byName("PostProcess_Shader");
		glUseProgram(PostProcessShader->Return_Shader_ID());
		Check_OpenGL_Errors("After Binding Shader!");
		glBindTexture(GL_TEXTURE_2D, Color_RT);
		Check_OpenGL_Errors("After Binding Texture!");
		glBindVertexArray(1);
		Check_OpenGL_Errors("After Binding VAO!");
		glDrawArrays(GL_TRIANGLES, 0, 6);
		Check_OpenGL_Errors("After Refreshing windows!");
		*/
	}
}

void OGL3_SYS::Render_IMGUI() {
	glfwMakeContextCurrent((GLFWwindow*)ONSCREEN_Windows[0]->GPU_CONTEXT);
	IMGUI::IMGUI::Render_Frame();
	IMGUI::IMGUI::Platform_Settings();
}


//Renderer Operations
void OGL3_SYS::Swap_Buffers() {
	for (GFX_WINDOW* window : ONSCREEN_Windows) {
		GLFWwindow* window_id = (GLFWwindow*)window->GPU_CONTEXT;
		glfwSwapBuffers(window_id);
	}
}

//Input (Keyboard-Controller) Operations

//1) Send keys status' from the last frame to the Engine!
//2) Take this frame's key status' from GLFW! But it will be used next frame!
void OGL3_SYS::Take_Inputs() {
	/*
	//For each key, set key pressed status with GLFW check!
	//This sends keys' status from last frame!
	if (true)
	{
		//KEYBOARD INPUT HANDLING

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

		//MOUSE INPUT HANDLING

		switch (Mouse_Controller::CURSOR_MODE) {
		case MOUSE_INPUT_UNLIMITED:
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			break;
		case MOUSE_INPUT_HIDDEN:
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			break;
		case MOUSE_INPUT_NORMAL:
			glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			break;

		default:
			cout << "Unsupported Cursor Mode in Mouse_Controller class!\n";
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
		Mouse_Controller::MOUSE_CURRENT_POSITION = vec2(xpos, ypos);

	}
	*/
	//Take this frame's key inputs!
	glfwPollEvents();
}


//GFX Resource Destroy Operations
void OGL3_SYS::Destroy_GFX_Resources() {
	for (GFX_MONITOR* monitor : CONNECTED_Monitors) {
		delete monitor;
	}
	for (GFX_WINDOW* window : ONSCREEN_Windows) {
		Close_Window(window);
		delete window;
	}
	IMGUI::IMGUI::Destroy_IMGUI_Resources();
	RENDERER->~GFX_Renderer();
	glfwTerminate();
}

void OGL3_SYS::Load_GFX_Files() {
	cout << "ERROR: Define how to load and compile GFX_Files!\n";
	cout << "We are loading after initializing the Renderer, because we want to compile everything at start!\n";
	TuranAPI::Breakpoint();
}



void OGL3_SYS::Show_Texture_on_Window(TuranAPI::File_System::Texture_Resource* TEXTURE) {
	glfwMakeContextCurrent((GLFWwindow*)ONSCREEN_Windows[0]->GPU_CONTEXT);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TEXTURE->GL_ID, 0);

}

void OGL3_SYS::Check_GL_Errors(const string& status) {
	int error = glGetError();
	//If there is a error, first print the status!
	if (error != NULL) {
		cout << "In status: " << status << endl;
	}
	else {
		return;
	}

	//Print the error!
	if (error == GL_INVALID_OPERATION) {
		cout << "Error: GL_INVALID_OPERATION!\n\n";
	}
	if (error == GL_INVALID_ENUM) {
		cout << "Error: GL_INVALID_ENUM!\n\n";
	}
	if (error == GL_INVALID_VALUE) {
		cout << "Error: GL_INVALID_VALUE!\n\n";
	}
	//I'm using NSight for graphic debugging for now, so I don't need this!
	//But if I won't use NSight for a time, I should activate this see real-usage graphic bugs!
	//SLEEP_THREAD(10);
}