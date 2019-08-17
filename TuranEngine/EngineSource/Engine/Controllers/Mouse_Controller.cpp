#include "Mouse_Controller.h"


unsigned int Mouse_Controller::Get_BUTTON_vectorindex(MOUSE_BUTTONs BUTTON) {
	for (unsigned int i = 0; i < ALL_BUTTONs.size(); i++) {
		if (ALL_BUTTONs[i] == BUTTON) {
			return i;
		}
	}
	cout << "Error: Intended key isn't in ALL_KEYs vector, returning 0!\n";
	return 0;
}

vector<MOUSE_BUTTONs> Mouse_Controller::Return_ALL_Buttons() {
	return ALL_BUTTONs;
}
void Mouse_Controller::Set_Button_is_Pressed(MOUSE_BUTTONs KEY, bool is_Key_Pressed) {
	//Get bool's vector index by KEY and set status!
	IS_BUTTON_PRESSED[Get_BUTTON_vectorindex(KEY)] = is_Key_Pressed;
}

bool Mouse_Controller::Is_Button_Pressed(MOUSE_BUTTONs BUTTON) {
	return IS_BUTTON_PRESSED[Get_BUTTON_vectorindex(BUTTON)];
}


void Mouse_Controller::Start_Cursor_Mode(MOUSE_INPUT_MODE cursor_mode) {
	if (CURSOR_MODE == MOUSE_INPUT_UNLIMITED) {
		cout << "You tried to start a position recording with a different Cursor Mode!\n";
		cout << "Current Cursor Mode is Unlimited Surface, so you can't change cursor mode until caller of Unlimited Surface deactivate the mode!\n";
		cout << "This means, changing Cursor Mode from Unlimited Surface to another isn't supported for TuranEngine!\n";
		cout << "Cursor Mode is still Unlimited Surface!\n";
		return;
	}
	else {
		cout << "Changed the Cursor Mode!\n";
		CURSOR_MODE = cursor_mode;
	}
}

void Mouse_Controller::Stop_Cursor_Mode(MOUSE_INPUT_MODE cursor_mode) {
	cout << "New Mode is Normal mode!\n";
	CURSOR_MODE = MOUSE_INPUT_NORMAL;
}




//Returns the Recording's index to get recording info or stop the recording in other frames!
vec2* Mouse_Controller::Start_Position_Recording(MOUSE_INPUT_MODE cursor_mode) {
	//Set current mouse position as starting position for recording, because we want to calculate offsets from when we start recording!
	vec2* mouse_start_point = new vec2(MOUSE_CURRENT_POSITION);
	POSITION_RECORDs.push_back(mouse_start_point);

	Start_Cursor_Mode(cursor_mode);

	return mouse_start_point;
}

void Mouse_Controller::Stop_Position_Recording(vec2* mouse_last_position, MOUSE_INPUT_MODE cursor_mode) {
	if (mouse_last_position == nullptr) {
		cout << "Error: You try to stop a position recording of a deleted recording!\n";
	}
	for (unsigned int i = 0; i < POSITION_RECORDs.size(); i++) {
		vec2* vec = POSITION_RECORDs[i];
		if (vec == mouse_last_position) {
			delete vec;
			vec = nullptr;
			//Delete record from vector!
			POSITION_RECORDs.erase(POSITION_RECORDs.begin() + i);
		}
	}
	Stop_Cursor_Mode(cursor_mode);
	cout << "Stopped position recording successfully!\n";
}

vec2 Mouse_Controller::Get_Position_Offset(vec2* mouse_last_position) {
	if (mouse_last_position == nullptr) {
		cout << "Error: You try to get position offset of a deleted recording!\n";
		return vec2(0);
	}
	//Return offset!
	vec2 offset = MOUSE_CURRENT_POSITION - *mouse_last_position;
	*mouse_last_position = MOUSE_CURRENT_POSITION;

	cout << "Offset X: " << offset.x << "\nOffset Y: " << offset.y << endl;
	return offset;
}

vector<MOUSE_BUTTONs> Mouse_Controller::ALL_BUTTONs = vector<MOUSE_BUTTONs>();
vector<bool> Mouse_Controller::IS_BUTTON_PRESSED = vector<bool>();
vector<vec2*> Mouse_Controller::POSITION_RECORDs = vector<vec2*>();
vec2 Mouse_Controller::MOUSE_CURRENT_POSITION = vec2(0);
MOUSE_INPUT_MODE Mouse_Controller::CURSOR_MODE = MOUSE_INPUT_NORMAL;

Mouse_Controller MOUSE_CONTROLLER_OBJ;