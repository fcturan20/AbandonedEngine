#pragma once
#include "Includes.h"

//OpenGL 3.0 Libs
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Graphics/GFX/Renderer/GFXI_MESH_REPRESENTATION.h"

class OGL3_Mesh : public GFXI_MESH {
private:
	friend class OGL3_Renderer;

public:

	~OGL3_Mesh() {
		//Delete mesh from GPU!
	}
};