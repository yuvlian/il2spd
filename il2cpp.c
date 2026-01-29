#include "config.h"
#include "il2cpp.h"
#include <stdio.h>

Il2CppDomain* g_Il2CppDomain = NULL;
static HMODULE g_GameAssembly = NULL;

bool init_game_assembly() {
    if (!g_GameAssembly) {
        g_GameAssembly = GetModuleHandleA("GameAssembly.dll");
    }
    if (!g_GameAssembly) {
        g_GameAssembly = LoadLibraryA("GameAssembly.dll");
    }
    if (!g_GameAssembly) {
        printf("Failed to init game assembly. Error: %lu\n", GetLastError());
        return false;
    }
    return true;
}

static void* get_il2cpp_export(const char* name) {
    if (!g_GameAssembly) {
        printf("Failed to get il2cpp export. Game assembly is not initialized.\n");
        return NULL;
    }
    void* addr = GetProcAddress(g_GameAssembly, name);
    if (!addr) {
        printf("Failed to get proc address for %s. Error: %lu\n", name, GetLastError());
    }
    return addr;
}

// Il2CppObject* il2cpp_string_new(const char* str) {
//     typedef Il2CppObject* (*fn)(const char*);
//     static fn func = NULL;
//     if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_string_new);
//     return func ? func(str) : NULL;
// }

Il2CppDomain* il2cpp_domain_get() {
    typedef Il2CppDomain* (*fn)(void);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_domain_get);
    return func ? func() : NULL;
}

void il2cpp_thread_attach(Il2CppDomain* domain) {
    typedef void (*fn)(Il2CppDomain*);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_thread_attach);
    if (func) func(domain);
}

Il2CppAssembly* il2cpp_domain_assembly_open(Il2CppDomain* domain, const char* name) {
    typedef Il2CppAssembly* (*fn)(Il2CppDomain*, const char*);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_domain_assembly_open);
    return func ? func(domain, name) : NULL;
}

Il2CppImage* il2cpp_assembly_get_image(Il2CppAssembly* assembly) {
    typedef Il2CppImage* (*fn)(Il2CppAssembly*);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_assembly_get_image);
    return func ? func(assembly) : NULL;
}

Il2CppClass* il2cpp_class_from_name(Il2CppImage* image, const char* nspace, const char* name) {
    typedef Il2CppClass* (*fn)(Il2CppImage*, const char*, const char*);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_class_from_name);
    return func ? func(image, nspace, name) : NULL;
}

MethodInfo* il2cpp_class_get_method_from_name(Il2CppClass* cls, const char* name, int32_t args) {
    typedef MethodInfo* (*fn)(Il2CppClass*, const char*, int32_t);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_class_get_method_from_name);
    return func ? func(cls, name, args) : NULL;
}

Il2CppObject* il2cpp_runtime_invoke(MethodInfo* method, void* obj, void** params, Il2CppException** e) {
    typedef Il2CppObject* (*fn)(MethodInfo*, void*, void**, Il2CppException**);
    static fn func = NULL;
    if (!func) func = (fn)get_il2cpp_export(g_Config.il2cpp_runtime_invoke);
    return func ? func(method, obj, params, e) : NULL;
}

bool init_il2cpp() {
    g_Il2CppDomain = il2cpp_domain_get();
    if (!g_Il2CppDomain) return false;
    il2cpp_thread_attach(g_Il2CppDomain);
    return true;
}
