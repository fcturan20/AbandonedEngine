#pragma once
#include "Engine_Includes.h"

#include "Mesh_Data_Class.h"

struct ENGINE Mesh_File {
private:
	static vector<Mesh_File*> ALL_OBJs;
public:
	string NAME;
	string PATH;
	MESH_TYPE TYPE;
	Mesh_File(string name, string path, MESH_TYPE mesh_type) : NAME(name), PATH(path), TYPE(mesh_type) {
		ALL_OBJs.push_back(this);
	}
	static vector<Mesh_File*> Get_All_OBJs();
};
