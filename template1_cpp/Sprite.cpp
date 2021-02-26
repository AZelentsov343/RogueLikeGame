//
// Created by azelentsov on 25.02.2021.
//

#include "Sprite.h"
#include <iostream>
#include <utility>

Sprite::Sprite(std::string id, const std::string &file, Point coords, RenderPriority p, bool collidable)
        : id(std::move(id)), image(file), coords(coords), priority(p), is_collidable(collidable) {
    width = image.Width();
    height = image.Height();
    validate_this();

    start = Point{0, 0};
    finish = Point{width, height};
}

Sprite::Sprite(std::string id, int width, int height, Point coords, RenderPriority p, bool collidable) : id(
        std::move(id)),
                                                                                                         image(width,
                                                                                                               height,
                                                                                                               4),
                                                                                                         width(width),
                                                                                                         height(height),
                                                                                                         coords(coords),
                                                                                                         priority(p),
                                                                                                         start({0, 0}),
                                                                                                         finish({width,
                                                                                                                 height}),
                                                                                                         is_collidable(
                                                                                                                 collidable) {}

Sprite::Sprite(const Sprite &other) noexcept: id(other.id), image(other.image), coords(other.coords),
                                              priority(other.priority),
                                              width(other.width), height(other.height), start(other.start),
                                              finish(other.finish), is_collidable(other.is_collidable) {}

Sprite::Sprite(Sprite &&other) noexcept: id(other.id), image(other.image), coords(other.coords),
                                         priority(other.priority),
                                         width(other.width), height(other.height), start(other.start),
                                         finish(other.finish), is_collidable(other.is_collidable) {}

void Sprite::cutSprite(Point _start, Point end) {
    image.cutOut(_start.x, _start.y, end.x, end.y);

    start = _start;
    finish = end;

    width = finish.x - start.x;
    height = finish.y - start.y;
}

void Sprite::DrawThis(Image &screen) {
    onUpdate();
    //std::cout << image.Width() << " " << image.Height() << std::endl;
    //std::cout << width << " " << height << std::endl;

    /*if (priority == RenderPriority::FOREGROUND) {
        std::cout << coords.x << " " << coords.y << std::endl;
        std::cout << width << " " << height << std::endl;
    }*/
    for (int i = coords.x; i < coords.x + width; i++) {
        for (int j = coords.y; j < coords.y + height; j++) {
            Pixel pix = image.GetPixel(i - coords.x, j - coords.y);
            if (pix != Pixel{0, 0, 0, 0}) {
                screen.PutPixel(i, coords.y + height - (j - coords.y) - 1, pix);
            }
        }
    }
}

void Sprite::onUpdate() {
    if (updates == 255u) {
        updates = 0;
    } else {
        updates++;
    }
}

double Sprite::distanceTo(Sprite *other) const {
    Point center{coords.x + width / 2, coords.y + height / 2};
    Point otherCenter{other->coords.x + other->width / 2, other->coords.y + other->height / 2};

    return center.distanceTo(otherCenter);
}

void Sprite::validate_this() const {
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


