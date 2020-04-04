#include "TuranAPI/TSTL/TSTL_Core.h"

namespace TuranAPI {
	namespace STL {

		String::String(TuranAPI::MemoryManagement::IAllocator* MemoryAllocator) : Allocator(MemoryAllocator) {

		}
		String::String(const char* text, TuranAPI::MemoryManagement::IAllocator* MemoryAllocator) : Allocator(MemoryAllocator) {
			*this = text;
		}
		String::String() {
			Allocator = LASTUSEDALLOCATOR;
		}
		String::String(const char* text) : String(text, LASTUSEDALLOCATOR) {

		}
		String::String(const String& object) {
			String(object, object.Allocator);
		}
		String::String(const String& object, TuranAPI::MemoryManagement::IAllocator* Allocator_) : Allocator(Allocator_){
			std::cout << "Copy Constructor for string has started! String to assign from: " << object << std::endl;
			buffer_length = object.buffer_length;
			pointer_toBuffer = (char*)Allocator->Allocate_MemoryBlock(object.buffer_length);
			memcpy(pointer_toBuffer, object.pointer_toBuffer, sizeof(char) * buffer_length);
		}
		String::~String() {
			if (!pointer_toBuffer) {
				Allocator->Delete_MemoryBlock(pointer_toBuffer);
			}
		}
		//Just copies the content, nothing fancy here!
		String& String::operator= (const String& string_toAssignFrom) {
			std::cout << "Operator = for string has started! String to Assign From: " << string_toAssignFrom << std::endl;
			unsigned int unnecessary_lettersnumber = 0;
			if (string_toAssignFrom.buffer_length > buffer_length) {
				if (pointer_toBuffer) {
					Allocator->Delete_MemoryBlock(pointer_toBuffer);
				}
				pointer_toBuffer = (char*)Allocator->Allocate_MemoryBlock(string_toAssignFrom.buffer_length);
				buffer_length = string_toAssignFrom.buffer_length;
			}
			else {
				unnecessary_lettersnumber = buffer_length - string_toAssignFrom.buffer_length;
			}
			memcpy(pointer_toBuffer, string_toAssignFrom.pointer_toBuffer, sizeof(char)* string_toAssignFrom.buffer_length);
			//Delete unnecessary letters of previous char buffer!
			for (std::size_t erase_unnecessarylettersindex = 0; erase_unnecessarylettersindex < unnecessary_lettersnumber; erase_unnecessarylettersindex++) {
				pointer_toBuffer[buffer_length - erase_unnecessarylettersindex] = 0;
			}
			return *this;
		}
		//This is only called from Vector
		String& String::operator= (const char* text) {
			unsigned int i = 0;
			while (text[i] != 0) {
				i++;
			}
			buffer_length = i + 1;
			if (Allocator == nullptr) {
				std::cout << "Allocator is nullptr!\n";
			}
			pointer_toBuffer = (char*)Allocator->Allocate_MemoryBlock(buffer_length * sizeof(char));
			memcpy(pointer_toBuffer, text, sizeof(char) * buffer_length);
			return *this;
		}
		String operator+ (const String& c1, const String& c2) {
			if (c1.Allocator == c2.Allocator) {
				String Final(c1.Allocator);
				Final.pointer_toBuffer = (char*)c1.Allocator->Allocate_MemoryBlock(c1.buffer_length + c2.buffer_length - 1);
				Final.buffer_length = c1.buffer_length + c2.buffer_length - 1;
				for (int i = 0; i < c1.buffer_length - 1; i++) {
					Final[i] = c1[i];
				}
				for (unsigned int i = 0; i < c2.buffer_length; i++) {
					Final[i + c1.buffer_length - 1] = c2[i];
				}
				return Final;
			}
			else {
				return String(LASTUSEDALLOCATOR);
			}
		}
		char& String::operator[] (unsigned int index) const {
			return pointer_toBuffer[index];
		}
		bool String::operator== (const char* text) const {
			if (pointer_toBuffer == nullptr) {
				return false;
			}
			for (std::size_t i = 0; i < buffer_length; i++) {
				if (text[i] == 0 || text[i] != pointer_toBuffer[i]) {
					return false;
				}
			}
			if (text[buffer_length - 1] != 0) {
				return false;
			}
			return true;
		}
		bool String::operator!=(const char* text) const {
			return !(*this == text);
		}
		String::operator const char* () const {
			return pointer_toBuffer;
		}
		std::ostream& operator<<(std::ostream& os, const String& string_toshow) {
			const char* pointer = string_toshow.pointer_toBuffer;
			os << string_toshow.pointer_toBuffer;
			return os;
		}
		const char* String::c_str() const {
			return *this;
		}
		std::size_t String::find_lastof(char letter) const {
			for (std::size_t index = buffer_length - 1; index > 0; index) {
				index--;
				if (letter == pointer_toBuffer[index]) {
					return index;
				}
			}
			//Means failed!
			return buffer_length;
		}
		std::size_t String::length() const {
			return buffer_length;
		}
		String* String::substr(std::size_t from, std::size_t to) const {
			String* str = new (LASTUSEDALLOCATOR) String();
			size_t length = to - from + 2;
			str->pointer_toBuffer = (char*)str->Allocator->Allocate_MemoryBlock(length * sizeof(char));
			str->buffer_length = length;
			memcpy(str->pointer_toBuffer, pointer_toBuffer + (from * sizeof(char)), length - 1);
			str->pointer_toBuffer[buffer_length - 1] = 0;
			return str;
		}
		char* Text_Add (const char* c1, const char* c2) {
			unsigned int c1length = 0;
			while (c1[c1length] != 0) {
				c1length++;
			}
			c1length += 1;
			unsigned int c2length = 0;
			while (c2[c2length] != 0) {
				c2length++;
			}
			c2length += 1;
			char* FinalText = new (LASTUSEDALLOCATOR) char[c1length + c2length - 1];
			memcpy(FinalText, c1, (c1length - 1) * sizeof(char));
			memcpy(FinalText + (c1length - 1) * sizeof(char), c2, c2length * sizeof(char));
			return FinalText;
		}
	}
}