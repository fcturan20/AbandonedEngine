#pragma once
#include "TuranAPI/API_ENUMs.h"
#include "GFXSource/GFX_Core.h"

//OpenGL4 Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "OpenGL4_Includes.h"

namespace OpenGL4 {
	unsigned int OGL4_API Find_Texture_Attachment_Type(GFX_API::GFX_ENUM attachment);
	unsigned int OGL4_API Find_Texture_Dimension(TuranAPI::TuranAPI_ENUMs dimension);
	unsigned int OGL4_API Find_Texture_Format(GFX_API::GFX_ENUM format);
	unsigned int OGL4_API Find_RenderTarget_Channel_Type(GFX_API::GFX_ENUM texture_format);
	unsigned int OGL4_API Find_Texture_Channel_Type(TuranAPI::TuranAPI_ENUMs channel_type);
	unsigned int OGL4_API Find_Texture_Value_Type(TuranAPI::TuranAPI_ENUMs value_type);
	unsigned int OGL4_API Find_Texture_Wrapping(TuranAPI::TuranAPI_ENUMs wrapping);
	unsigned int OGL4_API Find_Texture_Mipmap_Filtering(TuranAPI::TuranAPI_ENUMs mipmap_filter);

	//KEYBOARD_KEYs OGL3_API Convert_Key_to_Engine(int GLFW_Key);
	//int OGL3_API Convert_Key_to_GLFW_Key(KEYBOARD_KEYs Keyboard_Key);


	//int OGL3_API Convert_MouseButton_to_GLFW_Key(MOUSE_BUTTONs Mouse_Button);

	unsigned int OGL4_API Find_GFX_DepthTest_Mode(GFX_API::GFX_ENUM depth_test);
}
