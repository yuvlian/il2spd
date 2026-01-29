#include "config.h"
#include "il2cpp.h"
#include "input.h"
#include "timescale.h"
#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

void wait_exit() {
    printf("\nPress ENTER to exit...");
    getchar();
    exit(0);
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);

    #define CHECK_INIT(func) \
    if (!(func)) { \
        wait_exit(); \
    }

    CHECK_INIT(init_config())
    CHECK_INIT(init_game_assembly())
    CHECK_INIT(init_il2cpp())
    CHECK_INIT(init_input())
    CHECK_INIT(init_time_scale())

    #undef CHECK_INIT

    printf("il2spd initialized successfully.\n");
    printf("remember, spd too high might get you stuck or break the game!\n");
    printf("keybinds:\n");
    printf("  toggle: %s\n", g_Config.toggle_key);
    printf("  increase: %s\n", g_Config.incr_key);
    printf("  decrease: %s\n", g_Config.decr_key);

    bool speedEnabled = false;
    bool stateChanged = false;
    float speedValue = g_Config.start_spd_val;

    // check todo in input.c i guess
    while (1) {
        stateChanged = false;

        if (get_key_down(g_Config.toggle_key)) {
            stateChanged = true;
            speedEnabled = !speedEnabled;
            if (!speedEnabled) set_time_scale(1.0);
        }

        if (get_key_down(g_Config.incr_key)) {
            stateChanged = true;
            speedValue += g_Config.mod_spd_val;
        }

        if (get_key_down(g_Config.decr_key)) {
            stateChanged = true;
            speedValue -= g_Config.mod_spd_val;
        }

        if (speedValue < 0.1f) {
            stateChanged = true;
            speedValue = 1.0f;
        }

        if (stateChanged) {
            printf(
                "il2spd: %s | spd = %.2f\n",
                speedEnabled ? "on " : "off", 
                speedValue
            );
        }

        if (speedEnabled) {
            set_time_scale(speedValue);
        }

        Sleep(1);
    }

    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    DisableThreadLibraryCalls(hinstDLL);
    if (fdwReason == DLL_PROCESS_ATTACH) {
        HANDLE hThread = CreateThread(NULL, 0, MainThread, NULL, 0, NULL);
        if (hThread) CloseHandle(hThread);
    }
    return TRUE;
}
