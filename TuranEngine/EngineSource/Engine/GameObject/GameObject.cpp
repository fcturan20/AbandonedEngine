#include "GameObject.h"

vector<GameObject*> GameObject::ALL_GAMEOBJECTs = vector<GameObject*>();

GameObject::GameObject() {
	cout << "An GameObject is created!\n";
	ALL_GAMEOBJECTs.push_back(this);
}

void GameObject::Translate(vec3 new_position) {
	vec3 POSITION_CHANGE = new_position - POSITION;
	POSITION = new_position;
	for (EngineComponent* COMPONENT : COMPONENTs) {
		COMPONENT->Translate(COMPONENT->POSITION + POSITION_CHANGE);
	}
}

void GameObject::Rotate(vec3 new_rotation) {
	vec3 ROTATION_CHANGE = new_rotation - ROTATION;
	ROTATION = new_rotation;
	for (EngineComponent* COMPONENT : COMPONENTs) {
		COMPONENT->Rotate(COMPONENT->ROTATION + ROTATION_CHANGE);
	}
}

//Scale all GameObject with respect to (GameObject Scale/EngineComponent Scale) ratio!
void GameObject::Scale(vec3 new_scale) {
	vec3 SCALE_CHANGE_RATIO = new_scale / SCALE;
	SCALE = new_scale;
	for (EngineComponent* COMPONENT : COMPONENTs) {
		COMPONENT->Scale(COMPONENT->SCALE * SCALE_CHANGE_RATIO);
	}
}