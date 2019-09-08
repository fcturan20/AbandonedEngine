#include "GFX_RenderGraph.h"


GFX_RenderGraph::GFX_RenderGraph() {
	cout << "Render Graph object is created!\n";
}

GFX_Draw_Pass* GFX_RenderGraph::Get_DrawPass_byName(const string& NAME) {
	for (GFX_Draw_Pass* Draw_Pass : DRAW_PASSes) {
		if (Draw_Pass->Get_Name() == NAME) {
			return Draw_Pass;
		}
	}
	cout << "Error: Intended Draw Pass isn't found!: " << NAME << endl;
	TuranAPI::Breakpoint();
	return nullptr;
}