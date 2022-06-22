#include <windows.h>
#include <vector>
#include <d3d9.h>

#include "offsets.h"

#include "cheat.h"
#include "cheats/CrosshairCheat.h"
#include "cheats/TeleportEntityCheat.h"

std::vector<Cheat*> cheats;

typedef HRESULT(APIENTRY* EndSceneFn)(LPDIRECT3DDEVICE9 pDevice);
EndSceneFn org_end_scene = nullptr;

HRESULT APIENTRY EndSceneHook(LPDIRECT3DDEVICE9 pDevice) {
    for (Cheat* cheat : cheats) {
        cheat->EndScene(pDevice);
    }

    return org_end_scene(pDevice);
}

DWORD WINAPI MyThread(LPVOID lpParam) {
    base_address = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));

    // Init cheats
    cheats.push_back(new CrosshairCheat());
    cheats.push_back(new TeleportEntityCheat());

    // Hook DirectX9
    // TODO: On load find what writes to device instead of this addr
    IDirect3DDevice9* device = *(IDirect3DDevice9**)(base_address + DIRECTX9_DEVICE);
    
    // TODO: Clean, this method sucks.
    uintptr_t* device_table  = *reinterpret_cast<uintptr_t**>(device);

    size_t total_functions = 0;
    while (device_table[total_functions])
        total_functions++;

    uintptr_t* new_device_table = new uintptr_t[total_functions];
    memcpy(new_device_table, device_table, sizeof(uintptr_t) * total_functions);

    org_end_scene = reinterpret_cast<EndSceneFn>(device_table[42]);
    new_device_table[42] = reinterpret_cast<uintptr_t>(EndSceneHook);

    *reinterpret_cast<uintptr_t**>(device) = new_device_table;

    return 0;
}

BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(
            NULL,
            0,
            MyThread,
            NULL,
            0,
            NULL
        );
    }
 
    return TRUE;
}

