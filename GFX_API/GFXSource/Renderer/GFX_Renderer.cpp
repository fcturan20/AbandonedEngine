#include "GFX_Renderer.h"


GFX_Renderer::~GFX_Renderer() {
	cout << "Renderer is destroying!\n";
	delete Renderer_Context;
}