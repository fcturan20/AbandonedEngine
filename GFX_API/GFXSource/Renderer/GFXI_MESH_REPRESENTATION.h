#pragma once
#include "GFXSource/GFX_Includes.h"

class GFXAPI GFXI_MESH {
public:
	static vector<GFXI_MESH*> ALL_GFXI_MESHes;

	unsigned int VAO, VBO, EBO;
	unsigned int Indices_Number, Vertex_Number;
	GFXI_MESH();
};