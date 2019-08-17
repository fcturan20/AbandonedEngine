#include "Static_Model_Instance.h"

vector<Static_Model_Instance*> Static_Model_Instance::Get_All_Model_Instances() {
	return ALL_Model_Instances;
}

Static_Model* Static_Model_Instance::Access_Model() {
	return MODEL;
}

vector<string> Static_Model_Instance::Get_Draw_Pass_Names() {
	return DRAW_PASSes_NAMEs;
}

mat4 Static_Model_Instance::Return_World_Transform() {
	return world_transform;
}
vector<Static_Model_Instance*> Static_Model_Instance::ALL_Model_Instances = vector<Static_Model_Instance*>();

Static_Model_Instance::Static_Model_Instance(Static_Model* model, string shader_names, vector<string> draw_passes_names)
: EngineComponent(STATIC_MODEL_COMPONENT, vec3(0)), MODEL(model), SHADER_NAME(shader_names), DRAW_PASSes_NAMEs(draw_passes_names) {
	ALL_Model_Instances.push_back(this);
	/*
	if (shader_names.size() != model->Meshes_of_Model.size()) {
		cout << "Error: Shader List and Mesh List isn't match for model: " << model->Get_Name() << endl;
		this->~Static_Model_Instance();
	}
	*/
}

Static_Model_Instance::~Static_Model_Instance() {
	delete MODEL;
}