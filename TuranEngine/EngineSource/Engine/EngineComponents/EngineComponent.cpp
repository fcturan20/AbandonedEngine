#include "EngineComponent.h"


EngineComponent::EngineComponent(ENGINE_COMPs type, vec3 position) : COMPONENT_TYPE(type), POSITION(position) {
	cout << "An EngineComponent is created of type: " << type << "!\n";
}

//Transport a component to a new position!
void EngineComponent::Translate(vec3 new_position) {
	if (POSITION != new_position) {
		POSITION = new_position;
		is_TRANSFORM_CHANGED = true;
	}
}

//Rotate a component to a new rotation!
void EngineComponent::Rotate(vec3 new_rotation) {
	if (ROTATION != new_rotation) {
		ROTATION = new_rotation;
		is_TRANSFORM_CHANGED = true;
	}
}

//Scale a component to a new rotation!
void EngineComponent::Scale(vec3 new_scale) {
	if (SCALE != new_scale) {
		SCALE = new_scale;
		is_TRANSFORM_CHANGED = true;
	}
}