#pragma once

//This header is used to create a GL data type classification for all of the TuranEngine
//For example; Texture types, Mipmap settings, Desktop modes etc.
//In GL specific [GFX_API]_ENUMs.h, these data types have to be converted to GL specific data types
//For example; GFX_TEXTURE_2D data type here, should be converted to GL_TEXTURE_2D in OGL3_ENUMs.h

enum GFX_ENUM : unsigned short {
	GFX_NULL = 0,

	//Window modes

	GFX_FULLSCREEN = 1,
	GFX_WINDOWED,

	//V-Sync Modes

	V_SYNC_OFF,
	V_SYNC_ON,

	//Texture Dimensions

	GFX_TEXTURE_2D,

	//Texture Formats

	//This format should use RGBA channels in Turan Engine
	GFX_COLORTEXTURE_FORMAT,
	GFX_DEPTHTEXTURE_FORMAT,

	//Render Target Attachments

	GFX_TEXTURE_COLOR0_ATTACHMENT,
	GFX_TEXTURE_DEPTH_ATTACHMENT,

	//Parameter types

	GFX_UNSIGNED_BYTE,
	GFX_SIGNED_BYTE,
	GFX_UNSIGNED_INT,
	GFX_SIGNED_INT,
	GFX_FLOAT,
	GFX_MAT4x4,

	//Depth Test Functions

	GFX_DEPTH_ALWAYS,
	GFX_DEPTH_NEVER,
	GFX_DEPTH_LESS,
	GFX_DEPTH_LEQUAL,
	GFX_DEPTH_GREATER,
	GFX_DEPTH_GEQUAL,

	//Depth Mode

	GFX_DEPTH_READ_WRITE,
	GFX_DEPTH_READ_ONLY,
	GFX_DEPTH_OFF,

	//Texture Wrapping

	GFX_REPEAT,
	GFX_MIRRORED_REPEAT,
	GFX_CLAMP_TO_EDGE,

	//Texture Filtering

	GFX_NEAREST_FROM_1MIP,
	GFX_LINEAR_FROM_1MIP,
	GFX_NEAREST_FROM_2MIP,
	GFX_LINEAR_FROM_2MIP,

	//Texture Channels

	GFX_TEXTURE_RGB,
	GFX_TEXTURE_RGBA
};
