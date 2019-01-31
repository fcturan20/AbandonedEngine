#pragma once
#include <iostream>


using namespace std;

class RHI_C RHI {
public:
	void StartRendering() {
		std::cout << "Rendering started\n";
	}

	void SetOpenGLversion() {
		OpenGL.SetMinimumVersion();
	}
};

RHI_FUNC int Start() {
	cout << "Started Something\n";
	return 1;
}