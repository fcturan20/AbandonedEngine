#include "Keyboard_Controller.h"

//Don't forget to push back a IS_KEY_PRESSED, after ALL_KEYs.push_back()!
Keyboard_Controller::Keyboard_Controller() {
	ALL_KEYs.push_back(KEYBOARD_W); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_S); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_A); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_D); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_NP_2); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_NP_4); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_NP_6); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_NP_8); IS_KEY_PRESSED.push_back(false);
	ALL_KEYs.push_back(KEYBOARD_C); IS_KEY_PRESSED.push_back(false);
}

unsigned int Keyboard_Controller::Get_KEY_vectorindex(KEYBOARD_KEYs KEY) {
	for (unsigned int i = 0; i < ALL_KEYs.size(); i++) {
		if (ALL_KEYs[i] == KEY) {
			return i;
		}
	}
	cout << "Error: Intended key isn't in ALL_KEYs vector, returning 0!\n";
	return 0;
}

void Keyboard_Controller::Set_Key_is_Pressed(KEYBOARD_KEYs KEY, bool is_Key_Pressed) {
	//Get bool's vector index by KEY and set status!
	IS_KEY_PRESSED[Get_KEY_vectorindex(KEY)] = is_Key_Pressed;
}

vector<KEYBOARD_KEYs> Keyboard_Controller::Return_ALL_Keys() {
	return ALL_KEYs;
}

bool Keyboard_Controller::Is_Key_Pressed(KEYBOARD_KEYs KEY) {
	return IS_KEY_PRESSED[Get_KEY_vectorindex(KEY)];
}

Keyboard_Controller KEYBOARD_CONTROLLER_OBJ;

vector<KEYBOARD_KEYs> Keyboard_Controller::ALL_KEYs = vector<KEYBOARD_KEYs>();
vector<bool> Keyboard_Controller::IS_KEY_PRESSED = vector<bool>();