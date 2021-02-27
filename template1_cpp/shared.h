//
// Created by azelentsov on 25.02.2021.
//

#ifndef MAIN_SHARED_H
#define MAIN_SHARED_H

#include <cmath>
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
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;

    bool operator==(Pixel other) const {
        if (r == other.r && g == other.g && b == other.b && a == other.a) {
            return true;
        }
        return false;
    }

    bool operator!=(Pixel other) const {
        return !this->operator==(other);
    }
};

struct Point {
    int x;
    int y;

    double distanceTo(Point other) const {
        int xdist = (x - other.x) * (x - other.x);
        int ydist = (y - other.y) * (y - other.y);

        return std::sqrt(xdist + ydist);
    }

    bool operator==(Point other) const {
        return (x == other.x) && (y == other.y);
    }

    bool operator!=(Point other) const {
        return !this->operator==(other);
    }

    bool operator<(Point other) const {
        if (x < other.x) {
            return true;
        } else if (x > other.x) {
            return false;
        } else {
            return y < other.y;
        }
    }
};

enum RenderPriority {
    BACKGROUND,
    FOREGROUND
};

#endif //MAIN_SHARED_H
