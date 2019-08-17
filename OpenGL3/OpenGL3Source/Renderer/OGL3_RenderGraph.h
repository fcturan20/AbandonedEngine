#pragma once
#include "OpenGL3Source/OpenGL3_Includes.h"


class OGL3_API OGL3_RenderGraph : public GFX_RenderGraph {
protected:
	friend class OGL3_SYS;

	virtual void Update_GPU_Mesh_Buffers();
public:

};