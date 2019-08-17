#include "GFX_Draw_Pass.h"

GFX_Draw_Pass::GFX_Draw_Pass() : FRAMEBUFFER(new GFX_Framebuffer) {
	//When a Draw Pass is created, add it to the Renderer's Draw Pass list
	Draw_Passes.push_back(this);
}

vector<GFX_Draw_Pass*> GFX_Draw_Pass::Draw_Passes = vector<GFX_Draw_Pass*>();

GFX_Draw_Pass* GFX_Draw_Pass::Find_Draw_Pass_byName(string name) {
	for (GFX_Draw_Pass* draw_pass : Draw_Passes) {
		if (name == draw_pass->NAME)
			return draw_pass;
	}
	cout << "Draw Pass: " << name << " isn't found!\n";
	return nullptr;
}

//Getter-Setters
GFX_Framebuffer* GFX_Draw_Pass::Get_Framebuffer() {
	return FRAMEBUFFER;
}

vector<GFX_Draw_Pass*> GFX_Draw_Pass::Get_Draw_Passes() {
	return Draw_Passes;
}

string GFX_Draw_Pass::Get_Name() {
	return NAME;
}

/*
void GFX_Draw_Pass::Set_Camera(Camera* camera) {
	CAMERA = camera;
}
*/