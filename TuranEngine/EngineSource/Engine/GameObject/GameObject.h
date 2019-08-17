#pragma once
#include "Engine_Includes.h"

#include "Engine/EngineComponents/EngineComponent.h"

class ENGINE GameObject
{
	static vector<GameObject*> ALL_GAMEOBJECTs;
	vec3 POSITION, ROTATION, SCALE;
	
	vector<EngineComponent*> COMPONENTs;
public:
	GameObject();

	void Translate(vec3 new_position);
	void Rotate(vec3 new_rotation);
	void Scale(vec3 new_scale);
};

