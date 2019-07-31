#pragma once
#include "Includes.h"

#include "Engine/Controllers/Keyboard_Controller.h"

#include "EngineComponent.h"


class Camera : public EngineComponent {
	enum CAMERA_ACTIONs : unsigned char {
		CAMERA_MOVE_FORWARD = 0,
		CAMERA_MOVE_BACKWARD = 1,
		CAMERA_MOVE_LEFT = 2,
		CAMERA_MOVE_RIGHT = 3,
		CAMERA_MOVE_UPWARD = 4,
		CAMERA_MOVE_BELOW = 5
	};
	vector<CAMERA_ACTIONs> ACTIONs;

	vec3 POSITION, FRONT_VECTOR, RIGHT_VECTOR, UP_VECTOR, TARGET;
	mat4 VIEW_MATRIX;
	float FOV_in_RADIANS = 45.0f, ASPECT_RATIO = float(1920 / 1080), NEAR_FRUSTUM = 0.1f, FAR_FRUSTUM = 1000.0f;
	mat4 PROJECTION_MATRIX;

	//Mouse Entegration variables!

	bool ACTIONs_ACTIVE = false, REVERT_CAMERA_Y = true;
	vec2* mouse_last_position; //Please don't read or change this variable!
	vec2 mouse_position_offset;
	float Mouse_Sensitivity = 0.05f, Mouse_Yaw = 0, Mouse_Pitch = 0;


	//Update View and Projection matrixes!
	void Update_Camera_Matrixes();
	void Do_ACTIONs();
	void Find_ACTIONs();
	void Calculate_Camera_Direction();
public:
	Camera(vec3 position) : POSITION(position), TARGET(0, 0, 1) {
		Update_Camera_Matrixes();
	}

	mat4 Return_View_Matrix() {
		return VIEW_MATRIX;
	}
	
	mat4 Return_Projection_Matrix() {
		return PROJECTION_MATRIX;
	}

	void Take_Inputs();
};

void Camera::Update_Camera_Matrixes() {
	vec3 world_up(0, 1, 0);
	FRONT_VECTOR = normalize(TARGET);
	RIGHT_VECTOR = -normalize(cross(world_up, FRONT_VECTOR));
	UP_VECTOR = -normalize(cross(FRONT_VECTOR, RIGHT_VECTOR));

	mat4 view;
	VIEW_MATRIX = view;
	VIEW_MATRIX = lookAt(POSITION, FRONT_VECTOR + POSITION, world_up);

	PROJECTION_MATRIX = perspective(radians(FOV_in_RADIANS), ASPECT_RATIO, NEAR_FRUSTUM, FAR_FRUSTUM);
}

void Camera::Take_Inputs() {
	//Erase all of the actions related to last frame!
	vector<CAMERA_ACTIONs> empty_actions;
	ACTIONs = empty_actions;

	//If right click is pressed now!
	if (Mouse_Controller::Is_Button_Pressed(MOUSE_RIGHT_CLICK)) {
		//If it wasn't not pressed last frame, start recording position offsets!
		if (!ACTIONs_ACTIVE) {
			mouse_position_offset = vec2(0);
			mouse_last_position = Mouse_Controller::Start_Position_Recording(MOUSE_INPUT_UNLIMITED);
			ACTIONs_ACTIVE = true;
		}
		//If it was pressed last frame or even before, get position offset!
		else {
			mouse_position_offset = Mouse_Controller::Get_Position_Offset(mouse_last_position);
			mouse_position_offset.y = -mouse_position_offset.y;

			//Apply sensitivity to position offset to drop camera direction changing magnitude!
			mouse_position_offset *= Mouse_Sensitivity;
		}
	}
	//If right click isn't pressed now!
	else {
		//If it was pressed last frame, stop actions!
		if (ACTIONs_ACTIVE) {
			mouse_position_offset = vec2(0);
			Mouse_Controller::Stop_Position_Recording(mouse_last_position, MOUSE_INPUT_UNLIMITED);
			ACTIONs_ACTIVE = false;
		}
	}

	//If right click is pressed, control camera!
	if (ACTIONs_ACTIVE) {
		Find_ACTIONs();
		Do_ACTIONs();
		Calculate_Camera_Direction();
		//After doing all of the camera actions, update camera matrixes!
		Update_Camera_Matrixes();
	}
}


