#include "Resource_Type.h"
using namespace TuranAPI::File_System;

Resource_Type::Resource_Type(IAllocator* Allocator_) : NAME(Allocator_) {

}

unsigned int Resource_Type::Get_ID() {
	return ID;
}
