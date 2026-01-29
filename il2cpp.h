#ifndef IL2CPP_H
#define IL2CPP_H

#include <stdint.h>
#include <windows.h>
#include <stdbool.h>

typedef struct Il2CppDomain Il2CppDomain;
typedef struct Il2CppAssembly Il2CppAssembly;
typedef struct Il2CppImage Il2CppImage;
typedef struct Il2CppClass Il2CppClass;
typedef struct MethodInfo MethodInfo;
typedef struct Il2CppException Il2CppException;
typedef struct Il2CppObject Il2CppObject;

extern Il2CppDomain* g_Il2CppDomain;

bool init_game_assembly();
// Il2CppObject* il2cpp_string_new(const char* str);
Il2CppDomain* il2cpp_domain_get();
void il2cpp_thread_attach(Il2CppDomain* domain);
Il2CppAssembly* il2cpp_domain_assembly_open(Il2CppDomain* domain, const char* name);
Il2CppImage* il2cpp_assembly_get_image(Il2CppAssembly* assembly);
Il2CppClass* il2cpp_class_from_name(Il2CppImage* image, const char* nspace, const char* name);
MethodInfo* il2cpp_class_get_method_from_name(Il2CppClass* cls, const char* name, int32_t args);
Il2CppObject* il2cpp_runtime_invoke(MethodInfo* method, void* obj, void** params, Il2CppException** e);
bool init_il2cpp();

#endif
