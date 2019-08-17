#include "MESH_OBJs.h"

vector<Mesh_File*> Mesh_File::Get_All_OBJs() {
	return ALL_OBJs;
}
vector<Mesh_File*> Mesh_File::ALL_OBJs = vector<Mesh_File*>();