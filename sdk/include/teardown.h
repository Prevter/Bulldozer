#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>

#define callback extern "C" __declspec(dllexport) int

enum class GameState : uint32_t {
	Splash = 1,
	Menu,
	UI,
	Playing,
	Editing
};

class Scene {
public:
	char pad_0008[96]; //0x0008
	void* SmokeParticles; //0x0068
	void* N00001B40; //0x0070
	void* WaterParticles; //0x0078
	void* PlainParticles; //0x0080
	void* FireSystem; //0x0088

	virtual void Function0();
	virtual void Function1();
	virtual void Function2();
	virtual void Function3();
	virtual void Function4();
	virtual void Function5();
	virtual void Function6();
	virtual void Function7();
	virtual void Function8();
	virtual void Function9();
};

class Teardown {
public:
	int32_t Width; //0x0000
	int32_t Height; //0x0004
	GameState CurrentState; //0x0008
	GameState TargetState; //0x000C
	float LoadingEffect; //0x0010
	bool Playing; //0x0014
	char pad_0015[3]; //0x0015
	float LoadingEffect2; //0x0018
	bool MapOpened; //0x001C
	char pad_001D[43]; //0x001D
	class Scene* Scene; //0x0048
	char pad_0050[212]; //0x0050
	bool Paused; //0x0124
	char pad_0125[99]; //0x0125
};

extern Teardown* Game;
extern "C" __declspec(dllexport) void loadMemory(Teardown* ptr);