#include "Profiling_Window.h"
using namespace TuranAPI::IMGUI;
using namespace TuranAPI::Profiler;
#include <string>

Profiling_Window::Profiling_Window() : IMGUI_WINDOW("Profiler") {

}

void Profiling_Window::Run_Window() {
	if (!Is_Window_Open) {
		delete this;
		return;
	}
	if (!IMGUI::Create_Window(Window_Name, Is_Window_Open, false)) {
		IMGUI::End_Window();
		return;
	}
	IMGUI::Input_Text("Profiling Data File Path", &PATH);
	if (IMGUI::Button("Load the file")) {
		Profiled_Session = TuranAPI::Profiler::Load_a_Profiling_Resource(PATH);
	}

	if (Profiled_Session != nullptr) {
		std::cout << "Profiled session is created!\n";
		std::cout << "Profiled scope number: " << Profiled_Session->PROFILED_SCOPEs_VECTOR->size() << std::endl;
		if (IMGUI::Begin_Tree(PATH)) {
			for (unsigned int i = 0; i < Profiled_Session->PROFILED_SCOPEs_VECTOR->size(); i++) {
				Profiled_Scope* Scope = &(*Profiled_Session->PROFILED_SCOPEs_VECTOR)[i];
				if (IMGUI::Begin_Tree(Scope->NAME)) {
					IMGUI::Text(std::string("Start Point: " + std::to_string(Scope->START_POINT)).c_str());
					IMGUI::Text(std::string("End Point: " + std::to_string(Scope->END_POINT)).c_str());
					IMGUI::Text(std::string("Duration: " + std::to_string(Scope->DURATION) + "").c_str());
					if (Scope->DURATION < 1000) {
						IMGUI::Text(std::string("Duration: " + std::to_string(Scope->DURATION) + " milliseconds").c_str());
					}
					else {
						IMGUI::Text(std::string("Duration: " + std::to_string((Scope->DURATION) / 1000) + " seconds").c_str());
					}
					IMGUI::Text(std::string("Thread ID: " + std::to_string(Scope->THREAD_ID)).c_str());
					IMGUI::End_Tree();
				}
			}
			IMGUI::End_Tree();
		}
	}

	IMGUI::End_Window();
}