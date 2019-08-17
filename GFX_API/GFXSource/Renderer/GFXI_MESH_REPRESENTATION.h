#pragma once
#include "GFXSource/GFX_Includes.h"

class GFXAPI GFXI_MESH {
protected:
	unsigned int VAO, VBO, EBO;
	unsigned int Indices_Number, Vertex_Number;

public:
	unsigned int Return_VAO();
	unsigned int Return_VBO();
	unsigned int Return_EBO();
	unsigned int Return_Indices_Number();
	unsigned int Return_Vertex_Number();
};