#pragma once
#include "Includes.h"

class Gamepad_Controller {
	friend class Controller_Center;

	vector<Gamepad_Controller*> ALL_GAMEPADs;
	Gamepad_Controller(int Gamepad_ID) {

	}

	Gamepad_Controller* Find_Gamepad_byID(int Gamepad_ID) {
		for (Gamepad_Controller* GAMEPAD : ALL_GAMEPADs) {
			if (GAMEPAD->ID == Gamepad_ID)
				return GAMEPAD;
		}
		cout << "Error: Intended Gamepad: " << Gamepad_ID << " can't be found!\n";
	}

	Gamepad_Controller() {
		for (int i = 0; i < ALL_GAMEPADs.size(); i++) {
			Gamepad_Controller* GAMEPAD = ALL_GAMEPADs[i];
			if (this == GAMEPAD) {
				ALL_GAMEPADs.erase(ALL_GAMEPADs.begin() + i);
			}
		}
	}

	//Controller Name given by Windows Driver
	string Controller_Name;

	//ID in active Controllers 
	unsigned char ID;
	void Update_Inputs() {

	}
};

vector<Gamepad_Controller*> ALL_GAMEPADs = vector<Gamepad_Controller*>();