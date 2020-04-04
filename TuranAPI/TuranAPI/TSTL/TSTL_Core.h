#pragma once
#include "TuranAPI/MemoryManager/MemoryManager_Core.h"
#include "Vector.h"


namespace TuranAPI {
	namespace STL {
		class String {
			char* pointer_toBuffer = nullptr;
			std::size_t buffer_length = 0;
			TuranAPI::MemoryManagement::IAllocator* Allocator;
		public:
			String();
			String(const char* text);
			String(TuranAPI::MemoryManagement::IAllocator* Allocator);
			String(const char* text, TuranAPI::MemoryManagement::IAllocator* Allocator);
			String(const String& object);
			String(const String& object, TuranAPI::MemoryManagement::IAllocator* Allocator);
			~String();
			String& operator= (const String& string_toAssignFrom);
			String& operator= (const char* text);
			char& operator[] (unsigned int index) const;
			bool operator== (const char* text) const;
			bool operator!= (const char* text) const;
			operator const char* () const;
			friend String operator+ (const String& c1, const String& c2);
			friend std::ostream& operator<<(std::ostream& os, const String& string_toshow);
			std::size_t find_lastof(char letter) const;
			std::size_t length() const;
			const char* c_str() const;
			String* substr(std::size_t from, std::size_t to) const;
			void append(const char* text);
		};
		String operator+ (const String& c1, const String& c2);
		std::ostream& operator<<(std::ostream& os, const String& string_toshow);


		template <>
		class Vector<String> {
			String* pointer_toBuffer = nullptr;
			std::size_t buffer_size = 0, buffer_length = 0, expand_size = 0;
			TuranAPI::MemoryManagement::IAllocator* Allocator;
		public:
			//Expanding size variable is used to know how much to expand the vector if it's reached its limits.
			Vector(TuranAPI::MemoryManagement::IAllocator* Allocator, std::size_t expand_size, std::size_t size = 0);
			Vector(TuranAPI::MemoryManagement::IAllocator* Allocator, std::size_t expand_size, std::initializer_list<const char*>& list);
			~Vector();
			void push_back(const String& object);
			void push_back(const char* text);
			void erase(std::size_t index);
			void clear();
			String& operator[] (size_t index);
			const String& operator[] (size_t index) const;
			Vector<String>& operator= (std::initializer_list<const char*>& list);
			std::size_t size() const;
			std::size_t max_size() const;
			void resize(size_t resize);
			String* data();
			String& Get(size_t index) const;
		};
	}
}