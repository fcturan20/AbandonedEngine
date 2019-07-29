#pragma once
#include "Includes.h"

#include "Graphics/GFX/GFX_ENUMs.h"

class GFX_Renderer {
protected:
	friend class OGL3_SYS;
	friend class GFX_API;

	void* Renderer_Context;

	virtual void Start_Creation() = 0;
	virtual void New_Frame() = 0;

public:
	~GFX_Renderer() {
		cout << "Renderer is destroying!\n";
		delete Renderer_Context;
	}
};