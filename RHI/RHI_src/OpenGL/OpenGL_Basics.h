#pragma once

class RHI_C IOpenGL {
public:
	void SetMinimumVersion() {
		std::cout << "OpenGL minimum version is set\n";
	}
};

IOpenGL OpenGL;