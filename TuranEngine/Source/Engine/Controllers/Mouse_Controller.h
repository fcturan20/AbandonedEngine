#pragma once
#include "Includes.h"

//For now, just supported
enum MOUSE_BUTTONs : unsigned char {
	MOUSE_LEFT_CLICK = 0,
	MOUSE_RIGHT_CLICK = 1,
	MOUSE_WHEEL_CLICK = 2
};

class Mouse_Controller {
private:
	friend class OGL3_SYS;

	static vector<MOUSE_BUTTONs> ALL_BUTTONs;
	static vector<bool> IS_BUTTON_PRESSED;

	static unsigned int Get_BUTTON_vectorindex(MOUSE_BUTTONs BUTTON) {
		for (unsigned int i = 0; i < ALL_BUTTONs.size(); i++) {
			if (ALL_BUTTONs[i] == BUTTON) {
				return i;
			}
		}
		cout << "Error: Intended key isn't in ALL_KEYs vector, returning 0!\n";
		return 0;
	}

	//Mouse based variables to calculate position changes of cursor!
	static vec2 mouse_current_position;
	static vector<vec2*> Position_Records;
public:
	Mouse_Controller() {
		ALL_BUTTONs.push_back(MOUSE_LEFT_CLICK); IS_BUTTON_PRESSED.push_back(false);
		ALL_BUTTONs.push_back(MOUSE_RIGHT_CLICK); IS_BUTTON_PRESSED.push_back(false);
		ALL_BUTTONs.push_back(MOUSE_WHEEL_CLICK); IS_BUTTON_PRESSED.push_back(false);
	}

	static void Set_Button_is_Pressed(MOUSE_BUTTONs KEY, bool is_Key_Pressed) {
		//Get bool's vector index by KEY and set status!
		IS_BUTTON_PRESSED[Get_BUTTON_vectorindex(KEY)] = is_Key_Pressed;
	}

	static bool Is_Button_Pressed(MOUSE_BUTTONs BUTTON) {
		return IS_BUTTON_PRESSED[Get_BUTTON_vectorindex(BUTTON)];
	}

	static vector<MOUSE_BUTTONs> Return_ALL_Buttons() {
		return ALL_BUTTONs;
	}

	//Returns the Recording's index to get recording info or stop the recording in other frames!
	static vec2* Start_Position_Recording() {
		//Set current mouse position as starting position for recording, because we want to calculate offsets from when we start recording!
		vec2* mouse_start_point = new vec2(mouse_current_position);
		Position_Records.push_back(mouse_start_point);

		return mouse_start_point;
	}

	//Get position by recording start position pointer! I did this because an index would be changed if recording vector removed an element.
	static vec2 Get_Position_Offset(vec2* mouse_last_position) {
		if (mouse_last_position == nullptr) {
			cout << "Error: You try to get position offset of a deleted recording!\n";
			return vec2(0);
		}
		//Return offset!
		vec2 offset = mouse_current_position - *mouse_last_position;
		*mouse_last_position = mouse_current_position;

		cout << "Offset X: " << offset.x << "\nOffset Y: " << offset.y << endl;
		return offset;
	}

	//Stop calculating position recording! This should be called when you don't want to find a position change of mouse!
	//For example: This is called when releasing mouse - right click not to move or direct camera!
	static void Stop_Position_Recording(vec2* mouse_last_position) {
		if (mouse_last_position == nullptr) {
			cout << "Error: You try to stop a position recording of a deleted recording!\n";
		}
		for (unsigned int i = 0; i < Position_Records.size(); i++) {
			vec2* vec = Position_Records[i];
			if (vec == mouse_last_position) {
				delete vec;
				vec = nullptr;
				//Delete record from vector!
				Position_Records.erase(Position_Records.begin() + i);
			}
		}
		cout << "Stopped position recording successfully!\n";
	}
};

vector<MOUSE_BUTTONs> Mouse_Controller::ALL_BUTTONs = vector<MOUSE_BUTTONs>();
vector<bool> Mouse_Controller::IS_BUTTON_PRESSED = vector<bool>();
vector<vec2*> Mouse_Controller::Position_Records = vector<vec2*>();
vec2 Mouse_Controller::mouse_current_position = vec2(0);

Mouse_Controller MOUSE_CONTROLLER_OBJ;