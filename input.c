#include "input.h"
#include <stdio.h>
#include <stdint.h>

// TOOD: switch to windows native key down

static MethodInfo* g_GetKeyDown_ptr = NULL;

static uint32_t hash_str(const char* s) {
    uint32_t h = 2166136261u;
    while (*s) {
        char c = *s++;
        if (c >= 'A' && c <= 'Z')
            c += 32;
        h ^= (uint8_t)c;
        h *= 16777619u;
    }
    return h;
}

// dont wanna bother trying to get the correct overload
int get_key_code(const char* key) {
    if (!key) return 0;
    switch (hash_str(key)) {
        case 0x853c682c: return 8; // Backspace
        case 0x67c2444a: return 127; // Delete
        case 0x98f72e4c: return 9; // Tab
        case 0x5c6e1222: return 12; // Clear
        case 0x85ee37bf: return 13; // Return
        case 0x7084d38d: return 19; // Pause
        case 0x9e212406: return 27; // Escape
        case 0x3553e285: return 32; // Space
        case 0x783099f3: return 256; // Keypad0
        case 0x77309860: return 257; // Keypad1
        case 0x7a309d19: return 258; // Keypad2
        case 0x79309b86: return 259; // Keypad3
        case 0x7c30a03f: return 260; // Keypad4
        case 0x7b309eac: return 261; // Keypad5
        case 0x7e30a365: return 262; // Keypad6
        case 0x7d30a1d2: return 263; // Keypad7
        case 0x8030a68b: return 264; // Keypad8
        case 0x7f30a4f8: return 265; // Keypad9
        case 0x9d3d19e8: return 266; // KeypadPeriod
        case 0x17d3086c: return 267; // KeypadDivide
        case 0x5aefa679: return 268; // KeypadMultiply
        case 0x54357dab: return 269; // KeypadMinus
        case 0xccf34901: return 270; // KeypadPlus
        case 0x8db86cd1: return 271; // KeypadEnter
        case 0x752cd088: return 272; // KeypadEquals
        case 0xec3bbd79: return 273; // UpArrow
        case 0x7d1f8e16: return 274; // DownArrow
        case 0xcef29326: return 275; // RightArrow
        case 0x0bfe3409: return 276; // LeftArrow
        case 0xc6a39628: return 277; // Insert
        case 0xd2c8c28e: return 278; // Home
        case 0x6a8e75aa: return 279; // End
        case 0x4eb7126b: return 280; // PageUp
        case 0xdee8167e: return 281; // PageDown
        case 0x14226d78: return 282; // F1
        case 0x17227231: return 283; // F2
        case 0x1622709e: return 284; // F3
        case 0x19227557: return 285; // F4
        case 0x182273c4: return 286; // F5
        case 0x1b22787d: return 287; // F6
        case 0x1a2276ea: return 288; // F7
        case 0x0d226273: return 289; // F8
        case 0x0c2260e0: return 290; // F9
        case 0xfa320858: return 291; // F10
        case 0xfb3209eb: return 292; // F11
        case 0xfc320b7e: return 293; // F12
        case 0xfd320d11: return 294; // F13
        case 0xfe320ea4: return 295; // F14
        case 0xff321037: return 296; // F15
        case 0xdd7d8b01: return 48; // Alpha0
        case 0xdc7d896e: return 49; // Alpha1
        case 0xdb7d87db: return 50; // Alpha2
        case 0xda7d8648: return 51; // Alpha3
        case 0xe17d914d: return 52; // Alpha4
        case 0xe07d8fba: return 53; // Alpha5
        case 0xdf7d8e27: return 54; // Alpha6
        case 0xde7d8c94: return 55; // Alpha7
        case 0xd57d7e69: return 56; // Alpha8
        case 0xd47d7cd6: return 57; // Alpha9
        case 0x2f0d2304: return 33; // Exclaim
        case 0xd551945c: return 34; // DoubleQuote
        case 0xcec577d1: return 35; // Hash
        case 0xf364bd3f: return 36; // Dollar
        case 0x75f9fa5a: return 37; // Percent
        case 0xebb16704: return 38; // Ampersand
        case 0xb2887bd7: return 39; // Quote
        case 0x97a04084: return 40; // LeftParen
        case 0xffbd8ffb: return 41; // RightParen
        case 0xef8a6081: return 42; // Asterisk
        case 0xc4adc675: return 43; // Plus
        case 0xbffa8578: return 44; // Comma
        case 0xf7fa3daf: return 45; // Minus
        case 0x99c94704: return 46; // Period
        case 0xcb73e8ea: return 47; // Slash
        case 0x497e753c: return 58; // Colon
        case 0x0415d01e: return 59; // Semicolon
        case 0x216b57b8: return 60; // Less
        case 0x513c8d94: return 61; // Equals
        case 0x50c80b99: return 62; // Greater
        case 0x06d5a845: return 63; // Question
        case 0x57251588: return 64; // At
        case 0x8569a10c: return 91; // LeftBracket
        case 0x6f17fb77: return 92; // Backslash
        case 0x1184ac13: return 93; // RightBracket
        case 0x7aef16a8: return 94; // Caret
        case 0x34fdbabd: return 95; // Underscore
        case 0x78c98ede: return 96; // BackQuote
        case 0xe40c292c: return 97; // A
        case 0xe70c2de5: return 98; // B
        case 0xe60c2c52: return 99; // C
        case 0xe10c2473: return 100; // D
        case 0xe00c22e0: return 101; // E
        case 0xe30c2799: return 102; // F
        case 0xe20c2606: return 103; // G
        case 0xed0c3757: return 104; // H
        case 0xec0c35c4: return 105; // I
        case 0xef0c3a7d: return 106; // J
        case 0xee0c38ea: return 107; // K
        case 0xe90c310b: return 108; // L
        case 0xe80c2f78: return 109; // M
        case 0xeb0c3431: return 110; // N
        case 0xea0c329e: return 111; // O
        case 0xf50c43ef: return 112; // P
        case 0xf40c425c: return 113; // Q
        case 0xf70c4715: return 114; // R
        case 0xf60c4582: return 115; // S
        case 0xf10c3da3: return 116; // T
        case 0xf00c3c10: return 117; // U
        case 0xf30c40c9: return 118; // V
        case 0xf20c3f36: return 119; // W
        case 0xfd0c5087: return 120; // X
        case 0xfc0c4ef4: return 121; // Y
        case 0xff0c53ad: return 122; // Z
        case 0xaaa33c6f: return 123; // LeftCurlyBracket
        case 0xf81d19f9: return 124; // Pipe
        case 0xfd66e486: return 125; // RightCurlyBracket
        case 0xff1023a9: return 126; // Tilde
        case 0xfe4dfe3c: return 300; // Numlock
        case 0x2b67f02f: return 301; // CapsLock
        case 0x45cb7583: return 302; // ScrollLock
        case 0xb7ecb4e7: return 303; // RightShift
        case 0xe115ce54: return 304; // LeftShift
        case 0x9eb6ef3e: return 305; // RightControl
        case 0x2e50c0b5: return 306; // LeftControl
        case 0x4b8c1ffc: return 307; // RightAlt
        case 0x8816c52b: return 308; // LeftAlt
        case 0xc6c2f919: return 310; // LeftCommand
        case 0x2db726b0: return 310; // LeftApple
        case 0x76fec12d: return 311; // LeftWindows
        case 0xe1ebbf52: return 309; // RightCommand
        case 0x74a74c5f: return 309; // RightApple
        case 0x21af328a: return 312; // RightWindows
        case 0x12d2d369: return 313; // AltGr
        case 0x3871a3fa: return 315; // Help
        case 0x5f4e7027: return 316; // Pr
        case 0x1a4c91ae: return 317; // SysReq
        case 0xc9648178: return 318; // Break
        case 0x99e4dd3a: return 319; // Menu
        case 0x4640481c: return 323; // Mouse0
        case 0x474049af: return 324; // Mouse1
        case 0x48404b42: return 325; // Mouse2
        case 0x49404cd5: return 326; // Mouse3
        case 0x424041d0: return 327; // Mouse4
        case 0x43404363: return 328; // Mouse5
        case 0x444044f6: return 329; // Mouse6
        default: return 0;
    }
}


