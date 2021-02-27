//
// Created by azelentsov on 27.02.2021.
//

#include <iostream>
#include "Enemy.h"
#include "Fireball.h"

Enemy::Enemy(const std::string &file, Point coords, int move_speed)
        : MovingSprite("enemy", file, coords, RenderPriority::FOREGROUND, move_speed) {
    interactive = true;
    is_collidable = true;
    cutSprite({32, 0}, {64, 32});
    lastMoveDir = MovementDir::DOWN;
}

void Enemy::move(MovementDir dir) {
    MovingSprite::move(dir);

    lastMoveDir = dir;
}

void Enemy::chase() {

    if (!player || !valid) {
        return;
    }
    Point destination = {player->getCoords().x + player->getWidth() / 2, player->getCoords().y + player->getHeight() / 2};

    Point center = {coords.x + width / 2, coords.y + height / 2};

    int horDiff = destination.x - center.x;

    MovementDir hor = horDiff > 0 ? MovementDir::RIGHT : MovementDir::LEFT;

    int vertDiff = destination.y - center.y;

    MovementDir ver = vertDiff > 0 ? MovementDir::UP : MovementDir::DOWN;

    old_coords = coords;

    bool thrown_fireball = false;

    if (horDiff != 0 && vertDiff != 0) {
        move(hor);
        move(ver);
    } else if (horDiff != 0) {
        //move(hor);
        ThrowFireball(hor);

        thrown_fireball = true;
    } else if (vertDiff != 0) {
        //move(ver);
        ThrowFireball(ver);

        thrown_fireball = true;
    }

    if (!didMoved() && !thrown_fireball) {
        ThrowFireball(lastMoveDir);
    }


    if (intersects(player, coords)) {
        controller->registerCollision(this, player);
    }

}

void Enemy::ThrowFireball(MovementDir dir) {
    if (fireballCooldown > 0) {
        return;
    }
    auto fireball = new Fireball("enemy_fireball", "../resources/fireball.png", coords, dir);

    fireball->setController(controller);
    controller->addSprite(fireball);
    fireballCooldown = 20;

}

void Enemy::onUpdate() {

    MovingSprite::onUpdate();

    if (fireballCooldown > 0) {
        fireballCooldown--;
    }

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


