#pragma once
#include "Includes.h"

#include "Graphics/GFX/Renderer/GFX_Shader.h"
#include "Graphics/GFX/Renderer/GFXI_Material.h"



class Surface_Material : public GFXI_Material {
public:
	Surface_Material() : GFXI_Material() {
		//Set surface shader pointer to access shader for uniform and shader binding 
		SHADER = &Surface_Shader;

		//UNIFORM_LIST.push_back(Material_Uniform("model_transform", GFX_MAT4x4));
		UNIFORM_LIST.push_back(Material_Uniform("view_matrix", GFX_MAT4x4));
		UNIFORM_LIST.push_back(Material_Uniform("projection_matrix", GFX_MAT4x4));
	}
};