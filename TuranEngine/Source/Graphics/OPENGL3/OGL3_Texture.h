#pragma once
#include "Includes.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphics/GFX/GFX_ENUMs.h"
#include "Graphics/GFX/Renderer/GFX_Texture.h"

#include "Graphics/OPENGL3/OGL3_ENUMs.h"

class OGL3_Texture {
public:
	static void Send_Textures_to_GPU() {
		unsigned int i = 0;
		for (GFX_Texture* texture : GFX_Texture::ALL_TEXTUREs) {
			int texture_D = Find_Texture_Dimension(texture->DIMENSION);
			int Channel_Type = Find_Texture_Channel_Type(texture->CHANNEL_TYPE);
			int Value_Type = Find_Texture_Value_Type(texture->FORMAT_VALUETYPE);
			int Wrapping = Find_Texture_Wrapping(texture->WRAPPING);
			int Mipmap_Filtering = Find_Texture_Mipmap_Filtering(texture->MIPMAP_FILTERING);
			//All texture should be upscaled linearly!
			int Upscale_filtering = GL_LINEAR;


			glGenTextures(1, &texture->ID);
			Check_OpenGL_Errors("After generating the texture!\n");
			glBindTexture(texture_D, texture->ID);
			Check_OpenGL_Errors("After binding the texture!\n");
			cout << "Texture ID: " << texture->ID << endl;


			// Set the texture wrapping/filtering options (on the currently bound texture object)
			glTexParameteri(texture_D, GL_TEXTURE_WRAP_S, Wrapping);
			glTexParameteri(texture_D, GL_TEXTURE_WRAP_T, Wrapping);
			glTexParameteri(texture_D, GL_TEXTURE_MIN_FILTER, Mipmap_Filtering);
			glTexParameteri(texture_D, GL_TEXTURE_MAG_FILTER, Upscale_filtering);
			Check_OpenGL_Errors("After setting Wrapping and Filtering!\n");
			cout << "Set wrapping!\n";
			glTexImage2D(texture_D, 0, Channel_Type, texture->WIDTH, texture->HEIGHT, 0, Channel_Type, Value_Type, texture->DATA);
			glGenerateMipmap(texture_D);
			//glGenerateMipmap(texture_D);
			Check_OpenGL_Errors("After sending model texture: " + to_string(i) + "!\n");
			cout << "TexImage2D is finished!\n";
			i++;
		}
		cout << "Sent Texture Number: " << i << endl;
	}
};
