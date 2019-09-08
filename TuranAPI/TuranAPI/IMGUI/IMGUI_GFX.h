#pragma once
#include "TuranAPI/API_includes.h"

namespace TuranAPI {
	namespace IMGUI {
		class TURANAPI IMGUI_GFX {
		public:
			virtual void Initialize(void* Window_GPU_Context) = 0;
			virtual void Render_IMGUI(void* data) = 0;
			virtual void GFX_New_Frame() = 0;
			virtual void Destroy_IMGUI_GFX_Resources() = 0;
			virtual void Set_Platform_Settings() = 0;
		};
	}
}