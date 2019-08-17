#pragma once
#include "GFXSource/GFX_Includes.h"

#include "GFX_Shader.h"

struct GFXAPI Material_Uniform {
	string VARIABLE_NAME;
	GFX_ENUM VARIABLE_TYPE;
	void* DATA = nullptr;
	Material_Uniform(string variable_name, GFX_ENUM variable_type);
};

class GFXAPI GFX_Material {
protected:
	//All Materials!
	static vector<GFX_Material*> ALL_Materials;


	GFX_Shader* SHADER;
	//Uniforms won't change at run-time because we are defining uniforms at compile-time, but it is an easier syntax for now!
	//This list will be defined per material type (for example: Surface_PBR, Surface_Phong, Texture View etc.)
	vector<Material_Uniform> UNIFORM_LIST;

	unsigned int Find_Uniform_byName(string uniform_name);

public:
	void Set_Uniform_Data(string uniform_name, void* pointer_to_data);
};
