#include "Scene_Resource.h"
using namespace TuranAPI::File_System;

Scene_Resource* Scene_Resource::SCENE = nullptr;

TuranAPI::TuranAPI_ENUMs Scene_Resource::Get_Resource_Type() {
	return TuranAPI::SCENE_RESOURCE;
}