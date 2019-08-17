#pragma once
#include "Engine_Includes.h"

#include "Mesh_Data_Class.h"

class ENGINE Static_Model {
	friend class Model_Loader;
	static vector<Static_Model*> ALL_MODELs;

	unsigned int NAME;
public:
	string Get_Name();

	static vector<Static_Model*> Get_All_Models();

	vector<Mesh_Instance*> Meshes_of_Model;
};
