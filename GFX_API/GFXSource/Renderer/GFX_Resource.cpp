#include "GFX_Resource.h"

namespace GFX_API{
	unsigned int RenderTarget::Get_ID() const {
		return ID;
	}



	Framebuffer::Framebuffer(unsigned int width, unsigned int height) : WIDTH(width), HEIGHT(height), BOUND_RTs(LASTUSEDALLOCATOR, 1, 3) {

	}


	GPU_MESH::GPU_MESH() : ALL_GPU_MESHes(LASTUSEDALLOCATOR, 2, 2) {
		ALL_GPU_MESHes.push_back(this);
	}
}