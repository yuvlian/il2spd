#ifndef CONFIG_H
#define CONFIG_H

#include <windows.h>
#include <stdbool.h>

#define CONFIG_FILE "./il2spd.ini"

typedef struct {
    float start_spd_val;
    float mod_spd_val;

    char toggle_key[32];
    char incr_key[32];
    char decr_key[32];

    char il2cpp_assembly_get_image[64];
    char il2cpp_class_from_name[64];
    char il2cpp_class_get_method_from_name[64];
    char il2cpp_domain_get[64];
    char il2cpp_domain_assembly_open[64];
    char il2cpp_runtime_invoke[64];
    // char il2cpp_string_new[64];
    char il2cpp_thread_attach[64];
} Config;

extern Config g_Config;

bool init_config();

#endif
