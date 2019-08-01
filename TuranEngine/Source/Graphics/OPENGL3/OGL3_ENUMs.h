#pragma once
#include "Includes.h"

#include "Engine/Controllers/Keyboard_Controller.h"
#include "Engine/Controllers/Controller_Center.h"

#include "Graphics/GFX/GFX_ENUMs.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


int Find_Texture_Attachment_Type(GFX_ENUM attachment) {
	switch (attachment) {
	case GFX_TEXTURE_COLOR0_ATTACHMENT:
		return GL_COLOR_ATTACHMENT0;
	case GFX_TEXTURE_DEPTH_ATTACHMENT:
		return GL_DEPTH_ATTACHMENT;

	default:
		cout << "Error: Intended Texture Attachment isn't supported for now\n";
		return NULL;
	}
}

int Find_Texture_Dimension(GFX_ENUM dimension) {
	switch (dimension) {
	case GFX_TEXTURE_2D:
		return GL_TEXTURE_2D;

	default:
		cout << "Error: Intended Texture Dimension isn't supported for now\n";
		return NULL;
	}
}

int Find_Texture_Format(GFX_ENUM format) {
	switch (format) {
	case GFX_COLORTEXTURE_FORMAT:
		return GL_RGB;
	case GFX_DEPTHTEXTURE_FORMAT:
		return GL_DEPTH_COMPONENT;

	default:
		cout << "Error: Intended Texture Format isn't supported for now!\n";
		return NULL;
	}
}

int Find_Texture_Channel_Type(GFX_ENUM texture_format) {
	switch (texture_format) {
	case GFX_COLORTEXTURE_FORMAT:
		return GL_RGB;
	case GFX_DEPTHTEXTURE_FORMAT:
		return GL_DEPTH_COMPONENT;

	default:
		cout << "Error: Intended texture format isn't supported by Find_Texture_Channel_Type()\n";
		return NULL;
	}
}

int Find_Texture_Value_Type(GFX_ENUM value_type) {
	switch (value_type) {
	case GFX_UNSIGNED_BYTE:
		return GL_UNSIGNED_BYTE;
	case GFX_FLOAT:
		return GL_FLOAT;

	default:
		cout << "Error: Intended Texture Value Type isn't supported for now!\n";
		return NULL;
	}
}

void Check_OpenGL_Errors(string status) {
	int error = glGetError();
	//If there is a error, first print the status!
	if (error != NULL) {
		cout << "In status: " << status << endl;
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
}

KEYBOARD_KEYs Convert_Key_to_Engine(int GLFW_Key) {
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

int Convert_Key_to_GLFW_Key(KEYBOARD_KEYs Keyboard_Key) {
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


int Convert_MouseButton_to_GLFW_Key(MOUSE_BUTTONs Mouse_Button) {
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
