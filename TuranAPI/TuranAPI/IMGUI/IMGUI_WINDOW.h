#pragma once
#include "TuranAPI/API_includes.h"

namespace TuranAPI {
	namespace IMGUI {
		class TURANAPI IMGUI_WindowManager {
		public:
			class TURANAPI IMGUI_WINDOW
			{
			protected:
				bool Is_Window_Open = true;
				String Window_Name;

				//Definition of window's running progress!
				virtual void Run_Window() = 0;
			public:
				IMGUI_WINDOW(const char* name);


				bool Get_Is_Window_Open();

				~IMGUI_WINDOW();
			};
			Vector<IMGUI_WINDOW*> ALL_IMGUI_WINDOWs;
			static IMGUI_WindowManager* SELF;
			IMGUI_WindowManager();
			//Run all of the active IMGUI windows!
			//But generally, if a window is out of view, it isn't runned. But this is defined in Run_Window() for each window!
			static void Run_IMGUI_WINDOWs();
		};
	}
}