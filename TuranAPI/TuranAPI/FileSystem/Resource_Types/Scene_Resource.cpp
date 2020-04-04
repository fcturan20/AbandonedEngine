#include "Scene_Resource.h"
using namespace TuranAPI::File_System;

TuranAPI::TuranAPI_ENUMs Scene_Resource::Get_Resource_Type() {
	return TuranAPI::TuranAPI_ENUMs::SCENE_RESOURCE;
}


bool Scene_Resource::Verify_Resource_Data() {
	if (NAME != "" && PATH != "") {
		for (unsigned int i = 0; i < ADDED_COMPONENTs.size(); i++) {
			Game_Object::GameComponent* COMPONENT = ADDED_COMPONENTs[i];
			if (COMPONENT == nullptr) {
				TuranAPI::Breakpoint("Scene Resource isn't verified because a Game Component is nullptr!");
				return false;
			}
		}
		return true;
	}
	TuranAPI::Breakpoint("Scene Resource isn't verified because it has invalid Name or Path!\n"
		+ String("NAME: ") + NAME + String("\n PATH: ") + PATH + String("\n"));
	return false;
}

Scene_Resource::Scene_Resource() : ADDED_COMPONENTs(LASTUSEDALLOCATOR, 2, 4), ALL_SCENEs(LASTUSEDALLOCATOR, 10, 100) {

}