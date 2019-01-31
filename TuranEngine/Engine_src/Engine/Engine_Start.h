#pragma once


class Engine_C Engine {
public:
	void StartEngine() {
		std::cout << "Engine started\n";
	}

	void StartRendering() {
		cout << "Engine's RHI starts\n";
		RenderHardware.StartRendering();
	}
};
