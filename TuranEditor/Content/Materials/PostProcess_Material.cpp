#include "PostProcess_Material.h"

PostProcess_Material::PostProcess_Material() {
	//Set Shader for the Material!
	SHADER = new GFX_Shader("PostProcess_Shader", OPENGL3, "Content/Materials/Shaders/Post_Process.vert", "Content/Materials/Shaders/Post_Process.frag");

	UNIFORM_LIST.push_back(Material_Uniform("Display_Texture", GFX_TEXTURE_2D));
}