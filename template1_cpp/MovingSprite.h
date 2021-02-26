//
// Created by azelentsov on 26.02.2021.
//

#ifndef MAIN_MOVINGSPRITE_H
#define MAIN_MOVINGSPRITE_H

#include "Sprite.h"
#include "SpriteController.h"


class MovingSprite : public Sprite {
public:

    MovingSprite(std::string id, const std::string& file, Point coords, RenderPriority p = RenderPriority::FOREGROUND, int move_speed=4);

    void setController(SpriteController* newController) { this->controller = newController;}

    void move(MovementDir dir);

    bool didMoved() const;

protected:

    bool intersects(Sprite* other, Point new_coords) const;

    Point old_coords{};
    int move_speed = 4;
    SpriteController* controller = nullptr;
};


#endif //MAIN_MOVINGSPRITE_H
