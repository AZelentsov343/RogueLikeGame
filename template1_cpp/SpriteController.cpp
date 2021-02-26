//
// Created by azelentsov on 25.02.2021.
//

#include "SpriteController.h"
#include "Door.h"
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

    if (sprite->isInteractive()) {
        interactive.push_back(sprite);
    }
}

void SpriteController::addPlayer(Sprite* pl) {
    player = pl;
}


void SpriteController::update() {

    screen.makeDefault();

    for (auto sprite : background_queue) {
        sprite->DrawThis(screen);
    }
    for (auto sprite : foreground_queue) {
        sprite->DrawThis(screen);
    }

    player->DrawThis(screen);
}

bool SpriteController::registerCollision(Sprite *first, Sprite *second) {
    if (first->getID() == "player" && second->getID() == "wall") {
        //std::cout << "Wall collision registered" << std::endl;
        return false;
    } else if (first->getID() == "player" && second->getID() == "exit") {
        std::cout << "You won!" << std::endl;
        return true;
    } else if (first->getID() == "player" && second->getID() == "hole") {
        std::cout << "You lost!" << std::endl;
        return true;
    } else if (first->getID() == "player" && second->getID() == "door") {
        std::cout << "Door collision" << std::endl;
        Door* door = dynamic_cast<Door*>(second);
        return door->isOpened();
    }
    return true;
}


