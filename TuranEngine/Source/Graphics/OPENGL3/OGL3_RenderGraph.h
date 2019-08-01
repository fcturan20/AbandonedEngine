#pragma once
#include "Includes.h"

#include "Engine/Meshes/Mesh_HEADER.h"

#include "Engine/EngineComponents/EngineComponent.h"
#include "Engine/EngineComponents/Static_Model_Instance.h"

#include "Engine/Scene/Scene_Core.h"

#include "Graphics/GFX/Renderer/GFXI_MESH_REPRESENTATION.h"
#include "Graphics/GFX/Renderer/GFX_RenderGraph.h"


class OGL3_RenderGraph : public GFX_RenderGraph {
protected:
	friend class OGL3_SYS;

	virtual void Update_GPU_Mesh_Buffers();
public:

};



//For now, we are just sending Static Models because we don't use dynamic models in engine!
void OGL3_RenderGraph::Update_GPU_Mesh_Buffers() {
	//For each model in scene!
	for (Static_Model_Instance* model_instance : SCENE->MODELs) {

		//Send each mesh part of the model to GPU! 
		//Note: Each mesh has a different material according to .obj
		for (unsigned int mesh_index_in_model = 0; mesh_index_in_model < model_instance->MODEL->Meshes_of_Model.size(); mesh_index_in_model++) {
			Mesh_Data* mesh = model_instance->MODEL->Meshes_of_Model[mesh_index_in_model]->MESH_INFO;

			//If mesh is sent to GPU before, skip!
			if (mesh->Get_GFXI_Mesh() != nullptr) {
				cout << "GPU Mesh Buffer is found for Mesh: " << mesh->Get_Name() << endl;
				continue;
			}

			//Calculate the buffer size for the mesh!
			unsigned int Indices_Size = mesh->Get_Indice_Number() * sizeof(unsigned int);

			unsigned int Positions_Size = mesh->Get_Vertex_Number() * sizeof(vec3);
			unsigned int TextCoords_Size = mesh->Get_Vertex_Number() * sizeof(vec2);
			//Note: These have the same size with Positions_Size but I did this to understand the code better and debug easier!
			unsigned int Normals_Size = mesh->Get_Vertex_Number() * sizeof(vec3);
			unsigned int Tangents_Size = mesh->Get_Vertex_Number() * sizeof(vec3);
			unsigned int Bitangents_Size = mesh->Get_Vertex_Number() * sizeof(vec3);
			unsigned int Total_Vertex_Data_Size = Positions_Size + TextCoords_Size + Normals_Size + Tangents_Size + Bitangents_Size;

			GFXI_MESH* gfx_mesh = new GFXI_MESH;
			glGenVertexArrays(1, &gfx_mesh->VAO);
			glGenBuffers(1, &gfx_mesh->VBO);
			glGenBuffers(1, &gfx_mesh->EBO);
			gfx_mesh->Indices_Number = mesh->Get_Indice_Number();
			gfx_mesh->Vertex_Number = mesh->Get_Vertex_Number();

			glBindVertexArray(gfx_mesh->VAO);
			glBindBuffer(GL_ARRAY_BUFFER, gfx_mesh->VBO);
			glBufferData(GL_ARRAY_BUFFER, Total_Vertex_Data_Size, NULL, GL_STATIC_DRAW);
			glBufferSubData(GL_ARRAY_BUFFER, NULL, Positions_Size, mesh->Get_Positions());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size, TextCoords_Size, mesh->Get_TextCoords());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size + TextCoords_Size, Normals_Size, mesh->Get_Normals());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size + TextCoords_Size + Normals_Size, Tangents_Size, mesh->Get_Tangents());
			glBufferSubData(GL_ARRAY_BUFFER, Positions_Size + TextCoords_Size + Normals_Size + Tangents_Size, Bitangents_Size, mesh->Get_Bitangents());

			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gfx_mesh->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices_Size, mesh->Get_Indices(), GL_STATIC_DRAW);

			//Position Attribute
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)0);
			//TextCoord Attribute
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)Positions_Size);
			//Vertex Normal Attribute
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(Positions_Size + TextCoords_Size));
			//Tangent Attribute
			glEnableVertexAttribArray(3);
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(Positions_Size + TextCoords_Size + Normals_Size));
			//Bitangent Attribute
			glEnableVertexAttribArray(4);
			glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), (void*)(Positions_Size + TextCoords_Size + Normals_Size + Tangents_Size));


			cout << "GPU Mesh Buffer is sent for Mesh: " << mesh->Get_Name() << endl;
			mesh->Set_GFXI_Mesh(gfx_mesh);
		}
	}
}
