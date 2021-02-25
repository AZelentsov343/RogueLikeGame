//
// Created by azelentsov on 25.02.2021.
//

#include "SpriteController.h"

void SpriteController::addSprite(Sprite *sprite) {
    if (sprite->prior() == RenderPriority::BACKGROUND) {
        background_queue.push_back(sprite);
    } else {
        foreground_queue.push_back(sprite);
    }
}

void SpriteController::update() {

    screen.makeDefault();

    for (auto sprite : background_queue) {
        sprite->DrawThis(screen);
    }
    for (auto sprite : foreground_queue) {
        sprite->DrawThis(screen);
    }
}


