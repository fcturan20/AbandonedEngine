#include "Controller_Center.h"

void Controller_Center::Take_Inputs() {
	//	KEYBOARD.Update_Inputs();

	for (Gamepad_Controller* JOYSTICK : JOYSTICKs) {
		JOYSTICK->Update_Inputs();
	}

}
vector<Gamepad_Controller*> Controller_Center::JOYSTICKs = vector<Gamepad_Controller*>();