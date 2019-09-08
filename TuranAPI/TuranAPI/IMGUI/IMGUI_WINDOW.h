#pragma once
#include "TuranAPI/API_includes.h"

namespace TuranAPI {
	namespace IMGUI {
		class TURANAPI IMGUI_WINDOW
		{
		protected:
			bool Is_Window_Open = true;
			string Window_Name;

			static vector<IMGUI_WINDOW*> ALL_IMGUI_WINDOWs;

			//Definition of window's running progress!
			virtual void Run_Window() = 0;
		public:
			IMGUI_WINDOW(string name);

			//Run all of the active IMGUI windows!
			//But generally, if a window is out of view, it isn't runned. But this is defined in Run_Window() for each window!
			static void Run_IMGUI_WINDOWs();

			bool Get_Is_Window_Open();

			~IMGUI_WINDOW();
		};
	}
}