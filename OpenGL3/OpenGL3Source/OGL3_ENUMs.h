#pragma once
#include "GFXSource/GFX_Core.h"

#ifdef WINDOWS10_FORENGINE
#ifdef OPENGL3_BUILD
#define OGL3_API __declspec(dllexport)
#else
#define OGL3_API __declspec(dllimport)
#endif // OPENGL3_BUILD
#endif // WINDOWS10_FORENGINE



int OGL3_API Find_Texture_Attachment_Type(GFX_ENUM attachment);
int OGL3_API Find_Texture_Dimension(GFX_ENUM dimension);
int OGL3_API Find_Texture_Format(GFX_ENUM format);
int OGL3_API Find_Texture_Channel_Type(GFX_ENUM texture_format);
int OGL3_API Find_Texture_Value_Type(GFX_ENUM value_type);
int OGL3_API Find_Texture_Wrapping(GFX_ENUM wrapping);
int OGL3_API Find_Texture_Mipmap_Filtering(GFX_ENUM mipmap_filter);

void OGL3_API Check_OpenGL_Errors(string status);

//KEYBOARD_KEYs OGL3_API Convert_Key_to_Engine(int GLFW_Key);
//int OGL3_API Convert_Key_to_GLFW_Key(KEYBOARD_KEYs Keyboard_Key);


//int OGL3_API Convert_MouseButton_to_GLFW_Key(MOUSE_BUTTONs Mouse_Button);

int OGL3_API Find_GFX_DepthTest_Mode(GFX_ENUM depth_test);
