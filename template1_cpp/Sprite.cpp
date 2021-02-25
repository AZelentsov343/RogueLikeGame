//
// Created by azelentsov on 25.02.2021.
//

#include "Sprite.h"
#include <iostream>

Sprite::Sprite(const std::string &file, std::string id, Point coords, RenderPriority p)
        : image(file), id(std::move(id)), coords(coords), priority(p) {
    width = image.Width();
    height = image.Height();
    validate_this();

    start = Point{0, 0};
    finish = Point{width, height};
}

void Sprite::cutSprite(int x_st, int y_st, int x_fin, int y_fin) {
    image.cutOut(x_st, y_st, x_fin, y_fin);

    start = {x_st, y_st};
    finish = {x_fin, y_fin};

    width = finish.x - start.x;
    height = finish.y - start.y;
}

void Sprite::DrawThis(Image &screen) {
    updating();
    //std::cout << image.Width() << " " << image.Height() << std::endl;
    //std::cout << width << " " << height << std::endl;
    for (int i = coords.x; i < coords.x + width; i++) {
        for (int j = coords.y; j < coords.y + height; j++) {
            //std::cout << x << " " << y << " " << i - x << " " << j - y << std::endl;
            Pixel pix = image.GetPixel(i - coords.x, j - coords.y);
            screen.PutPixel(i, j, pix);
        }
    }
}

void Sprite::updating() {
    if (updates == 255u) {
        updates = 0;
    } else {
        updates++;
    }
    if (updates % update_freq == 0) {
        if (finish.x == 256) {
            cutSprite(256, 256, 512, 512);
        } else {
            cutSprite(0, 0, 256, 256);
        }
    }
}

void Sprite::validate_this() {
    std::ostringstream s;
    if (coords.x + width > WINDOW_WIDTH) {
        s << "Sprite id " << id << " x + width > WINDOW_WIDTH";
        throw std::runtime_error(s.str());
    }
    if (coords.x < 0) {
        s << "Sprite id " << id << " x < 0";
        throw std::runtime_error(s.str());
    }
    if (coords.y < 0) {
        s << "Sprite id " << id << " y < 0";
        throw std::runtime_error(s.str());
    }
    if (coords.y + height > WINDOW_HEIGHT) {
        s << "Sprite id " << id << " y + height > WINDOW_HEIGHT";
        throw std::runtime_error(s.str());
    }
}


