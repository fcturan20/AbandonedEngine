#include "GFXI_Material.h"

Material_Uniform::Material_Uniform(string variable_name, GFX_ENUM variable_type) : VARIABLE_NAME(variable_name), VARIABLE_TYPE(variable_type){}

vector<GFX_Material*> GFX_Material::ALL_Materials = vector<GFX_Material*>();

void GFX_Material::Set_Uniform_Data(string uniform_name, void* pointer_to_data) {
	Material_Uniform* uniform = &UNIFORM_LIST[Find_Uniform_byName(uniform_name)];
	if (pointer_to_data == nullptr) {
		cout << "Error: Couldn't set GPU uniform data, because data is nullptr!\n";
		return;
	}
	uniform->DATA = pointer_to_data;
}

unsigned int GFX_Material::Find_Uniform_byName(string uniform_name) {
	for (unsigned int i = 0; i < UNIFORM_LIST.size(); i++) {
		if (UNIFORM_LIST[i].VARIABLE_NAME == uniform_name)
			return i;
	}
	cout << "Error: Intended uniform variable: " << uniform_name << " can't be found in Shader: " << SHADER->Return_Name() << endl;
	return -1;
}