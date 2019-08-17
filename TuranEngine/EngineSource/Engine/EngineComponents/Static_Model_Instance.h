#pragma once
#include "Engine_Includes.h"

#include "EngineComponent.h"

#include "Engine/Meshes/Static_Model_Class.h"

/* There are some abstractions and lacks in this class, here is some definitions:
1) In a model, each part that has different material index is created as a mesh according to .obj file!
2) So, each model consists of meshes! 
3) This means you would specify each mesh's shader in this class, but I don't want to complicate this anymore!
4) So, for now, each mesh of the model uses the same material/shader and each model has one material/shader!
5) There is no difference between the terms "material" and "shader", because there isn't a material system in engine!
*/
class ENGINE Static_Model_Instance : public EngineComponent {
	friend class OGL3_RenderGraph;

	Static_Model* MODEL;
	string SHADER_NAME;
	vector<string> DRAW_PASSes_NAMEs;
	mat4 world_transform;

	static vector<Static_Model_Instance*> ALL_Model_Instances;
public:
	Static_Model_Instance(Static_Model* model, string shader_names, vector<string> draw_passes_names);

	~Static_Model_Instance();

	static vector<Static_Model_Instance*> Get_All_Model_Instances();

	Static_Model* Access_Model();
	vector<string> Get_Draw_Pass_Names();
	mat4 Return_World_Transform();
};
