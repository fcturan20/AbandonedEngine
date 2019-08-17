#pragma once
#include "Engine_Includes.h"


class ENGINE EngineComponent {
	friend class GameObject;
protected:
	vec3 POSITION, ROTATION, SCALE;
	ENGINE_COMPs COMPONENT_TYPE;
	//Is component's transform changed this frame? Default is true because application starts!
	bool is_TRANSFORM_CHANGED = true;

	EngineComponent(ENGINE_COMPs type, vec3 position);
public:
	//Transport a component to a new position!
	void Translate(vec3 new_position);
	//Rotate a component to a new rotation!
	void Rotate(vec3 new_rotation);
	//Scale a component to a new rotation!
	void Scale(vec3 new_scale);
};