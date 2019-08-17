#pragma once
#include "Engine_Includes.h"

#include "Engine/Controllers/Keyboard_Controller.h"

#include "EngineComponent.h"

//This EngineComponent doesn't respond to EngineComponent ROTATION and SCALE!
//In an normal engine Scale would change the Viewport Scale (View Frustum changing)
//And Rotation would change the Viewport's Look Direction, but we will use only one Camera for now!
class ENGINE Camera : public EngineComponent {
	enum CAMERA_ACTIONs : unsigned char {
		CAMERA_MOVE_FORWARD = 0,
		CAMERA_MOVE_BACKWARD = 1,
		CAMERA_MOVE_LEFT = 2,
		CAMERA_MOVE_RIGHT = 3,
		CAMERA_MOVE_UPWARD = 4,
		CAMERA_MOVE_BELOW = 5
	};
	vector<CAMERA_ACTIONs> ACTIONs;

	vec3 FRONT_VECTOR, RIGHT_VECTOR, UP_VECTOR, TARGET;
	mat4 VIEW_MATRIX;
	float FOV_in_ANGLES = 45.0f, ASPECT_RATIO = float(float(1920) / float(1080)), NEAR_FRUSTUM = 0.1f, FAR_FRUSTUM = 1000000.0f;
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
	Camera(vec3 position);

	mat4* Return_View_Matrix();
	mat4* Return_Projection_Matrix();

	void Take_Inputs();
};