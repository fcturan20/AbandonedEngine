#pragma once
#include "TuranAPI/API_includes.h"
#include "Resource_Type.h"

namespace TuranAPI {
	namespace File_System {

		class TURANAPI FileList_Resource : public Resource_Type {
			Vector<Resource_Type*> ContentListVector;
		public:
			FileList_Resource(const String& path);
			virtual TuranAPI::TuranAPI_ENUMs Get_Resource_Type() override;
			Vector<Resource_Type*>* Get_ContentListVector();
			virtual bool Verify_Resource_Data();
		};

	}
}