#include "OGL3_FileSystem.h"
#include "TuranAPI/Profiler/Profiler_Core.h"


void OGL3_FileSystem::Load_GFX_Contents_fromDisk() {
	cout << "GFX Contents are being loaded now!\n";

	TuranAPI::File_System::FileSystem::Load_Resources_fromFileList(&GFXContentList_onDisk);

}

void OGL3_FileSystem::Clear_All_GFXContents() {
	GFXContentList_onDisk.Get_ContentListVector()->clear();
	TuranAPI::File_System::FileSystem::Write_a_Resource_toDisk(&GFXContentList_onDisk);
}