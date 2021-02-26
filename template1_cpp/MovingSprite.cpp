//
// Created by azelentsov on 26.02.2021.
//

#include "MovingSprite.h"

#include <utility>
#include <iostream>

MovingSprite::MovingSprite(std::string id, const std::string &file, Point coords, RenderPriority p, int move_speed)
        : Sprite(std::move(id), file, coords, p),
          move_speed(move_speed),
          old_coords(coords) {}

bool MovingSprite::didMoved() const {
    if (coords.x == old_coords.x && coords.y == old_coords.y)
        return false;
    else
        return true;
}

void MovingSprite::stopX() {
    old_coords.x = coords.x;
}

void MovingSprite::stopY() {
    old_coords.y = coords.y;
}

void MovingSprite::move(MovementDir dir) {
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
                if (intersects(sprite, {coords.x, coords.y + move_dist})) {
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
                if (intersects(sprite, {coords.x, coords.y - move_dist})) {
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
                if (intersects(sprite, {coords.x - move_dist, coords.y})) {
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
                if (intersects(sprite, {coords.x + move_dist, coords.y})) {
                    move_dist = controller->registerCollision(this, sprite) ? move_dist : 0;
                }
            }
            old_coords.x = coords.x;
            coords.x += move_dist;
            break;
        default:
            break;
    }
}

bool MovingSprite::intersects(Sprite *other, Point new_coords) const {
    if (other->getCoords().x + other->getWidth() <= new_coords.x + 3 || new_coords.x + width <= other->getCoords().x + 3) {
        return false;
    }
    if (other->getCoords().y + other->getHeight() <= new_coords.y + 3 || new_coords.y + height <= other->getCoords().y + 3) {
        return false;
    }
    return true;
}