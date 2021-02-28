//
// Created by azelentsov on 25.02.2021.
//

#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include <utility>
#include <stdexcept>
#include <sstream>
#include <set>

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

    void cutSprite(Point start, Point end);

    virtual void DrawThis(Image &screen);

    RenderPriority prior() const { return priority; }

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    Point getCoords() const { return coords; }

    std::string getID() const { return id; }

    bool collidable() const { return is_collidable; }

    bool isInteractive() const { return interactive; }

    void rotateVertically() { rotatedVertically = true; }

    void makeUncollidable() { is_collidable = false; }

    bool Moving() const { return moving; }

    bool needRedraw() const { return need_redraw; }

    void setRedraw() {need_redraw = true; }

    void makeLight() { closeToFire = true; }

    bool lighted() const { return closeToFire; }

protected:

    unsigned char updates = 0;
    unsigned char update_freq = 100u;

    void validate_this() const;

    virtual void onUpdate();

    double distanceTo(Sprite *other) const;

    bool rotatedVertically = false;
    bool rotatedHorizontally = false;
    bool rotated90CounterClockwise = false;

    Image image;
    int width;
    int height;
    Point coords;
    const std::string id;
    bool is_collidable;
    bool interactive = false;

    bool need_redraw = true;
    bool moving = false;

    RenderPriority priority;

    Point start{};
    Point finish{};

    bool valid = true;

    bool closeToFire = false;

};


#endif //MAIN_SPRITE_H
