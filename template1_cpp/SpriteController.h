//
// Created by azelentsov on 25.02.2021.
//

#ifndef MAIN_SPRITECONTROLLER_H
#define MAIN_SPRITECONTROLLER_H

#include <vector>

#include "Sprite.h"


class SpriteController {
public:
    SpriteController() : screen(WINDOW_WIDTH, WINDOW_HEIGHT, 4) {}

    void addSprite(Sprite* sprite);

    static bool registerCollision(Sprite* first, Sprite* second);

    Pixel* Data() const { return screen.Data(); }

    void update();

    std::vector<Sprite*> collidable;

private:

    Image screen;

    std::vector<Sprite*> background_queue;

    std::vector<Sprite*> foreground_queue;
};


#endif //MAIN_SPRITECONTROLLER_H
