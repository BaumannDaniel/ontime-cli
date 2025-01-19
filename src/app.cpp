#include <cstdlib>
#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

extern "C" {
int main() {
    ma_result result;
    ma_engine engine;

    result = ma_engine_init(nullptr, &engine);
    if (result != MA_SUCCESS) {
        return -1;
    }

    ma_engine_play_sound(&engine, "/home/daniel/Downloads/M1F1-Alaw-AFsp.wav", nullptr);

    printf("Press Enter to quit...");
    getchar();

    ma_engine_uninit(&engine);
    return EXIT_SUCCESS;
}
}
