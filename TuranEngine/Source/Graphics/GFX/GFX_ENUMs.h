#pragma once

//This header is used to create a GL data type classification for all of the TuranEngine
//For example; Texture types, Mipmap settings, Desktop modes etc.
//In GL specific [GFX_API]_ENUMs.h, these data types have to be converted to GL specific data types
//For example; GFX_TEXTURE_2D data type here, should be converted to GL_TEXTURE_2D in OGL3_ENUMs.h


enum WINDOW_MODE : unsigned char {
	GFX_FULLSCREEN = 0,
	GFX_WINDOWED = 1
};

enum V_SYNC : unsigned char {
	V_SYNC_OFF = 0,
	V_SYNC_ON = 1
};

enum TEXTURE_DIMENSION : unsigned char {
	GFX_TEXTURE_2D = 0,
	/*For now, other texture dimensions aren't allowed!
	GFX_TEXTURE_1D = 1,
	GFX_TEXTURE_3D = 2*/
};

enum TEXTURE_FORMAT : unsigned char {
	//This format should use RGBA channels in Turan Engine
	GFX_COLORTEXTURE_FORMAT = 0,
	GFX_DEPTHTEXTURE_FORMAT = 1
};

enum TEXTURE_ATTACHMENT : unsigned char {
	GFX_TEXTURE_COLOR0_ATTACHMENT = 0,
	GFX_TEXTURE_DEPTH_ATTACHMENT = 1
};

enum TEXTURE_FORMAT_VALUETYPE : unsigned char {
	GFX_UNSIGNED_BYTE = 0,
	GFX_FLOAT = 1
};

enum TEXTURE_FILTERING : unsigned char {

};

enum TEXTURE_WRAPPING : unsigned char {

};

enum GFX_DEPTH_TEST : unsigned char {
	GFX_DEPTH_ALWAYS = 0,
	GFX_DEPTH_NEVER = 1,
	GFX_DEPTH_LESS = 2,
	GFX_DEPTH_LEQUAL = 3,
	GFX_DEPTH_GREATER = 4,
	GFX_DEPTH_GEQUAL = 5
};

//Define Depth mode as Read&Write, Read-Only, Off
//Off means no Depth Testing will perform!
//Read-Only means Depth Test will perform and discard fragments, but won't change Depth Buffer!
//Read&Write means Depth Test will perform and change Depth Buffer!
enum GFX_DEPTH_MODE : unsigned char {
	GFX_DEPTH_READ_WRITE = 0,
	GFX_DEPTH_READ_ONLY = 1,
	GFX_DEPTH_OFF = 2
};
