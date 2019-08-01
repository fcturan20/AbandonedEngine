#pragma once
#include "Includes.h"

#include "Graphics/GFX/Renderer/GFXI_Material.h"

enum MESH_TYPE : unsigned char {
	MESH_STATIC = 0,
	MESH_DYNAMIC = 1,
	MESH_SKELETAL = 2
};

//This class holds a mesh's (A part of the imported model) vertex attributes and GPU buffer class pointer that stores attributes' GPU buffer informations (Such as VAO, VBO etc.)!
//This class doesn't have a shader because shaders should be set in a Static_Model_Instance!
class Mesh_Data {
private:
	friend class Mesh_Loader;
	friend class GFX_Renderer;
	friend class OGL3_Renderer;
	friend class OGL3_SYS;

protected:
	vec3* POSITIONs = nullptr, *NORMALs = nullptr, *TANGENTs = nullptr, *BITANGENTs = nullptr;
	unsigned int *INDICEs = nullptr;
	vec2 *TEXTCOORDs = nullptr;
	int VERTEX_NUMBER = 0, INDICEs_LENGTH = 0;
	void* GFX_MESH = nullptr;
	MESH_TYPE TYPE;
	string NAME = "";

public:
	Mesh_Data() {
		
	}

	~Mesh_Data() {
		delete[] POSITIONs;
		delete[] NORMALs;
		delete[] TEXTCOORDs;
		delete[] TANGENTs;
		delete[] BITANGENTs;
	}

	string Get_Name() {
		return NAME;
	}

	vec3* Get_Positions() {
		return POSITIONs;
	}

	unsigned int* Get_Indices() {
		return INDICEs;
	}

	vec3* Get_Normals() {
		return NORMALs;
	}

	vec2* Get_TextCoords() {
		return TEXTCOORDs;
	}

	vec3* Get_Tangents() {
		return TANGENTs;
	}

	vec3* Get_Bitangents() {
		return BITANGENTs;
	}

	int Get_Vertex_Number() {
		return VERTEX_NUMBER;
	}

	int Get_Indice_Number() {
		return INDICEs_LENGTH;
	}

	void* Get_GFXI_Mesh() {
		return GFX_MESH;
	}

	void Set_GFXI_Mesh(void* gfx_mesh) {
		GFX_MESH = gfx_mesh;
	}
};

//This class is used to support rendering each Mesh with different material without changing any other Mesh's Material that uses same Geometry Data
class Mesh_Instance {
public:
	Mesh_Data* MESH_INFO;
	GFXI_Material* MATERIAL;
};