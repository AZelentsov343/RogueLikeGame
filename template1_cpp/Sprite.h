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
    Sprite(std::string id, const std::string &file, Point coords, RenderPriority p = RenderPriority::BACKGROUND,
           bool collidable = false);

    explicit Sprite(std::string id, int width = tileSize, int height = tileSize, Point coords = {0, 0},
                    RenderPriority p = RenderPriority::BACKGROUND, bool collidable = false);

    Sprite(const Sprite &other) noexcept;

    Sprite(Sprite &&other) noexcept;

    void cutSprite(int x_st, int y_st, int x_fin, int y_fin);

    void DrawThis(Image &screen);

    RenderPriority prior() const { return priority; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    Point getCoords() const { return coords; }

    std::string getID() const { return id; }

    bool collidable() const { return is_collidable; }

protected:

    unsigned char updates = 0;
    unsigned char update_freq = 100u;

    void validate_this() const;

    void onUpdate();

    Image image;
    int width;
    int height;
    Point coords;
    const std::string id;
    bool is_collidable;

    RenderPriority priority;

    Point start{};
    Point finish{};
};


#endif //MAIN_SPRITE_H
