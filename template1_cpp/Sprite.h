//
// Created by azelentsov on 25.02.2021.
//

#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include <utility>
#include <stdexcept>
#include <sstream>

#include "Image.h"
#include "shared.h"


class Sprite {
public:
    Sprite(const std::string& file, std::string id, Point coords, RenderPriority p = RenderPriority::BACKGROUND);

    void cutSprite(int x_st, int y_st, int x_fin, int y_fin);

    void DrawThis(Image& screen);

    RenderPriority prior() const { return priority; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

private:

    unsigned char updates = 0;
    unsigned char update_freq = 100u;

    void validate_this();

    void updating();

    Image image;
    std::string id;
    int width;
    int height;
    Point coords;

    RenderPriority priority;

    Point start{};
    Point finish{};
};


#endif //MAIN_SPRITE_H
