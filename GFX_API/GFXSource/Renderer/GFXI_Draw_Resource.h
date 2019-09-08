#pragma once
#include "GFXSource/GFX_Includes.h"

class GFXAPI GFXI_Draw_Resource {
	friend class GFX_Draw_Pass;
	//Code which parts of a mesh will be stored and how for each Draw Resource!
protected:

	//Clean resources when you won't use render node anymore!
	virtual void Clean_Resource() = 0;
	virtual void Update_Resources() = 0;
};