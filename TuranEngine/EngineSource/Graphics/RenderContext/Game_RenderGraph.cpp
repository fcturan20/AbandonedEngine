#include "Game_RenderGraph.h"
#include "Draw Passes/Draw_Passes.h"

void Game_RenderGraph::Create_Resources() {
	G_BUFFER_DrawPass* GBUFFER = new G_BUFFER_DrawPass;
	DRAW_PASSes.push_back(GBUFFER);
	DRAW_PASSes[0]->Creation(&GFXI_MESH::ALL_GFXI_MESHes);
	cout << "Created Game_RenderGraph resources!\n";
}

void Game_RenderGraph::Update_Resources() {
	cout << "Error: You forgot to code Update_Resources() of Game_RenderGraph!\n";
}

void Game_RenderGraph::Run_RenderGraph() {
	cout << "Running Game_RenderGraph!\n";
	DRAW_PASSes[0]->Render_Loop();
	
	//Display the final result on main window!
	GFX_API::RENDERER->Show_RenderTarget_onWindow(GFX_API::ONSCREEN_Windows[0], DRAW_PASSes[0]->Get_Framebuffer()->BOUND_RTs[0]);
}