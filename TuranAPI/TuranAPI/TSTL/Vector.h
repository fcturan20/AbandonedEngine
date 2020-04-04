#pragma once
#include "TuranAPI/MemoryManager/MemoryManager_Core.h"
#include <iostream>

namespace TuranAPI {
	namespace STL {
		template <typename T>
		//To avoid unnecessary copies and wasting memory blocks, you should guess the optimum size for your buffer!
		//This Vector can only include classes that has a TClass member!
		class Vector {
			T* pointer_toBuffer = nullptr;
			std::size_t buffer_size = 0, buffer_length = 0, expand_size = 0;
			TuranAPI::MemoryManagement::IAllocator* Allocator;
		public:
			//Expanding size variable is used to know how much to expand the vector if it's reached its limits.
			Vector(TuranAPI::MemoryManagement::IAllocator* Allocator, std::size_t expand_size, std::size_t size = 0);
			Vector(TuranAPI::MemoryManagement::IAllocator* Allocator, std::size_t expand_size, std::initializer_list<T>& list);
			~Vector();
			void push_back(const T& object);
			void erase(std::size_t index);
			void clear();
			T& operator[] (size_t index);
			const T& operator[] (size_t index) const;
			Vector<T>& operator= (std::initializer_list<T>& list);
			std::size_t size() const;
			std::size_t max_size() const;
			void resize(size_t resize);
			T* data();
			T& Get(size_t index) const;
		};

		template<class T>
		Vector<T>::Vector(TuranAPI::MemoryManagement::IAllocator* Allocator_, std::size_t expanding_size, std::size_t size) : Allocator(Allocator_), expand_size(expanding_size) {
			pointer_toBuffer = (T*)Allocator->Allocate_MemoryBlock(size * sizeof(T));
			if (pointer_toBuffer) {
				buffer_size = size;
				buffer_length = 0;
			}
			else {
				std::cout << "A vector of " << size << "elements isn't created!\n";
			}
		}
		template<class T>
		Vector<T>::Vector(TuranAPI::MemoryManagement::IAllocator* Allocator_, std::size_t expanding_size, std::initializer_list<T>& list) : Allocator(Allocator_), expand_size(expanding_size) {
			for (auto element : list) {
				this->push_back(element);
			}
		}
		template<class T>
		Vector<T>::~Vector() {
			for (size_t i = 0; i < buffer_length; i++) {
				pointer_toBuffer[i].~T();
			}
			Allocator->Delete_MemoryBlock(pointer_toBuffer);
		}
		template<class T>
		void Vector<T>::push_back(const T& object) {
			if (expand_size == 0 && buffer_length == buffer_size) {
				std::cout << "Vector's expand size is 0, so it's not expandable! No changes.\n";
				return;
			}
			if (!pointer_toBuffer) {
				std::cout << "Vector.push_back() has failed because vector is failed on creation already!\n";
			}
			if (buffer_length == buffer_size) {
				std::cout << "The vector's size is not enough! Expanding its size!";
				void* PTR = Allocator->Allocate_MemoryBlock((buffer_size + expand_size) * sizeof(T));
				if (PTR) {
					memcpy(PTR, pointer_toBuffer, buffer_size * sizeof(T));
					Allocator->Delete_MemoryBlock(pointer_toBuffer);
					pointer_toBuffer = (T*)PTR;
					buffer_size += expand_size;

					memcpy(&pointer_toBuffer[buffer_length], &object, sizeof(T));
					buffer_length += 1;
				}
				else {
					std::cout << "Vector.push_back() has failed!\n";
				}
			}
			else {
				memcpy(&pointer_toBuffer[buffer_length], &object, sizeof(T));
				buffer_length += 1;
			}
		}
		template<class T>
		void Vector<T>::erase(size_t index) {
			if (index > buffer_length) {
				std::cout << "There is no initialized element of index: " << index << std::endl;
				return;
			}
			if (index == buffer_length - 1) {
				std::cout << "Last element already!\n";
				buffer_length -= 1;
				pointer_toBuffer[index].~T();
				for (unsigned int i = 0; i < sizeof(T); i++) {
					*((char*)pointer_toBuffer + (sizeof(T) * index) + i) = 0;
				}
				return;
			}
			pointer_toBuffer[index].~T();
			for (unsigned int i = 0; i < (buffer_length - 1) - index; i++) {
				memcpy(&pointer_toBuffer[index + i], &pointer_toBuffer[index + i + 1], sizeof(T));
			}
			buffer_length -= 1;
		}
		template<class T>
		void Vector<T>::clear() {
			for (unsigned int i = 0; i < buffer_length * sizeof(T); i++) {
				*((char*)pointer_toBuffer + i) = '\0';
			}
			buffer_length = 0;
		}
		template<class T>
		T& Vector<T>::operator[](size_t index) {
			if (index < buffer_length) {
				return pointer_toBuffer[index];
			}
			else {
				std::cout << "There is no element with index " << index << " in the Vector!\n";
				T defaultvar;
				return defaultvar;
			}
		}
		template<class T>
		Vector<T>& Vector<T>::operator= (std::initializer_list<T>& list) {
			for (auto element : list) {
				this->push_back(element);
			}
			return *this;
		}
		template<class T>
		const T& Vector<T>::operator[](size_t index) const {
			if (index < buffer_length) {
				return pointer_toBuffer[index];
			}
			else {
				std::cout << "There is no element with index " << index << " in the Vector!\n";
				T defaultvar;
				return defaultvar;
			}
		}
		template<class T>
		size_t Vector<T>::size() const {
			return buffer_length;
		}
		template<class T>
		size_t Vector<T>::max_size() const {
			return buffer_size;
		}
		template<class T>
		void Vector<T>::resize(size_t resize) {
			if (resize > buffer_size) {
				void* PTR = Allocator->Allocate_MemoryBlock((resize) * sizeof(T));
				if (PTR) {
					memcpy(PTR, pointer_toBuffer, buffer_size * sizeof(T));
					Allocator->Delete_MemoryBlock(pointer_toBuffer);
					pointer_toBuffer = (T*)PTR;
					buffer_size = resize;
				}
				else {
					std::cout << "Vector.push_back() has failed!\n";
				}
			}
			else if (resize < buffer_size && resize < buffer_length) {
				//Set every byte to 0
				for (unsigned int i = 0; i < (buffer_length - resize) * sizeof(T); i++) {
					*((char*)pointer_toBuffer + (resize * sizeof(T)) + i) = 0;
				}
				buffer_length = resize;
			}
			else if (resize < buffer_size && resize > buffer_length) {
				//Set every byte to 0
				for (unsigned int i = 0; i < (resize - buffer_length) * sizeof(T); i++) {
					*((char*)pointer_toBuffer + (buffer_length * sizeof(T)) + i) = 0;
				}
			}
			//This is for a special case where buffer pointer is handled by 3rd party libraries!
			//For example: Vulkan uses buffer pointer to fill the data, when this happens we should specify buffer_length to access the buffer successfully!
			//Never delete this, for the sake of VULKAN!
			buffer_length = resize;
		}
		template<class T>
		T* Vector<T>::data() {
			return pointer_toBuffer;
		}
		template<class T>
		T& Vector<T>::Get(size_t index) const {
			return pointer_toBuffer[index];
		}
	}
}