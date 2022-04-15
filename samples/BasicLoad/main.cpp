#include <teardown.h>

callback Init() {
	std::cout << "[BasicLoad] Window size: " << Game->Width << "x" << Game->Height << "\n";
	return 0;
}

callback Frame() {
	std::cout << "[BasicLoad] Game data: " << "\n";
	std::cout << "\t" << "Resolution: " << Game->Width << "x" << Game->Height << "\n";
	std::cout << "\t" << "Current state: " << (uint32_t)Game->CurrentState << "\n";
	std::cout << "\t" << "Is playing: " << Game->Playing << "\n";

	return 0;
}