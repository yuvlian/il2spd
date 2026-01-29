#include "timescale.h"
#include <stdio.h>

static MethodInfo* g_set_timeScale_ptr = NULL;

bool init_time_scale() {
    if (!g_Il2CppDomain) {
        printf("Failed to init time scale. il2cpp is not initialized.\n");
        return false;
    }

    Il2CppAssembly* assembly = il2cpp_domain_assembly_open(g_Il2CppDomain, "UnityEngine.CoreModule");
    if (!assembly) {
        printf("Failed to init time scale. UnityEngine.CoreModule is missing.\n");
        return false;
    }

    Il2CppImage* image = il2cpp_assembly_get_image(assembly);
    if (!image) {
        printf("Failed to init time scale. Image is null.\n");
        return false;
    }

    Il2CppClass* time_class = il2cpp_class_from_name(image, "UnityEngine", "Time");
    if (!time_class) {
        printf("Failed to init time scale. Time class is missing.\n");
        return false;
    }

    g_set_timeScale_ptr = il2cpp_class_get_method_from_name(time_class, "set_timeScale", 1);
    if (!g_set_timeScale_ptr) {
        printf("Failed to init time scale. set_timeScale method is missing.\n");
        return false;
    }

    return true;
}

void set_time_scale(float value) {
    if (!g_set_timeScale_ptr) {
        printf("Failed to set time scale. g_set_timeScale_ptr is not initialized.\n");
        return;
    }

    void* args[1];
    args[0] = &value;
    Il2CppException* exc = NULL;
    il2cpp_runtime_invoke(g_set_timeScale_ptr, NULL, args, &exc);

    if (exc) {
        printf("Failed to set time scale. il2cpp_runtime_invoke returned an exception.\n");
    }
}
