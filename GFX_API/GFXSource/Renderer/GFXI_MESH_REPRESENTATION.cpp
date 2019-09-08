#include "GFXI_MESH_REPRESENTATION.h"

vector<GFXI_MESH*> GFXI_MESH::ALL_GFXI_MESHes = vector<GFXI_MESH*>{};

GFXI_MESH::GFXI_MESH() {
	ALL_GFXI_MESHes.push_back(this);
}