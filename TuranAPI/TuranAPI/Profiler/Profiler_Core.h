#pragma once
#include "TuranAPI/API_includes.h"

namespace TuranAPI {
	namespace Profiler {
		class TURANAPI Profiler_Core {
		public:
			//If you want to directly access it, you should use std::chrono::time_point<chrono::steady_clock> type!
			static void* START_POINT_PTR;

			static void Start_Timing();
			//Don't forget to call End_Timing() if you want to stop timing!
			static float Get_Timing_in_Seconds();
			//Don't forget to call Get_Timing() if you want to get timing!
			static void End_Timing();
		};


	}
}