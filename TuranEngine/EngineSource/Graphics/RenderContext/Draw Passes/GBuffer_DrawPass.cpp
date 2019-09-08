#include "GBuffer_DrawPass.h"
#include "GFXSource/GFX_Core.h"

G_BUFFER_DrawResource::G_BUFFER_DrawResource(vector<GFXI_MESH*>* model_meshes) {
	vector<GFXI_MESH*> meshes_of_this_drawpass;
	//Search Static Models of all Scene and for each model, if one of draw pass names that is in the model is G-Buffer then add it to vector
	for (GFXI_MESH* mesh_of_model : *model_meshes) {
		meshes_of_this_drawpass.push_back(mesh_of_model);
	}

	for (GFXI_MESH* mesh : meshes_of_this_drawpass) {
		Add_Mesh(mesh);
	}
}

void G_BUFFER_DrawResource::Add_Mesh(GFXI_MESH* mesh) {
	Static_VAOs.push_back(mesh->VAO);
	Static_Indice_Numbers.push_back(mesh->Indices_Number);
}

void G_BUFFER_DrawResource::Clean_Resource() {
	cout << "You forgot to code Clean_Resource() of G_BUFFER_DrawResource!\n";
	TuranAPI::Breakpoint();
}
void G_BUFFER_DrawResource::Update_Resources() {
	cout << "You forgot to code Update_Resources() of G_BUFFER_DrawResource!\n";
	TuranAPI::Breakpoint();
}

void G_BUFFER_DrawPass::Creation(vector<GFXI_MESH*>* model_meshes) {
	GFX_API::GFX_API_OBJ->Check_GL_Errors("Before Creation!");
	NAME = "G-Buffer";

	//Set depth modes!
	DEPTHBUFFER_MODE = GFX_DEPTH_READ_WRITE;
	DEPTHTEST_MODE = GFX_DEPTH_LESS;		 //Reversed depth!

	FRAMEBUFFER = GFX_API::RENDERER->Create_Framebuffer(1920, 1080);


	GFX_API::RENDERER->Bind_Framebuffer(FRAMEBUFFER);
	//First Render Texture is Color
	GFX_API::RENDERER->Create_RenderTarget(FRAMEBUFFER, FRAMEBUFFER->WIDTH, FRAMEBUFFER->HEIGHT, TuranAPI::API_TEXTURE_2D, GFX_COLORTEXTURE_FORMAT, GFX_TEXTURE_COLOR0_ATTACHMENT, TuranAPI::VAR_UBYTE8);
	//Second Render Texture is Depth
	GFX_API::RENDERER->Create_RenderTarget(FRAMEBUFFER, FRAMEBUFFER->WIDTH, FRAMEBUFFER->HEIGHT, TuranAPI::API_TEXTURE_2D, GFX_DEPTHTEXTURE_FORMAT, GFX_TEXTURE_DEPTH_ATTACHMENT, TuranAPI::VAR_FLOAT32);
	GFX_API::RENDERER->Attach_RenderTargets_to_Framebuffer(FRAMEBUFFER);
	GFX_API::RENDERER->Check_ActiveFramebuffer_Status("G-Buffer");

	DRAW_RESOURCE = new G_BUFFER_DrawResource(model_meshes);
	cout << NAME << " Draw Pass Creation is done!\n";
}

void G_BUFFER_DrawPass::Update_Resources() {
	cout << "You forgot to code Update_Resources() of G_BUFFER_DrawPass!\n";
	TuranAPI::Breakpoint();
}

void G_BUFFER_DrawPass::Render_Loop() {
	cout << "G-Buffer Render Loop is started to run!\n";
	GFX_API::GFX_API_OBJ->Check_GL_Errors("Before Render Loop!");

	GFX_API::RENDERER->Set_Depth_Test(DEPTHTEST_MODE, DEPTHBUFFER_MODE);

	GFX_API::GFX_API_OBJ->Check_GL_Errors("Before Binding Framebuffer!");
	GFX_API::RENDERER->Bind_Framebuffer(FRAMEBUFFER);
	GFX_API::RENDERER->Clear_RenderTarget(FRAMEBUFFER, GFX_TEXTURE_COLOR0_ATTACHMENT, vec3(0.2f, 0.3f, 0.3f));
	GFX_API::RENDERER->Clear_RenderTarget(FRAMEBUFFER, GFX_TEXTURE_DEPTH_ATTACHMENT, vec3(1));		//Reversed Depth!
	
	
	mat4 proj_mat = perspective(radians(45.0f), float(1920.0f / 1080.0f), 0.1f, 10000.0f);
	mat4 view_mat;
	view_mat = translate(view_mat, vec3(0, -8,-22));
	mat4 world_transform;

	static TuranAPI::File_System::Material_Instance* material_inst = TuranAPI::File_System::Material_Instance::Find_MaterialInstance_byName("SurfaceInst_Default");
	material_inst->Set_Uniform_Data("projection_matrix", value_ptr(proj_mat));
	material_inst->Set_Uniform_Data("view_matrix", value_ptr(view_mat));
	material_inst->Set_Uniform_Data("world_transform", value_ptr(world_transform));

	//For each mesh in the Draw Pass!
	G_BUFFER_DrawResource* gbuffer_resource = (G_BUFFER_DrawResource*)DRAW_RESOURCE;
	unsigned int RenderMesh_Number = gbuffer_resource->Static_VAOs.size();
	cout << "Mesh number that will be rendered: " << RenderMesh_Number << endl;

	for (unsigned int mesh_index = 0; mesh_index < RenderMesh_Number; mesh_index++) {
		GFX_API::RENDERER->Bind_Material_Instance(material_inst);


		GFX_API::GFX_API_OBJ->Check_GL_Errors(string("Before binding uniforms of a mesh in G-Buffer that mesh_index: " + to_string(mesh_index) + " Draw Pass!"));
		GFX_API::RENDERER->Draw_Indexed_Objects(vector<void*>{(void*)& gbuffer_resource->Static_VAOs[mesh_index]}, vector<unsigned int>{gbuffer_resource->Static_Indice_Numbers[mesh_index]});
	}

	cout << "G-Buffer Render Loop is finished!\n";
}
