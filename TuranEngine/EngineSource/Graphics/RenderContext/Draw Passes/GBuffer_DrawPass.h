#pragma once
#include "Engine_Includes.h"
#include "GFXSource/Renderer/GFX_Renderer.h"


class ENGINE G_BUFFER_DrawResource : public GFXI_Draw_Resource {
public:

	vector<unsigned int> Static_VAOs;
	vector<unsigned int> Static_Indice_Numbers;
	//It isn't supported for now, because there is no Scene description!
	//vector<TuranAPI::File_System::Material_Instance*> Material_Instances;

	G_BUFFER_DrawResource(vector<GFXI_MESH*>* model_meshes);
	void Add_Mesh(GFXI_MESH* mesh);


	virtual void Clean_Resource() override;
	virtual void Update_Resources() override;
};

class ENGINE G_BUFFER_DrawPass : public GFX_Draw_Pass {
	virtual void Creation(vector<GFXI_MESH*>* model_meshes) override;
	virtual void Update_Resources() override;
	virtual void Render_Loop() override;
};
