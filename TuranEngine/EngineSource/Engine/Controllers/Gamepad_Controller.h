#pragma once
#include "Engine_Includes.h"

class ENGINE Gamepad_Controller {
	friend class Controller_Center;

	vector<Gamepad_Controller*> ALL_GAMEPADs;
	Gamepad_Controller(int Gamepad_ID);

	Gamepad_Controller* Find_Gamepad_byID(int Gamepad_ID);

	~Gamepad_Controller();

	//Controller Name given by Windows Driver
	string Controller_Name;

	//ID in active Controllers 
	unsigned char ID;
	void Update_Inputs();
};
