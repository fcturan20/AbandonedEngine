#pragma once
#include "Includes.h"

#include "GFX_Shader.h"
#include "Graphics/GFX/GFX_ENUMs.h"

struct Material_Uniform {
	string VARIABLE_NAME;
	GFX_ENUM VARIABLE_TYPE;
	const float* DATA = nullptr;
	Material_Uniform(string variable_name, GFX_ENUM variable_type) : VARIABLE_NAME(variable_name), VARIABLE_TYPE(variable_type){}
};

class GFXI_Material {
protected:
	friend class OGL3_Material;

	//All Materials!
	static vector<GFXI_Material*> ALL_Materials;


	GFX_Shader* SHADER;
	//Uniforms won't change at run-time because we are defining uniforms at compile-time, but it is an easier syntax for now!
	//This list will be defined per material type (for example: Surface_PBR, Surface_Phong, Texture View etc.)
	vector<Material_Uniform> UNIFORM_LIST;

	unsigned int Find_Uniform_byName(string uniform_name) {
		for (unsigned int i = 0; i < UNIFORM_LIST.size(); i++) {
			if (UNIFORM_LIST[i].VARIABLE_NAME == uniform_name)
				return i;
		}
		cout << "Error: Intended uniform variable: " << uniform_name << " can't be found in Shader: " << SHADER->Return_Name() << endl;
		return -1;
	}

public:
	void Set_Uniform_Data(string uniform_name, const float* pointer_to_data) {
		Material_Uniform* uniform = &UNIFORM_LIST[Find_Uniform_byName(uniform_name)];
		if (pointer_to_data == nullptr) {
			cout << "Error: Couldn't set GPU uniform data, because data is nullptr!\n";
			return;
		}
		uniform->DATA = pointer_to_data;
	}
};


vector<GFXI_Material*> GFXI_Material::ALL_Materials = vector<GFXI_Material*>();