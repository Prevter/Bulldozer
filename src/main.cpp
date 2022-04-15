#include "includes.h"

void InitializeConsole() {
    AllocConsole();
    FILE* f; freopen_s(&f, "CONOUT$", "w", stdout);
}

DWORD WINAPI MainThread(LPVOID param) {
    std::ifstream configFile("config.json");
    json config;
        
    if (configFile.fail()) {
        InitializeConsole();
        std::cerr << "Config file was not found!\n";
    }
    else {
        configFile >> config;
        configFile.close();
        if (config["console"].get<bool>()) {
            InitializeConsole();
        }
    }

    if (!std::filesystem::is_directory("dll") || !std::filesystem::exists("dll")) {
        std::filesystem::create_directory("dll");
    }

    std::cout << "    ____            __  __      __                         \n";
    std::cout << "   / __ )  __  __  / / / / ____/ / ____  ____  ___    _____\n";
    std::cout << "  / __  | / / / / / / / / / __  / / __ \\/_  / / _ \\  / ___/\n";
    std::cout << " / /_/ / / /_/ / / / / / / /_/ / / /_/ / / /_/  __/ / /    \n";
    std::cout << "/_____/  \\__,_/ /_/ /_/  \\__,_/  \\____/ /___/\\___/ /_/     \n";
    std::cout << "Mod loader for Teardown\nVersion 0.9.5\n";

    uintptr_t moduleBase = (uintptr_t)GetModuleHandleA(NULL);
    uintptr_t baseAddress = moduleBase + 0x441780;

    while (true) {
        uintptr_t ptr = *(uintptr_t*)(baseAddress);

        if (ptr != NULL) {
            Game = (Teardown*)ptr;
            break;
        }

        Sleep(1000);
    }

    std::cout << "[Bulldozer] Loading game memory [ OK ]\n";

    Hooks::InitHooks();
    std::cout << "[Bulldozer] Hooking to game functions [ OK ]\n";
	
    for (const auto& entry : std::filesystem::directory_iterator("dll")) {
        std::string filename = entry.path().string();

        if (filename.substr(filename.find_last_of(".") + 1) == "dll") {
            std::cout << "[Bulldozer] Loading " << filename;

            //std::wstring wname = s2ws(filename);
            HMODULE lib = LoadLibraryA(filename.c_str());
            if (lib == NULL) {
                std::cout << " [ FAIL ]\n";
                continue;
            }
            std::cout << " [ OK ]\n";

            ((LoadMemory)GetProcAddress(lib, "loadMemory"))(Game);

            InitCallback initCallback = (InitCallback)GetProcAddress(lib, "Init");
            if (initCallback != NULL) 
                initCallback();

            FrameCallback frameMethod = (FrameCallback)GetProcAddress(lib, "Frame");
            if (frameMethod != NULL) 
                Hooks::FrameCallbacks.push_back(frameMethod);
        }
    }

    std::ofstream o("config.json");
    o << std::setw(4) << config << std::endl;
    o.close();
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
        DisableThreadLibraryCalls(hModule);
        break;
    default:
        break;
    }
    return TRUE;
}