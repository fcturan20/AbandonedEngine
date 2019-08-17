#include "Scene_Core.h"

Scene::Scene(string name)
	: NAME(name){
	cout << "An empty Scene is created, name is: " << name << endl;
	ALL_SCENEs.push_back(this);
}

vector<Scene*> Scene::ALL_SCENEs = vector<Scene*>();

void Scene::Run_Scene() {
	//Update EngineComponents of the Scene!
	CAMERAs[0]->Take_Inputs();
	mat4* view_matrix = CAMERAs[0]->Return_View_Matrix();
	mat4* proj_matrix = CAMERAs[0]->Return_Projection_Matrix();

	for (Static_Model_Instance* model : MODELs) {
		for (Mesh_Instance* mesh : model->Access_Model()->Meshes_of_Model) {
			mesh->MATERIAL->Set_Uniform_Data("view_matrix", value_ptr(*view_matrix));
			mesh->MATERIAL->Set_Uniform_Data("projection_matrix", value_ptr(*proj_matrix));
		}
	}
}

void* Scene::Return_RenderGraph() {
	return RENDERGRAPH;
}

unsigned int Scene::Get_RenderGraph_type_Index() {
	return RENDERGRAPH_type_INDEX;
}

void Scene::Set_RenderGraph(void* rendergraph_ptr) {
	RENDERGRAPH = rendergraph_ptr;
}

vector<Static_Model_Instance*>* Scene::Access_Static_MODELs() {
	return &MODELs;
}

string Scene::Return_Name() {
	return NAME;
}

//For now, our scene has only one camera so the camera is main and active all time!
Camera* Scene::Return_Active_Camera() {
	return CAMERAs[0];
}