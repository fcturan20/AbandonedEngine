#pragma once
#include "Includes.h"

#include "Engine/EngineComponents/EngineComponent.h"
#include "Engine/EngineComponents/Camera.h"
#include "Engine/EngineComponents/Static_Model_Instance.h"

class Scene {
private:
	friend class OGL3_RenderGraph;
	friend class GFX_RenderGraph;

	string NAME;
	vector<Static_Model_Instance*> MODELs;
	vector<Camera*> CAMERAs;
	unsigned int RENDERGRAPH_type_INDEX;
	void* RENDERGRAPH = nullptr;



public:
	Scene(string name, vector<Static_Model_Instance*> models, vector<Camera*> cameras)
		: NAME(name), MODELs(models), CAMERAs(cameras) {
		ALL_SCENEs.push_back(this);
	}

	void Run_Scene();

	void* Return_RenderGraph() {
		return RENDERGRAPH;
	}

	unsigned int Get_RenderGraph_type_Index() {
		return RENDERGRAPH_type_INDEX;
	}

	void Set_RenderGraph(void* rendergraph_ptr) {
		RENDERGRAPH = rendergraph_ptr;
	}

	vector<Static_Model_Instance*>* Access_Static_MODELs() {
		return &MODELs;
	}

	string Return_Name() {
		return NAME;
	}

	//For now, our scene has only one camera so the camera is main and active all time!
	Camera* Return_Active_Camera() {
		return CAMERAs[0];
	}

	static vector<Scene*> ALL_SCENEs;
};

vector<Scene*> Scene::ALL_SCENEs = vector<Scene*>();

void Scene::Run_Scene() {
	//Update EngineComponents of the Scene!
	CAMERAs[0]->Take_Inputs();
}

Scene First_Scene("First_Scene", Static_Model_Instance::Get_All_Model_Instances(), vector<Camera*>{new Camera(vec3(0, 0, -30))});