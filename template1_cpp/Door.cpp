//
// Created by azelentsov on 26.02.2021.
//

#include "Door.h"

Door::Door(const std::string &file, Point coords) : Sprite("door", file, coords, RenderPriority::FOREGROUND, true) {
    interactive = true;
    cutSprite({0, 0}, {32, 32});
}

void Door::DrawThis(Image &screen) {
    onUpdate();

    for (int i = coords.x; i < coords.x + width; i++) {
        for (int j = coords.y; j < coords.y + height; j++) {
            Pixel pix = image.GetPixel(i - coords.x, j - coords.y);
            if (pix != Pixel{0, 0, 0, 0}) {
                screen.PutPixel(i, j, pix);
            }
        }
    }
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