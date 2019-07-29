#pragma once
#include "Includes.h"

class GFXI_MESH {
protected:
	unsigned int VAO, VBO, EBO;
	unsigned int Indices_Number, Vertex_Number;

	friend class OGL3_RenderGraph;

public:
	unsigned int Return_VAO() {
		return VAO;
	}

	unsigned int Return_VBO() {
		return VBO;
	}

	unsigned int Return_EBO() {
		return EBO;
	}

	unsigned int Return_Indices_Number() {
		return Indices_Number;
	}

	unsigned int Return_Vertex_Number() {
		return Vertex_Number;
	}
};