bool init_input() {
    if (!g_Il2CppDomain) {
        printf("Failed to init input. il2cpp is not initialized.\n");
        return false;
    }

    Il2CppAssembly* assembly = il2cpp_domain_assembly_open(g_Il2CppDomain, "UnityEngine.InputLegacyModule");
    if (!assembly) {
        printf("Failed to init input. InputLegacyModule is missing.\n");
        return false;
    }

    Il2CppImage* image = il2cpp_assembly_get_image(assembly);
    if (!image) {
        printf("Failed to init input. Image is null.\n");
        return false;
    }

    Il2CppClass* input_class = il2cpp_class_from_name(image, "UnityEngine", "Input");
    if (!input_class) {
        printf("Failed to init input. Input class is missing.\n");
        return false;
    }

    g_GetKeyDown_ptr = il2cpp_class_get_method_from_name(input_class, "GetKeyDown", 1);
    if (!g_GetKeyDown_ptr) {
        printf("Failed to init input. GetKeyDown is missing.\n");
        return false;
    }

    return true;
}

bool get_key_down(const char* key) {
    if (!g_GetKeyDown_ptr) {
        printf("Failed to get key down. g_GetKeyDown_ptr is not initialized.\n");
        return false;
    }
    if (!key) {
        printf("Failed to get key down. key is empty.\n");
        return false;
    }

    // Il2CppObject* m_key = il2cpp_string_new(key);
    // if (!m_key) {
    //     printf("Failed to get key down. Failed to create il2cpp string.");
    //     return false;
    // }
    int m_key = get_key_code(key);
    if (m_key == 0) {
        printf("Failed to get key down. Invalid key for key code.");
        return false;
    }

    void* args[1];
    args[0] = &m_key;

    Il2CppException* exc = NULL;
    Il2CppObject* ret = il2cpp_runtime_invoke(g_GetKeyDown_ptr, NULL, args, &exc);
    // printf("Debug: Key %s (Code %d) result object ptr: %p\n", key, m_key, ret);
    if (exc) {
        printf("Failed to get key down. il2cpp_runtime_invoke returned an exception.\n");
    }
    if (ret) {
        return *(bool*)((char*)ret + (sizeof(void*) * 2));
    }
    return false;
}
