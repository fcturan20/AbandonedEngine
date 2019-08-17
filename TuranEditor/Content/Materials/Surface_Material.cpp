#include "Surface_Material.h"


Surface_Material::Surface_Material() : GFX_Material() {
	//Set surface shader pointer to access shader for uniform and shader binding 
	SHADER = new GFX_Shader("Surface_Shader", OPENGL3, "Main.vert", "Main.frag");

	//UNIFORM_LIST.push_back(Material_Uniform("model_transform", GFX_MAT4x4));
	UNIFORM_LIST.push_back(Material_Uniform("view_matrix", GFX_MAT4x4));
	UNIFORM_LIST.push_back(Material_Uniform("projection_matrix", GFX_MAT4x4));
	UNIFORM_LIST.push_back(Material_Uniform("texture_diffuse", GFX_TEXTURE_2D));
}