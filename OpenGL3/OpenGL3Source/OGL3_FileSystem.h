#pragma once
#include "OpenGL3Source/OpenGL3_Includes.h"
#include "TuranAPI/API_FileSystem.h"


class OGL3_API OGL3_FileSystem : public GFX_FileSystem{
public:
	virtual void Load_GFX_Contents_fromDisk() override;
	virtual void Clear_All_GFXContents() override;
};

