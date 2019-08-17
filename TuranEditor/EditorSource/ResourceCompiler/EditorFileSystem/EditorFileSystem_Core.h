#pragma once
#include "EngineSource/TuranEngine.h"
using namespace File_System;

/*
1) This namespace is defined in Engine
2) But extended in Editor to handle Editor specific files too!
*/
namespace File_System {
	/*
	1) This class is used to load the project's editor datas;
	2) You can specify how to create and load new data types here!
	3) If project's File_List.bin isn't found, gives error to either specify the location or create a new project!
	*/
	class Editor_FileSystem : public FileSystem {
	public:
		//Load the project or create a new one!
		Editor_FileSystem();
	};
}