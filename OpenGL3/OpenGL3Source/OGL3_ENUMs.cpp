#include "OGL3_ENUMs.h"

//OpenGL3 Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "TuranAPI/API_includes.h"
using namespace TuranAPI;

int Find_Texture_Attachment_Type(GFX_ENUM attachment) {
	switch (attachment) {
	case GFX_TEXTURE_COLOR0_ATTACHMENT:
		return GL_COLOR_ATTACHMENT0;
	case GFX_TEXTURE_DEPTH_ATTACHMENT:
		return GL_DEPTH_ATTACHMENT;

	default:
		cout << "Error: Intended Texture Attachment isn't supported by OpenGL3 for now\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_Texture_Dimension(TuranAPI_ENUMs dimension) {
	switch (dimension) {
	case API_TEXTURE_2D:
		return GL_TEXTURE_2D;
	default:
		cout << "Error: Intended Texture Dimension isn't supported by OpenGL3 for now\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_Texture_Format(GFX_ENUM format) {
	switch (format) {
	case GFX_COLORTEXTURE_FORMAT:
		return GL_RGBA;
	case GFX_DEPTHTEXTURE_FORMAT:
		return GL_DEPTH_COMPONENT;
	default:
		cout << "Error: Intended Texture Format isn't supported by OpenGL3 for now!\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_RenderTarget_Channel_Type(GFX_ENUM texture_format) {
	switch (texture_format) {
	case GFX_COLORTEXTURE_FORMAT:
		return GL_RGBA;
	case GFX_DEPTHTEXTURE_FORMAT:
		return GL_DEPTH_COMPONENT;
	default:
		cout << "Error: Intended texture format isn't supported by OpenGL3 for now!\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_Texture_Channel_Type(TuranAPI::TuranAPI_ENUMs channel_type) {
	switch (channel_type) {
	case API_TEXTURE_RGB:
		return GL_RGB;
	case API_TEXTURE_RGBA:
		return GL_RGBA;
	default:
		cout << "Error: Intended texture channel type isn't supported by OpenGL3 for now!\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_Texture_Value_Type(TuranAPI_ENUMs value_type) {
	switch (value_type) {
	case VAR_UBYTE8:
		return GL_UNSIGNED_BYTE;
	case VAR_BYTE8:
		return GL_BYTE;
	case VAR_UINT32:
		return GL_UNSIGNED_INT;
	case VAR_INT32:
		return GL_INT;
	case VAR_FLOAT32:
		return GL_FLOAT;
	default:
		cout << "Error: Intended Texture Value Type isn't supported by OpenGL3 for now!\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_Texture_Wrapping(TuranAPI_ENUMs wrapping) {
	switch (wrapping) {
	case API_TEXTURE_REPEAT:
		return GL_REPEAT;
	case API_TEXTURE_MIRRORED_REPEAT:
		return GL_MIRRORED_REPEAT;
	case API_TEXTURE_CLAMP_TO_EDGE:
		return GL_CLAMP_TO_EDGE;
	default:
		cout << "Error: Intended Wrapping Type isn't supported by OpenGL3 for now!\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

int Find_Texture_Mipmap_Filtering(TuranAPI_ENUMs mipmap_filter) {
	switch (mipmap_filter) {
	case API_TEXTURE_LINEAR_FROM_1MIP:
		return GL_LINEAR;
	case API_TEXTURE_LINEAR_FROM_2MIP:
		return GL_LINEAR_MIPMAP_LINEAR;
	case API_TEXTURE_NEAREST_FROM_1MIP:
		return GL_NEAREST;
	case API_TEXTURE_NEAREST_FROM_2MIP:
		return GL_NEAREST_MIPMAP_LINEAR;
	default:
		cout << "Error: Intended Mipmap Filtering Type isn't supported by OpenGL3 for now!\n";
		this_thread::sleep_for(chrono::seconds(5));
		return -1;
	}
}

	//INPUT HANDLING!

/*
KEYBOARD_KEYs ENGINE Convert_Key_to_Engine(int GLFW_Key) {
	switch (GLFW_Key) {
	case GLFW_KEY_W:
		return KEYBOARD_W;
	case GLFW_KEY_S:
		return KEYBOARD_S;
	case GLFW_KEY_A:
		return KEYBOARD_A;
	case GLFW_KEY_D:
		return KEYBOARD_D;
	case GLFW_KEY_KP_2:
		return KEYBOARD_NP_2;
	case GLFW_KEY_KP_4:
		return KEYBOARD_NP_4;
	case GLFW_KEY_KP_6:
		return KEYBOARD_NP_6;
	case GLFW_KEY_KP_8:
		return KEYBOARD_NP_8;
	case GLFW_KEY_C:
		return KEYBOARD_C;

	default:
		"Error: Intended key isn't supported, returns KEYBOARD_A!\n";
		return KEYBOARD_A;
	}
}

int ENGINE Convert_Key_to_GLFW_Key(KEYBOARD_KEYs Keyboard_Key) {
	switch (Keyboard_Key) {
	case KEYBOARD_W:
		return GLFW_KEY_W;
	case KEYBOARD_S:
		return GLFW_KEY_S;
	case KEYBOARD_A:
		return GLFW_KEY_A;
	case KEYBOARD_D:
		return GLFW_KEY_D;
	case KEYBOARD_NP_2:
		return GLFW_KEY_KP_2;
	case KEYBOARD_NP_4:
		return GLFW_KEY_KP_4;
	case KEYBOARD_NP_6:
		return GLFW_KEY_KP_6;
	case KEYBOARD_NP_8:
		return GLFW_KEY_KP_8;
	case KEYBOARD_C:
		return GLFW_KEY_C;

	default:
		cout << "Error: Intended key isn't supported, return GLFW_KEY_A!\n";
		return GLFW_KEY_A;
	}
}


int ENGINE Convert_MouseButton_to_GLFW_Key(MOUSE_BUTTONs Mouse_Button) {
	switch (Mouse_Button) {
	case MOUSE_LEFT_CLICK:
		return GLFW_MOUSE_BUTTON_LEFT;
	case MOUSE_RIGHT_CLICK:
		return GLFW_MOUSE_BUTTON_RIGHT;
	case MOUSE_WHEEL_CLICK:
		return GLFW_MOUSE_BUTTON_MIDDLE;

	default:
		cout << "Error: Intended mouse button isn't supported, return GLFW_MOUSE_BUTTON_1!\n";
		return GLFW_MOUSE_BUTTON_1;
	}
}

*/



int Find_GFX_DepthTest_Mode(GFX_ENUM depth_test) {
	switch (depth_test) {
	case GFX_DEPTH_ALWAYS:
		return GL_ALWAYS;
	case GFX_DEPTH_GEQUAL:
		return GL_GEQUAL;
	case GFX_DEPTH_GREATER:
		return GL_GREATER;
	case GFX_DEPTH_LEQUAL:
		return GL_LEQUAL;
	case GFX_DEPTH_LESS:
		return GL_LESS;
	case GFX_DEPTH_NEVER:
		return GL_NEVER;
	default:
		cout << "Error: Intended Depth Test Mode can't be found! GL_NEVER is returned!\n";
		return GL_NEVER;
	}
}
