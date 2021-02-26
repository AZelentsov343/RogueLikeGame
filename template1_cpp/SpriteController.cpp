//
// Created by azelentsov on 25.02.2021.
//

#include "SpriteController.h"
#include <iostream>

void SpriteController::addSprite(Sprite* sprite) {
    if (sprite->prior() == RenderPriority::BACKGROUND) {
        background_queue.push_back(sprite);
    } else {
        foreground_queue.push_back(sprite);
    }

    if (sprite->collidable()) {
        collidable.push_back(sprite);
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

bool SpriteController::registerCollision(Sprite *first, Sprite *second) {
    if (first->getID() == "player" && second->getID() == "wall") {
        //std::cout << "Wall collision registered" << std::endl;
        return false;
    }
    return true;
}


