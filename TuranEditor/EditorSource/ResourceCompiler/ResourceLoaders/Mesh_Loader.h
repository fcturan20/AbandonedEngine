#pragma once
#include "EditorSource/Editor_Includes.h"

//Assimp libraries to load Model
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class ENGINE Model_Loader {
private:


public:
	void Import_Model(string PATH);
};
