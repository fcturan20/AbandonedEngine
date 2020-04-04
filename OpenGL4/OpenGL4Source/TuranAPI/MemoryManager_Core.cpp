#include "TuranAPI/MemoryManager/MemoryManager_Core.h"
#include <stdlib.h>
#include <iostream>



namespace TuranAPI {
	namespace MemoryManagement {
		TAPIMemoryAllocator* TAPIMemoryAllocator::SELF = nullptr;
		TAPIMemoryAllocator::TAPIMemoryAllocator(){
			if (SELF != nullptr) {
				std::cout << "Don't create a MemoryAllocator! Call didn't do anything!\n";
				return;
			}
			std::cout << "TAPIMemoryAllocator is created!\n";
			SELF = this;
			MemoryPool.address = nullptr;
			MemoryPool.size = 0;
		}
		TAPIMemoryAllocator::~TAPIMemoryAllocator() {
			std::cout << "TAPIMemoryAllocator is being deleted!\n";
		}
		void* TAPIMemoryAllocator::Allocate_MemoryBlock(size_t size) {
			std::cout << "A buffer of " << size << " bytes allocation request found in TAPIMemoryAllocator!\n";
			void* finaladdress = SELF->MemoryPool.address;
			for (unsigned int blockindex = 0; blockindex < MAX_MEMORYBLOCKNUMBER; blockindex++) {
				MemoryBlockInfo& MemoryBlock = Allocated_MemoryBlocks[blockindex];
				finaladdress = (char*)finaladdress + MemoryBlock.size;
				if (size <= MemoryBlock.size && MemoryBlock.address == nullptr) {
					std::cout << "Intended block's size is less than or equal to found memory block!\n";
					MemoryBlock.address = finaladdress;
					//You shouldn't change Memory Block's size because all of the allocations before this, is made upon previous size!
					//You should move all the previous allocated memory to set the size (Which is not ideal!)
					//If I'd want to find memory leaks causing this, I could write code here to log the leaks!
					return MemoryBlock.address;
				}
				else if (MemoryBlock.size == 0 && MemoryBlock.address == nullptr) {
					std::cout << "An empty block is created for intended block! Block's Array index is: " << blockindex << "\n";
					std::cout << "MemoryPool's start pointer: " << MemoryPool.address << std::endl << "MemoryBlock's pointer: " << finaladdress << std::endl;
					//This means this index in the Allocated_MemoryBlocks has never been used, so we can add the data here!
					MemoryBlock.address = finaladdress;
					MemoryBlock.size = size;
					return MemoryBlock.address;
				}
			}
			//If you arrive here, that means there is no empty memory block in all Allocated_MemoryBlocks array!
			std::cout << "There is no empty memory block in all Allocated_MemoryBlocks array, so nullptr is returned!\n";
			return nullptr;
		}
		void TAPIMemoryAllocator::Delete_MemoryBlock(void* Pointer_ToDelete) {
			for (unsigned int i = 0; i < MAX_MEMORYBLOCKNUMBER; i++) {
				MemoryBlockInfo& MemoryBlock = Allocated_MemoryBlocks[i];
				if (MemoryBlock.address == Pointer_ToDelete) {
					//Set memory bits as 0
					for (unsigned int i = 0; i < MemoryBlock.size; i++) {
						*((char*)MemoryBlock.address + i) = 0;
					}
					MemoryBlock.address = nullptr;
					//We don't change size of an MemoryBlock ever, because all allocations are made according to them!
				}
			}
		}
		const MemoryBlockInfo& TAPIMemoryAllocator::Get_MemoryBlockInfo(void* address) {
			for (unsigned int i = 0; i < MAX_MEMORYBLOCKNUMBER; i++) {
				MemoryBlockInfo& MemoryBlock = Allocated_MemoryBlocks[i];
				if (address == MemoryBlock.address) {
					return MemoryBlock;
				}
				if (MemoryBlock.address == nullptr && MemoryBlock.size == 0) {
					return MemoryBlockInfo();
				}
			}
		}

		TMemoryManager* TMemoryManager::SELF = nullptr;
		TMemoryManager::TMemoryManager(size_t Main_MemoryBlockSize) {
			std::cout << "TMemoryManager is created!\n";
			MainMemoryBlock.address = malloc(Main_MemoryBlockSize);
			MainMemoryBlock.size = Main_MemoryBlockSize;
			std::cout << "Main Memory Block's start pointer: " << MainMemoryBlock.address << std::endl;
			SELF = this;
			MemoryBlockInfo TuranAPI_MemoryPool;
			TuranAPI_MemoryPool.address = MainMemoryBlock.address;
			TuranAPI_MemoryPool.size = 1024 * 1024 * 1;
			TAPIAllocator.MemoryPool = TuranAPI_MemoryPool;
			LastUsedAllocator = &TAPIAllocator;

			void* AllocatedMemoryAddres = LastUsedAllocator->Allocate_MemoryBlock(10);
		}
		TMemoryManager::~TMemoryManager() {
			std::cout << "TMemoryManager is being deleted!\n";
		}
	}
}

void* operator new(size_t size) {
	std::cout << "A memory block of " << size << " bytes will be allocated!\n";
	return LASTUSEDALLOCATOR->Allocate_MemoryBlock(size);
}
void* operator new(size_t size, TuranAPI::MemoryManagement::IAllocator* Allocator) {
	return Allocator->Allocate_MemoryBlock(size);
}
void operator delete(void* pointerToDelete) {
	LASTUSEDALLOCATOR->Delete_MemoryBlock(pointerToDelete);
}
void operator delete(void* pointerToDelete, TuranAPI::MemoryManagement::IAllocator* Allocator) {
	Allocator->Delete_MemoryBlock(pointerToDelete);
}
