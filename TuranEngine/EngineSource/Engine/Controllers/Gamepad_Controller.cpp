#include "Gamepad_Controller.h"

Gamepad_Controller::Gamepad_Controller(int Gamepad_ID) : ID(Gamepad_ID) {

}

Gamepad_Controller::~Gamepad_Controller() {
	for (int i = 0; i < ALL_GAMEPADs.size(); i++) {
		Gamepad_Controller* GAMEPAD = ALL_GAMEPADs[i];
		if (this == GAMEPAD) {
			ALL_GAMEPADs.erase(ALL_GAMEPADs.begin() + i);
		}
	}
}

void Gamepad_Controller::Update_Inputs() {

}


Gamepad_Controller* Gamepad_Controller::Find_Gamepad_byID(int Gamepad_ID) {
	for (Gamepad_Controller* GAMEPAD : ALL_GAMEPADs) {
		if (GAMEPAD->ID == Gamepad_ID)
			return GAMEPAD;
	}
	cout << "Error: Intended Gamepad: " << Gamepad_ID << " can't be found!\n";
}

vector<Gamepad_Controller*> ALL_GAMEPADs = vector<Gamepad_Controller*>();