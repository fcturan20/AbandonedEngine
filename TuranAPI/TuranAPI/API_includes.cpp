#include "API_includes.h"

void TuranAPI::Breakpoint() {
	char input;
	cout << "Application hit a breakpoint, would you like to continue? (Note: Be careful, application may crash!) \nTo continue: enter y, to close: enter x \nInput: ";
	cin >> input;
	if (input == 'y') {
		return;
	}
	else if (input == 'x') {
		exit(EXIT_FAILURE);
	}
	else {
		cout << "Wrong input:\n";
		TuranAPI::Breakpoint();
	}
}

template<typename T>
unsigned int TuranAPI::Delete_Items_from_Vector(vector<T>* Vector_to_EraseSomething, vector<bool>* ShouldErase_forEachIndex, unsigned int start_index) {
	if (Vector_to_EraseSomething->size() != ShouldErase_forEachIndex->size()) {
		cout << "Error: in Delete Items from Vector(), 2 vectors should have same size!\n";
		TuranAPI::Breakpoint();
	}
	unsigned int i = start_index;
	for (i = start_index; i < Vector_to_EraseSomething->size(); i++) {
		bool should_erase = (*ShouldErase_forEachIndex)[i];
		if (should_erase) {
			Vector_to_EraseSomething->erase(Vector_to_EraseSomething->begin() + i);
			ShouldErase_forEachIndex->erase(ShouldErase_forEachIndex->begin() + i);
			i = Delete_Items_from_Vector<T>(Vector_to_EraseSomething, ShouldErase_forEachIndex, i);
		}
	}
	return i;
}