#pragma once
#include "Includes.h"

#include "Mesh_Data_Class.h"

struct Mesh_File {
private:
	static vector<Mesh_File*> ALL_OBJs;
public:
	string NAME;
	string PATH;
	MESH_TYPE TYPE;
	Mesh_File(string name, string path, MESH_TYPE mesh_type) : NAME(name), PATH(path), TYPE(mesh_type) {
		ALL_OBJs.push_back(this);
	}
	static vector<Mesh_File*> Get_All_OBJs() {
		return ALL_OBJs;
	}
};

vector<Mesh_File*> Mesh_File::ALL_OBJs = vector<Mesh_File*>();

Mesh_File Nanosuit_File{ "Nanosuit", "C:/Users/furka/Desktop/Çalýþmalar/Modeller/Nanosuit/nanosuit.obj", MESH_STATIC };
//Mesh_File Sponza_File{ "Sponza", "C:/Users/furka/Desktop/Çalýþmalar/Modeller/Sponza Scene/sponza.obj", MESH_STATIC };