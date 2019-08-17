#pragma once
#include "Engine_Includes.h"

enum ENGINE MESH_TYPE : unsigned char {
	MESH_STATIC = 0,
	MESH_DYNAMIC = 1,
	MESH_SKELETAL = 2
};

//This class holds a mesh's (A part of the imported model) vertex attributes and GPU buffer class pointer that stores attributes' GPU buffer informations (Such as VAO, VBO etc.)!
//This class doesn't have a shader because shaders should be set in a Static_Model_Instance!
class ENGINE Mesh_Data {
private:
	friend class Model_Loader;
	friend class GFX_Renderer;
	friend class OGL3_Renderer;
	friend class OGL3_SYS;

protected:
	vec3* POSITIONs = nullptr, *NORMALs = nullptr, *TANGENTs = nullptr, *BITANGENTs = nullptr;
	unsigned int *INDICEs = nullptr;
	vec2 *TEXTCOORDs = nullptr;
	int VERTEX_NUMBER = 0, INDICEs_LENGTH = 0;
	void* GFX_MESH = nullptr;
	string NAME = "";

public:


	string Get_Name();
	vec3* Get_Positions();
	unsigned int* Get_Indices();
	vec3* Get_Normals();
	vec2* Get_TextCoords();
	vec3* Get_Tangents();
	vec3* Get_Bitangents();
	int Get_Vertex_Number();
	int Get_Indice_Number();
	void* Get_GFXI_Mesh();
	void Set_GFXI_Mesh(void* gfx_mesh);
};

//This class is used to support rendering each Mesh with different material without changing any other Mesh's Material that uses same Geometry Data
class ENGINE Mesh_Instance {
public:
	Mesh_Data* MESH_INFO;
	GFX_Material* MATERIAL;
};