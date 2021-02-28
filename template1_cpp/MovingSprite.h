//
// Created by azelentsov on 26.02.2021.
//

#ifndef MAIN_MOVINGSPRITE_H
#define MAIN_MOVINGSPRITE_H

#include "SpriteController.h"


class MovingSprite : public Sprite {
public:

    MovingSprite(std::string id, const std::string& file, Point coords, RenderPriority p = RenderPriority::FOREGROUND, int move_speed=4);

    void setController(SpriteController* newController) { this->controller = newController;}

    virtual void move(MovementDir dir);

    bool didMoved() const;

    virtual void stopX();

    virtual void stopY();

protected:

    bool intersects(Sprite* other, Point new_coords) const;

    Point old_coords{};
    int move_speed = 4;
    SpriteController* controller = nullptr;
    unsigned char movesCount = 0;
};


#endif //MAIN_MOVINGSPRITE_H
