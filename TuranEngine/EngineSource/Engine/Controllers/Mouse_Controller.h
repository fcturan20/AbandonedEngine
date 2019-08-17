#pragma once
#include "Engine_Includes.h"

//For now, just supported
enum MOUSE_BUTTONs : unsigned char {
	MOUSE_LEFT_CLICK = 0,
	MOUSE_RIGHT_CLICK = 1,
	MOUSE_WHEEL_CLICK = 2
};

enum MOUSE_INPUT_MODE : unsigned char {
	//Creates a unlimited surface to take every motion input of mouse!
	//This means, your mouse input positions will not be limited to window size!
	MOUSE_INPUT_UNLIMITED = 0,
	//Window size based input mode, but cursor is hidden!
	//It is same thing as normal, but only hidden!
	MOUSE_INPUT_HIDDEN = 1,
	//Default input mode, window size based input mode!
	//Cursor can be seen and input surface is limited to window size!
	MOUSE_INPUT_NORMAL = 2
};

class ENGINE Mouse_Controller {
private:
	friend class OGL3_SYS;

	static vector<MOUSE_BUTTONs> ALL_BUTTONs;
	static vector<bool> IS_BUTTON_PRESSED;
	//This variable is accessed every frame by GLFW to change cursor mode!
	static MOUSE_INPUT_MODE CURSOR_MODE;

	static unsigned int Get_BUTTON_vectorindex(MOUSE_BUTTONs BUTTON);

	//Mouse based variables to calculate position changes of cursor!
	static vec2 MOUSE_CURRENT_POSITION;
	static vector<vec2*> POSITION_RECORDs;
	static void Start_Cursor_Mode(MOUSE_INPUT_MODE cursor_mode);
	static void Stop_Cursor_Mode(MOUSE_INPUT_MODE cursor_mode);
public:
	Mouse_Controller() {
		ALL_BUTTONs.push_back(MOUSE_LEFT_CLICK); IS_BUTTON_PRESSED.push_back(false);
		ALL_BUTTONs.push_back(MOUSE_RIGHT_CLICK); IS_BUTTON_PRESSED.push_back(false);
		ALL_BUTTONs.push_back(MOUSE_WHEEL_CLICK); IS_BUTTON_PRESSED.push_back(false);
	}

	static void Set_Button_is_Pressed(MOUSE_BUTTONs KEY, bool is_Key_Pressed);

	static bool Is_Button_Pressed(MOUSE_BUTTONs BUTTON);

	static vector<MOUSE_BUTTONs> Return_ALL_Buttons();


	//Returns the Recording's index to get recording info or stop the recording in other frames!
	static vec2* Start_Position_Recording(MOUSE_INPUT_MODE cursor_mode);

	//Get position by recording start position pointer! I did this because an index would be changed if recording vector removed an element.
	static vec2 Get_Position_Offset(vec2* mouse_last_position);

	//Stop calculating position recording! This should be called when you don't want to find a position change of mouse!
	//For example: This is called when releasing mouse - right click not to move or direct camera!
	static void Stop_Position_Recording(vec2* mouse_last_position, MOUSE_INPUT_MODE cursor_mode);
};
