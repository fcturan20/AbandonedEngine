#pragma once
#include "Includes.h"

#include "EngineComponent.h"

#include "Engine/Meshes/Mesh_HEADER.h"

/* There are some abstractions and lacks in this class, here is some definitions:
1) In a model, each part that has different material index is created as a mesh according to .obj file!
2) So, each model consists of meshes! 
3) This means you would specify each mesh's shader in this class, but I don't want to complicate this anymore!
4) So, for now, each mesh of the model uses the same material/shader and each model has one material/shader!
5) There is no difference between the terms "material" and "shader", because there isn't a material system in engine!
*/
class Static_Model_Instance : public EngineComponent {
	friend class OGL3_RenderGraph;

	Static_Model* MODEL;
	string SHADER_NAME;
	vector<string> DRAW_PASSes_NAMEs;
	mat4 world_transform;

	static vector<Static_Model_Instance*> ALL_Model_Instances;
public:
	Static_Model_Instance(Static_Model* model, string shader_names, vector<string> draw_passes_names)
		: MODEL(model), SHADER_NAME(shader_names), DRAW_PASSes_NAMEs(draw_passes_names) {
		ALL_Model_Instances.push_back(this);
		/*
		if (shader_names.size() != model->Meshes_of_Model.size()) {
			cout << "Error: Shader List and Mesh List isn't match for model: " << model->Get_Name() << endl;
			this->~Static_Model_Instance();
		}
		*/
	}

	~Static_Model_Instance() {
		delete MODEL;
	}

	static vector<Static_Model_Instance*> Get_All_Model_Instances() {
		return ALL_Model_Instances;
	}

	Static_Model* Access_Model() {
		return MODEL;
	}

	vector<string> Get_Draw_Pass_Names() {
		return DRAW_PASSes_NAMEs;
	}

	mat4 Return_World_Transform() {
		return world_transform;
	}
};

vector<Static_Model_Instance*> Static_Model_Instance::ALL_Model_Instances = vector<Static_Model_Instance*>();

Static_Model_Instance First_Model_Instance(Static_Model::Get_All_Models()[0], "Surface_Material", vector<string>{"G-Buffer"});