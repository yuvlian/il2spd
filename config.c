#include "config.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>

Config g_Config = {0};

bool file_exists(const char* path) {
    DWORD attr = GetFileAttributesA(path);
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
}

static bool create_default_config(void) {
    FILE* f = fopen(CONFIG_FILE, "w");
    if (!f) {
        printf("Failed to create config: %s\n", strerror(errno));
        return false;
    }

    fprintf(f,
        "start_spd_val=1.0\n"
        "mod_spd_val=0.1\n"
        "toggle_key=LeftShift\n"
        "incr_key=UpArrow\n"
        "decr_key=DownArrow\n"
        "# you can leave these empty if they're not renamed\n"
        "il2cpp_assembly_get_image=\n"
        "il2cpp_class_from_name=\n"
        "il2cpp_class_get_method_from_name=\n"
        "il2cpp_domain_get=\n"
        "il2cpp_domain_assembly_open=\n"
        "il2cpp_runtime_invoke=\n"
        // "il2cpp_string_new=\n"
        "il2cpp_thread_attach=\n"
    );

    fclose(f);
    return true;
}

bool init_config(void) {
    if (!file_exists(CONFIG_FILE)) {
        printf("Config file is missing, initializing.\n");
        if (!create_default_config()) {
            printf("Default config file creation failed.\n");
        } else {
            printf(
                "Config file created in the target process directory. Please edit %s and rerun.\n", 
                CONFIG_FILE
            );
        }
        return false;
    }

    FILE* f = fopen(CONFIG_FILE, "r");
    if (!f) {
        printf("Failed to open config file. Error: %s\n", strerror(errno));
        return false;
    }

    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0;

        if (line[0] == '#' || line[0] == 0)
            continue;

        if (sscanf(line, "start_spd_val=%f", &g_Config.start_spd_val) == 1) {}
        else if (sscanf(line, "mod_spd_val=%f", &g_Config.mod_spd_val) == 1) {}

        else if (strncmp(line, "toggle_key=", 11) == 0)
            strcpy(g_Config.toggle_key, line + 11);
        else if (strncmp(line, "incr_key=", 9) == 0)
            strcpy(g_Config.incr_key, line + 9);
        else if (strncmp(line, "decr_key=", 9) == 0)
            strcpy(g_Config.decr_key, line + 9);

        else if (strncmp(line, "il2cpp_assembly_get_image=", 26) == 0)
            strcpy(g_Config.il2cpp_assembly_get_image, line + 26);
        else if (strncmp(line, "il2cpp_class_from_name=", 23) == 0)
            strcpy(g_Config.il2cpp_class_from_name, line + 23);
        else if (strncmp(line, "il2cpp_class_get_method_from_name=", 34) == 0)
            strcpy(g_Config.il2cpp_class_get_method_from_name, line + 34);
        else if (strncmp(line, "il2cpp_domain_get=", 18) == 0)
            strcpy(g_Config.il2cpp_domain_get, line + 18);
        else if (strncmp(line, "il2cpp_domain_assembly_open=", 28) == 0)
            strcpy(g_Config.il2cpp_domain_assembly_open, line + 28);
        else if (strncmp(line, "il2cpp_runtime_invoke=", 22) == 0)
            strcpy(g_Config.il2cpp_runtime_invoke, line + 22);
        // else if (strncmp(line, "il2cpp_string_new=", 18) == 0)
            // strcpy(g_Config.il2cpp_string_new, line + 18);
        else if (strncmp(line, "il2cpp_thread_attach=", 21) == 0)
            strcpy(g_Config.il2cpp_thread_attach, line + 21);
    }

    fclose(f);

    if (g_Config.start_spd_val == 0.0f) {
        printf("Config validation failed: start_spd_val missing\n");
        return false;
    }

    if (g_Config.mod_spd_val == 0.0f) {
        printf("Config validation failed: mod_spd_val missing\n");
        return false;
    }

    #define MIRROR_IF_EMPTY(field, name) \
        if (g_Config.field[0] == 0) strcpy(g_Config.field, name)

        MIRROR_IF_EMPTY(il2cpp_assembly_get_image, "il2cpp_assembly_get_image");
        MIRROR_IF_EMPTY(il2cpp_class_from_name, "il2cpp_class_from_name");
        MIRROR_IF_EMPTY(il2cpp_class_get_method_from_name, "il2cpp_class_get_method_from_name");
        MIRROR_IF_EMPTY(il2cpp_domain_get, "il2cpp_domain_get");
        MIRROR_IF_EMPTY(il2cpp_domain_assembly_open, "il2cpp_domain_assembly_open");
        MIRROR_IF_EMPTY(il2cpp_runtime_invoke, "il2cpp_runtime_invoke");
        // MIRROR_IF_EMPTY(il2cpp_string_new, "il2cpp_string_new");
        MIRROR_IF_EMPTY(il2cpp_thread_attach, "il2cpp_thread_attach");

    #undef MIRROR_IF_EMPTY

    return true;
}
