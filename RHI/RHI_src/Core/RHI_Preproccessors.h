#pragma once
/*
	This header for Syntax of RHI.
	If you want to add a class or a data structure, you should use RHI_C prefix to export it
	If you want to add a function or something shouldn't be imported with its definition, you should use RHI_FUNC prefix to export it


*/

#ifdef TE_PLATFORM_WINDOWS
	#ifdef RHI_BUILD_DLL
		#define RHI_C __declspec(dllexport)
		#define RHI_FUNC __declspec(dllexport)
	#else
		#define RHI_C __declspec(dllimport)
		#define RHI_FUNC
	#endif // RHI_BUILD_DLL

#else
	#error Physics only supports Windows!
#endif // TE_PLATFORM_WINDOWS
