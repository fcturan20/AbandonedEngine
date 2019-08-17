#pragma once
#include "Engine_Includes.h"

#include "Engine/EngineComponents/EngineComponent.h"
#include "Engine/EngineComponents/Camera.h"
#include "Engine/EngineComponents/Static_Model_Instance.h"

#include "Engine/GameObject/GameObject.h"

class ENGINE Scene {
private:
	string NAME;
	vector<GameObject*> GAME_OBJECTs;
	vector<Static_Model_Instance*> MODELs;
	vector<Camera*> CAMERAs;
	unsigned int RENDERGRAPH_type_INDEX;
	void* RENDERGRAPH = nullptr;

public:
	Scene(string name);

	virtual void Run_Scene();

	static vector<Scene*> ALL_SCENEs;
	void* Return_RenderGraph();

	unsigned int Get_RenderGraph_type_Index();

	void Set_RenderGraph(void* rendergraph_ptr);

	vector<Static_Model_Instance*>* Access_Static_MODELs();

	string Return_Name();

	//For now, our scene has only one camera so the camera is main and active all time!
	Camera* Return_Active_Camera();
};