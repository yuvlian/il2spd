#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Config g_Config = {0};

static void write_default_config(void) {
    WritePrivateProfileStringA("Settings", "start_spd_val", "1.0", CONFIG_FILE);
    WritePrivateProfileStringA("Settings", "mod_spd_val", "0.1", CONFIG_FILE);
    WritePrivateProfileStringA("Settings", "toggle_key", "LeftShift", CONFIG_FILE);
    WritePrivateProfileStringA("Settings", "incr_key", "UpArrow", CONFIG_FILE);
    WritePrivateProfileStringA("Settings", "decr_key", "DownArrow", CONFIG_FILE);

    WritePrivateProfileStringA("IL2CPP", "il2cpp_assembly_get_image", "", CONFIG_FILE);
    WritePrivateProfileStringA("IL2CPP", "il2cpp_class_from_name", "", CONFIG_FILE);
    WritePrivateProfileStringA("IL2CPP", "il2cpp_class_get_method_from_name", "", CONFIG_FILE);
    WritePrivateProfileStringA("IL2CPP", "il2cpp_domain_get", "", CONFIG_FILE);
    WritePrivateProfileStringA("IL2CPP", "il2cpp_domain_assembly_open", "", CONFIG_FILE);
    WritePrivateProfileStringA("IL2CPP", "il2cpp_runtime_invoke", "", CONFIG_FILE);
    WritePrivateProfileStringA("IL2CPP", "il2cpp_thread_attach", "", CONFIG_FILE);
}

bool init_config(void) {
    if (GetFileAttributesA(CONFIG_FILE) == INVALID_FILE_ATTRIBUTES) {
        printf("Config file is missing, initializing.\n");
        write_default_config();
        printf("Config file (il2spd.ini) created with defaults. Please edit it and rerun.\n");
        return false;
    }

    char buf[64];

    GetPrivateProfileStringA("Settings", "start_spd_val", "1.0", buf, sizeof(buf), CONFIG_FILE);
    g_Config.start_spd_val = (float)atof(buf);

    GetPrivateProfileStringA("Settings", "mod_spd_val", "0.1", buf, sizeof(buf), CONFIG_FILE);
    g_Config.mod_spd_val = (float)atof(buf);

    GetPrivateProfileStringA("Settings", "toggle_key", "LeftShift", g_Config.toggle_key, sizeof(g_Config.toggle_key), CONFIG_FILE);
    GetPrivateProfileStringA("Settings", "incr_key", "UpArrow", g_Config.incr_key, sizeof(g_Config.incr_key), CONFIG_FILE);
    GetPrivateProfileStringA("Settings", "decr_key", "DownArrow", g_Config.decr_key, sizeof(g_Config.decr_key), CONFIG_FILE);

    #define READ_IL2CPP(field, name) \
        GetPrivateProfileStringA("IL2CPP", name, "", g_Config.field, sizeof(g_Config.field), CONFIG_FILE); \
        if (g_Config.field[0] == 0) strcpy(g_Config.field, name)

    READ_IL2CPP(il2cpp_assembly_get_image, "il2cpp_assembly_get_image");
    READ_IL2CPP(il2cpp_class_from_name, "il2cpp_class_from_name");
    READ_IL2CPP(il2cpp_class_get_method_from_name, "il2cpp_class_get_method_from_name");
    READ_IL2CPP(il2cpp_domain_get, "il2cpp_domain_get");
    READ_IL2CPP(il2cpp_domain_assembly_open, "il2cpp_domain_assembly_open");
    READ_IL2CPP(il2cpp_runtime_invoke, "il2cpp_runtime_invoke");
    READ_IL2CPP(il2cpp_thread_attach, "il2cpp_thread_attach");

    #undef READ_IL2CPP

    if (g_Config.start_spd_val == 0.0f) g_Config.start_spd_val = 1.0f;
    if (g_Config.mod_spd_val == 0.0f) g_Config.mod_spd_val = 0.1f;

    return true;
}
