#pragma once
#include "Includes.h"
/*Input System:
1) GFX_API specific class (for example: OGL3_SYS) stores takes inputs (Window close operations, key inputs, window size change etc.) every frame!
2) This class gets key inputs every frame with Take_Inputs(), this function is called by Take_Inputs() from GFX_API specific class!
3) This class only stores key inputs and controllers to distribute all around the Turan Engine so every system can access it!
4) This system allows us not to include GFX_API in every header that we want to access key inputs!
Note: Controller system is one of the first defined systems in all application (In main.h), so each system can access it!
*/
//#include "Keyboard_Controller.h"
#include "Gamepad_Controller.h"


class Controller_Center {
	//Keyboard_Controller KEYBOARD;
	vector<Gamepad_Controller*> JOYSTICKs;

public:
	void Take_Inputs() {
	//	KEYBOARD.Update_Inputs();

		for (Gamepad_Controller* JOYSTICK : JOYSTICKs) {
			JOYSTICK->Update_Inputs();
		}
		
	}

	//vector<KEYBOARD_KEYs> Get_Pressed_Keyboard_Keys() {
	//	return KEYBOARD.Pressed_Keys;
	//}
};

Controller_Center CONTROLLER_CENTER;