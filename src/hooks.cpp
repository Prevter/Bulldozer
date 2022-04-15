#include "hooks.h"
wglSwapBuffers OriginalWglSwapBuffers;
HWND hGameWindow;

void Hooks::InitHooks() {
    HMODULE hMod = GetModuleHandle("opengl32.dll");
    if (hMod)
    {
        void* ptr = GetProcAddress(hMod, "wglSwapBuffers");
        MH_Initialize();
        MH_CreateHook(ptr, HookedWglSwapBuffers, reinterpret_cast<void**>(&OriginalWglSwapBuffers));
        MH_EnableHook(ptr);

        /*MH_CreateHook(&SetCursorPos, &hSetCursorPos, reinterpret_cast<void**>(&oSetCursorPos));
        MH_EnableHook(&SetCursorPos);

        MH_CreateHook(&ShowCursor, &hShowCursor, reinterpret_cast<void**>(&oShowCursor));
        MH_EnableHook(&ShowCursor);*/
    }
}

BOOL WINAPI Hooks::HookedWglSwapBuffers(_In_ HDC hDc)
{
    if (!HandlersInitialized) {
        hGameWindow = WindowFromDC(hDc);
        //hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)windowProc_hook);
        HandlersInitialized = true;
    }

    /*captureMouse = false;
    if (!setupHandlers) {
        hGameWindow = WindowFromDC(hDc);
        hGameWindowProc = (WNDPROC)SetWindowLongPtr(hGameWindow, GWLP_WNDPROC, (LONG_PTR)windowProc_hook);
        setupHandlers = true;
    }

    for (CallFrame cf : FrameUpdaters)
        if (cf(hGameWindow) == 1) captureMouse = true;*/

    for (FrameCallback callback : FrameCallbacks)
        if (callback(hGameWindow) == 1)
            continue;
            //captureMouse = true;
    return OriginalWglSwapBuffers(hDc);
}