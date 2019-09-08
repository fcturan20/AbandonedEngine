#include "Profiler_Core.h"
using namespace TuranAPI::Profiler;

void* Profiler_Core::START_POINT_PTR;

void Profiler_Core::Start_Timing() {
	auto DATA_POINTER_CREATION = new chrono::time_point<chrono::steady_clock>;
	START_POINT_PTR = (void*)DATA_POINTER_CREATION;

	*(chrono::time_point<chrono::steady_clock>*)START_POINT_PTR = chrono::high_resolution_clock::now();
}

float Profiler_Core::Get_Timing_in_Seconds() {
	auto NOW = chrono::high_resolution_clock::now();
	if (START_POINT_PTR == nullptr) {
		cout << "Error: You forgot the call Start_Timing() before Get_Timing()!\n";
		SLEEP_THREAD(20);
		return 0.0f;
	}
	chrono::duration<float> duration = (NOW - (*(chrono::time_point<chrono::steady_clock>*)START_POINT_PTR));
	return duration.count();
}

void Profiler_Core::End_Timing() {
	delete START_POINT_PTR;
	START_POINT_PTR = nullptr;
}