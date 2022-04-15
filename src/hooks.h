#pragma once
#include <iostream>
#include <vector>
#include <MinHook.h>
#include <GLFW/glfw3.h>
#include <gl/gl.h>

typedef int(__cdecl* LoadMemory)(void* ptr);
typedef int(__cdecl* InitCallback)(void);

typedef int(__cdecl* FrameCallback)(HWND GameWindow);
typedef BOOL(__stdcall* wglSwapBuffers)(_In_ HDC hDc);

class Hooks {
public:
	inline static bool HandlersInitialized = false;

	inline static std::vector<FrameCallback> FrameCallbacks;
	static BOOL WINAPI HookedWglSwapBuffers(_In_ HDC hDc);

	static void InitHooks();
};




