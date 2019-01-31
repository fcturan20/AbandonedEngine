#pragma once

//This is the place for Engine's Core Preproccessors


#ifdef TE_PLATFORM_WINDOWS
	#ifdef TE_BUILD_DLL
		#define Engine_C __declspec(dllexport)
		#define Engine_FUNC __declspec(dllexport)
	#else
		#define Engine_C __declspec(dllimport)
		#define Engine_FUNC

	#endif 
#else
	#error Turan Engine only supports Windows!
#endif