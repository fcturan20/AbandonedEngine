#include "Static_Model_Class.h"

string Static_Model::Get_Name() {
	return "NAME type is changed to int, please fix this!\n";
}

vector<Static_Model*> Static_Model::Get_All_Models() {
	return ALL_MODELs;
}
vector<Static_Model*> Static_Model::ALL_MODELs = vector<Static_Model*>();