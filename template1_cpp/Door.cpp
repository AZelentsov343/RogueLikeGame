//
// Created by azelentsov on 26.02.2021.
//

#include "Door.h"

Door::Door(const std::string &file, Point coords) : Sprite("door", file, coords, RenderPriority::FOREGROUND, true) {
    interactive = true;
    cutSprite({0, 0}, {32, 32});
}


void Door::Interact() {
    opened ? Close() : Open();
}

void Door::Open() {
    cutSprite({32, 0}, {64, 32});
    opened = true;
}

void Door::Close() {
    cutSprite({0, 0}, {32, 32});
    opened = false;
}