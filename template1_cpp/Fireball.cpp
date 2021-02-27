//
// Created by azelentsov on 27.02.2021.
//

#include "Fireball.h"

Fireball::Fireball(const std::string &id, const std::string &file, Point coords, MovementDir _direction, int move_speed)
        : MovingSprite(id, file, coords, RenderPriority::FOREGROUND, move_speed) {
    direction = _direction;
    if (direction == MovementDir::LEFT) {
        rotatedHorizontally = true;
    } else if (direction == MovementDir::UP) {
        rotated90CounterClockwise = true;
    } else if (direction == MovementDir::DOWN) {
        rotated90CounterClockwise = true;
        rotatedVertically = true;
    }
    is_collidable = true;

    cutSprite({0, 0}, {32, 32});
}

void Fireball::StartBreaking() {
    breaking = true;
    update_freq = 2;
    cutSprite({0, 32}, {32, 64});
}

void Fireball::DrawThis(Image &screen) {

    onUpdate();

    if (!valid) {
        return;
    }

    for (int i = coords.x; i < coords.x + width; i++) {
        for (int j = coords.y; j < coords.y + height; j++) {
            Pixel pix = rotated90CounterClockwise ? image.GetPixel(j - coords.y, i - coords.x) : image.GetPixel(
                    i - coords.x, j - coords.y);
            if (pix != Pixel{255, 255, 255, 0} && pix != Pixel{0, 0, 0, 0}) {
                screen.PutPixel(rotatedHorizontally ? coords.x + width - (i - coords.x) - 1 : i,
                                rotatedVertically ? coords.y + height - (j - coords.y) - 1 : j, pix);
            }
        }
    }
}

void Fireball::onUpdate() {
    MovingSprite::onUpdate();
    if (breaking) {
        if (updates % update_freq == 0) {
            cutSprite({(start.x + 32) % 160,32}, {(start.x + 32) % 160 + 32, 64});
            movesToBreak--;
            if (movesToBreak == 0) {
                valid = false;
            }
        }
    } else {
        move(direction);

        if (updates % update_freq == 0) {
            cutSprite({(start.x + 32) % 160, start.y}, {(start.x + 32) % 160 + 32, finish.y});
        }
    }


}
