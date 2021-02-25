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

    void addSprite(Sprite *sprite);

    Pixel* Data() const { return screen.Data(); }

    void update();

    Image screen;
private:
    std::vector<Sprite*> background_queue;

    std::vector<Sprite*> foreground_queue;



};


#endif //MAIN_SPRITECONTROLLER_H
