#pragma once
#include "TuranAPI/API_Logger.h"
#include "TuranAPI/API_Profiler.h"

#ifdef WINDOWS10_FORENGINE
#ifdef OPENGL4_BUILD
#define OGL4_API __declspec(dllexport)
#else
#define OGL4_API __declspec(dllimport)
#endif // OPENGL4_BUILD
#endif // WINDOWS10_FORENGINE
