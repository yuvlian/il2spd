gcc dllmain.c config.c il2cpp.c input.c timescale.c -o il2spd.dll -static-libgcc -shared -O3 -s -flto -march=native -mtune=native -Wl,--gc-sections -fdata-sections -ffunction-sections