void Camera::Calculate_Camera_Direction() {
	//Calculate mouse position angle in yaw and pitch (But it is a tricky calculation, not a real angle)! These variables does never restore to defaults, because it would cause a camera direction jump!
	Mouse_Yaw += mouse_position_offset.x;
	Mouse_Pitch += mouse_position_offset.y;

	//Limit Pitch direction to 90 degrees, because we don't want our camera to upside-down!
	if (Mouse_Pitch > 89.0f) {
		Mouse_Pitch = 89.0f;
	}
	else if (Mouse_Pitch < -89.0f) {
		Mouse_Pitch = -89.0f;
	}

	cout << "Mouse Yaw: " << Mouse_Yaw << "\nMouse Pitch: " << Mouse_Pitch << endl;

	if (Mouse_Yaw == 0 && Mouse_Pitch == 0) {
		return;
	}
	else {
		//Set target direction!
		TARGET.x = cos(radians(Mouse_Pitch)) * cos(radians(Mouse_Yaw));
		TARGET.y = sin(radians(Mouse_Pitch));
		TARGET.z = cos(radians(Mouse_Pitch)) * sin(radians(Mouse_Yaw));
	}
}


void Camera::Do_ACTIONs() {
	for (CAMERA_ACTIONs ACTION : ACTIONs) {
		if (ACTION == CAMERA_MOVE_FORWARD) {
			POSITION += FRONT_VECTOR;
		}
		if (ACTION == CAMERA_MOVE_BACKWARD) {
			POSITION -= FRONT_VECTOR;
		}
		if (ACTION == CAMERA_MOVE_LEFT) {
			POSITION -= RIGHT_VECTOR;
		}
		if (ACTION == CAMERA_MOVE_RIGHT) {
			POSITION += RIGHT_VECTOR;
		}
		if (ACTION == CAMERA_MOVE_UPWARD) {
			POSITION += UP_VECTOR;
		}
		if (ACTION == CAMERA_MOVE_BELOW) {
			POSITION -= UP_VECTOR;
		}
	}
	if (ACTIONs.size() > 0) {
		cout << "Position:\nX:" << POSITION.x << "\nY: " << POSITION.y << "\nZ: " << POSITION.z << endl;
	}
}

void Camera::Find_ACTIONs() {
	cout << "Camera is taking inputs!\n";
	vector<KEYBOARD_KEYs> all_keys = Keyboard_Controller::Return_ALL_Keys();
	for (KEYBOARD_KEYs key : all_keys) {
		if (key == KEYBOARD_W && Keyboard_Controller::Is_Key_Pressed(KEYBOARD_W)) {
			ACTIONs.push_back(CAMERA_MOVE_FORWARD);
		}
		if (key == KEYBOARD_S && Keyboard_Controller::Is_Key_Pressed(KEYBOARD_S)) {
			ACTIONs.push_back(CAMERA_MOVE_BACKWARD);
		}
		if (key == KEYBOARD_A && Keyboard_Controller::Is_Key_Pressed(KEYBOARD_A)) {
			ACTIONs.push_back(CAMERA_MOVE_LEFT);
		}
		if (key == KEYBOARD_D && Keyboard_Controller::Is_Key_Pressed(KEYBOARD_D)) {
			ACTIONs.push_back(CAMERA_MOVE_RIGHT);
		}
		if (key == KEYBOARD_NP_8 && Keyboard_Controller::Is_Key_Pressed(KEYBOARD_NP_8)) {
			ACTIONs.push_back(CAMERA_MOVE_UPWARD);
		}
		if (key == KEYBOARD_NP_2 && Keyboard_Controller::Is_Key_Pressed(KEYBOARD_NP_2)) {
			ACTIONs.push_back(CAMERA_MOVE_BELOW);
		}
	}
}