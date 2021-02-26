#include <iostream>
#include <utility>
#include "Player.h"


Player::Player(const std::string &file, Point coords, int move_speed)
        : MovingSprite("player", file, coords, RenderPriority::FOREGROUND, move_speed) {
    cutSprite({32, 0}, {64, 32});
}

void Player::DrawThis(Image &screen) {
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


void Player::onUpdate() {
    MovingSprite::onUpdate();

    if (updates % update_freq == 0 && didMoved()) {
        if (start.x == 0) {
            cutSprite({32, start.y}, {64, finish.y});
        } else if (start.x == 32) {
            cutSprite({64, start.y}, {92, finish.y});
        } else if (start.x == 64) {
            cutSprite({0, start.y}, {32, finish.y});
        }
    } else if (updates % update_freq == 0 && !didMoved()) {
        cutSprite({32, start.y}, {64, finish.y});
    }
}