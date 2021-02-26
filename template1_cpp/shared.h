//
// Created by azelentsov on 25.02.2021.
//

#ifndef MAIN_SHARED_H
#define MAIN_SHARED_H
#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 1024, WINDOW_HEIGHT = 1024;
constexpr int tileSize = 32;

enum class MovementDir {
    UP,
    DOWN,
    LEFT,
    RIGHT
};


struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Point {
    int x;
    int y;
};

enum RenderPriority {
    BACKGROUND,
    FOREGROUND
};

#endif //MAIN_SHARED_H
