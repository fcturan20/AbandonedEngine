#pragma once
#include "Includes.h"

#include "Mesh_Data_Class.h"

class Static_Model {
	friend class Mesh_Loader;
	static vector<Static_Model*> ALL_MODELs;

	string NAME;
public:
	string Get_Name() {
		return NAME;
	}

	static vector<Static_Model*> Get_All_Models() {
		return ALL_MODELs;
	}

	vector<Mesh_Data*> Meshes_of_Model;
};

vector<Static_Model*> Static_Model::ALL_MODELs = vector<Static_Model*>();