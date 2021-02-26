#include <iostream>
#include <utility>
#include "Player.h"
#include "Door.h"


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

void Player::move(MovementDir dir) {
    MovingSprite::move(dir);

    lastMoveDir = dir;
}

void Player::Interact() {
    for (Sprite* item : controller->interactive) {
        double dist = distanceTo(item);
        if (dist < width + height) {
            if (item->getID() == "door") {
                dynamic_cast<Door*>(item)->Interact();
            }
        }
    }
}


void Player::onUpdate() {
    MovingSprite::onUpdate();

    if (lastMoveDir == MovementDir::UP) {
        cutSprite({start.x, 96}, {finish.x, 128});
    } else if (lastMoveDir == MovementDir::DOWN) {
        cutSprite({start.x, 0}, {finish.x, 32});
    } else if (lastMoveDir == MovementDir::RIGHT) {
        cutSprite({start.x, 64}, {finish.x, 96});
    } else { // lastMoveDir == MovementDir::LEFT
        cutSprite({start.x, 32}, {finish.x, 64});
    }

    if (updates % update_freq == 0 && didMoved()) {
        if (start.x == 0) {
            cutSprite({32, start.y}, {64, finish.y});
        } else if (start.x == 32) {
            cutSprite({64, start.y}, {96, finish.y});
        } else if (start.x == 64) {
            cutSprite({0, start.y}, {32, finish.y});
        }
    } else if (updates % update_freq == 0 && !didMoved()) {
        cutSprite({32, start.y}, {64, finish.y});
    }
}