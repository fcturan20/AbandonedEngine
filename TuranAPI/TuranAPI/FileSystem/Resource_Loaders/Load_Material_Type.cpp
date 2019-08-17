#include "TuranAPI/FileSystem/FileSystem_Core.h"
using namespace TuranAPI::File_System;

void FileSystem::Load_Material_Type(void* data, unsigned int id) {
	cout << "Loading Material Type (Shader Stage) ID: " << id << endl;
	auto MATERIAL_TYPE = GameContent::GetResource(data)->TYPE_as_Material_Type();

	
}