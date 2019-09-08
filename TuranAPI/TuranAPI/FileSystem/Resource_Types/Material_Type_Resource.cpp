#include "Material_Type_Resource.h"

using namespace TuranAPI::File_System;

Material_Uniform::Material_Uniform(string variable_name, TuranAPI::TuranAPI_ENUMs variable_type) : VARIABLE_NAME(variable_name), VARIABLE_TYPE(variable_type) {}
Material_Uniform::Material_Uniform() {}

vector<Material_Instance*> Material_Instance::ALL_Material_Instances = vector<Material_Instance*>{};

vector<Material_Type_Resource*> Material_Type_Resource::ALL_MATERIAL_TYPEs = vector<Material_Type_Resource*>{};

TuranAPI::TuranAPI_ENUMs Material_Instance::Get_Resource_Type() {
	return TuranAPI::MATERIAL_INSTANCE_RESOURCE;
}



Material_Type_Resource::Material_Type_Resource() {
	ALL_MATERIAL_TYPEs.push_back(this);
}

TuranAPI::TuranAPI_ENUMs Material_Type_Resource::Get_Resource_Type() {
	return MATERIAL_TYPE_RESOURCE;
}

Material_Instance::Material_Instance() {
	ALL_Material_Instances.push_back(this);
}

void Material_Instance::Set_Uniform_Data(string uniform_name, void* pointer_to_data) {
	Material_Uniform* uniform = &UNIFORM_LIST[Find_Uniform_byName(uniform_name)];
	if (pointer_to_data == nullptr) {
		cout << "Error: Couldn't set GPU uniform data, because data is nullptr!\n";
		TuranAPI::Breakpoint();
		return;
	}
	if (uniform == nullptr) {
		cout << "Error: Found uniform is nullptr!\n";
		TuranAPI::Breakpoint();
		return;
	}
	uniform->DATA = pointer_to_data;
}

unsigned int Material_Instance::Find_Uniform_byName(string uniform_name) {
	for (unsigned int i = 0; i < UNIFORM_LIST.size(); i++) {
		if (UNIFORM_LIST[i].VARIABLE_NAME == uniform_name)
			return i;
	}
	cout << "Error: Intended uniform variable: " << uniform_name << " can't be found in Material Type: " << Material_Type->NAME << endl;
	TuranAPI::Breakpoint();
	return -1;
}

Material_Instance* Material_Instance::Find_MaterialInstance_byID(unsigned int ID) {
	for (Material_Instance* MAT_INST : ALL_Material_Instances) {
		if (MAT_INST->ID == ID) {
			return MAT_INST;
		}
	}
	cout << "Error: Intended Material Instance isn't found by ID!: " << ID << endl;
	TuranAPI::Breakpoint();
	return nullptr;
}

Material_Instance* Material_Instance::Find_MaterialInstance_byName(string name_of_resource) {
	for (Material_Instance* MAT_INST : ALL_Material_Instances) {
		if (MAT_INST->NAME == name_of_resource) {
			return MAT_INST;
		}
	}
	cout << "Error: Intended Material Instance: " << name_of_resource << " isn't found!\n";
	TuranAPI::Breakpoint();
	return nullptr;
}