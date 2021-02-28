//
// Created by azelentsov on 27.02.2021.
//

#include "Fireball.h"
#include <iostream>

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
    //std::cout << "Started breaking " << std::endl;
    breaking = true;
    update_freq = 2;
    cutSprite({0, 32}, {32, 64});
    makeUncollidable();
}

void Fireball::move(MovementDir dir) {
    if (!controller) {
        throw std::runtime_error("moving sprite has no contoller attached");
    }
    if (controller->isUpdating()) {
        return;
    }

    int move_dist = move_speed * 1;
    switch (dir) {
        case MovementDir::UP:
            while (move_dist > 0 && coords.y + move_dist + tileSize >= WINDOW_HEIGHT) {
                move_dist--;
            }

            for (auto sprite : controller->collidable) {
                if (sprite->collidable() && intersects(sprite, {coords.x, coords.y + move_dist})) {
                    move_dist = controller->registerCollision(this, sprite) ? move_dist : 0;
                }
            }

            old_coords.y = coords.y;
            coords.y += move_dist;
            break;
        case MovementDir::DOWN:
            while (move_dist > 0 && coords.y - move_dist < 0) {
                move_dist--;
            }
            for (auto sprite : controller->collidable) {
                if (sprite->collidable() && intersects(sprite, {coords.x, coords.y - move_dist})) {
                    move_dist = controller->registerCollision(this, sprite) ? move_dist : 0;
                }
            }
            old_coords.y = coords.y;
            coords.y -= move_dist;

            break;
        case MovementDir::LEFT:
            while (move_dist > 0 && coords.x - move_dist < 0) {
                move_dist--;
            }
            for (auto sprite : controller->collidable) {
                if (sprite->collidable() && intersects(sprite, {coords.x - move_dist, coords.y})) {
                    move_dist = controller->registerCollision(this, sprite) ? move_dist : 0;
                }
            }
            old_coords.x = coords.x;
            coords.x -= move_dist;
            break;
        case MovementDir::RIGHT:
            while (move_dist > 0 && coords.x + move_dist + tileSize >= WINDOW_WIDTH) {
                move_dist--;
            }
            for (auto sprite : controller->collidable) {
                if (sprite->collidable() && intersects(sprite, {coords.x + move_dist, coords.y})) {
                    move_dist = controller->registerCollision(this, sprite) ? move_dist : 0;
                }
            }
            old_coords.x = coords.x;
            coords.x += move_dist;
            break;
        default:
            break;
    }

    movesCount++;
    if (movesCount % 3) {
        for (int i = coords.x - tileSize / 4; i < coords.x + width + tileSize / 4; i++) {
            for (int j = coords.y - tileSize / 4; j < coords.y + height + tileSize / 4; j++) {
                if (i < 0 || i >= WINDOW_WIDTH || j < 0 || j >= WINDOW_HEIGHT) {
                    continue;
                }
                for (Sprite *pointer : controller->which[{i, j}]) {
                    pointer->setRedraw();
                }
            }
        }
    }
}

void Fireball::DrawThis(Image &screen) {
    //std::cout << "Drawing " << std::endl;

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
    need_redraw = true;
}

void Fireball::onUpdate() {
    //std::cout << "Updating " << std::endl;
    MovingSprite::onUpdate();

    if (!valid) {
        return;
    }

    if (coords.x == 0 || coords.y == 0 || coords.x > WINDOW_WIDTH - tileSize - 3 || coords.y > WINDOW_HEIGHT - tileSize - 3 ) {
        StartBreaking();
    }
    if (breaking) {
        if (updates % update_freq == 0) {

            cutSprite({(start.x + 32) % 160,32}, {(start.x + 32) % 160 + 32, 64});
            movesToBreak--;
            if (movesToBreak == 0) {
                valid = false;
                for (int i = coords.x - tileSize; i < coords.x + width + tileSize; i++) {
                    for (int j = coords.y - tileSize; j < coords.y + height + tileSize; j++) {
                        if (i < 0 || i >= WINDOW_WIDTH || j < 0 || j >= WINDOW_HEIGHT) {
                            continue;
                        }
                        for (Sprite* pointer : controller->which[{i, j}]) {
                            pointer->setRedraw();
                        }
                    }
                }
            }
        }
    } else {
        move(direction);

        if (updates % update_freq == 0) {
            cutSprite({(start.x + 32) % 160, start.y}, {(start.x + 32) % 160 + 32, finish.y});
        }
    }
}
