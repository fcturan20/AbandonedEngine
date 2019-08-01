#pragma once

//This header is used to create a GL data type classification for all of the TuranEngine
//For example; Texture types, Mipmap settings, Desktop modes etc.
//In GL specific [GFX_API]_ENUMs.h, these data types have to be converted to GL specific data types
//For example; GFX_TEXTURE_2D data type here, should be converted to GL_TEXTURE_2D in OGL3_ENUMs.h

enum GFX_ENUM : unsigned short {
	GFX_NULL = 0,

	GFX_FULLSCREEN = 1,
	GFX_WINDOWED,

	V_SYNC_OFF,
	V_SYNC_ON,

	GFX_TEXTURE_2D,

	//This format should use RGBA channels in Turan Engine
	GFX_COLORTEXTURE_FORMAT,
	GFX_DEPTHTEXTURE_FORMAT,


	GFX_TEXTURE_COLOR0_ATTACHMENT,
	GFX_TEXTURE_DEPTH_ATTACHMENT,

	GFX_UNSIGNED_BYTE,
	GFX_SIGNED_BYTE,
	GFX_UNSIGNED_INT,
	GFX_SIGNED_INT,
	GFX_FLOAT,
	GFX_MAT4x4,


	GFX_DEPTH_ALWAYS,
	GFX_DEPTH_NEVER,
	GFX_DEPTH_LESS,
	GFX_DEPTH_LEQUAL,
	GFX_DEPTH_GREATER,
	GFX_DEPTH_GEQUAL,

	GFX_DEPTH_READ_WRITE,
	GFX_DEPTH_READ_ONLY,
	GFX_DEPTH_OFF,

	OPENGL_3
};
