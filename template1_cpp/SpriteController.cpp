//
// Created by azelentsov on 25.02.2021.
//

#include "SpriteController.h"
#include "Door.h"
#include "Enemy.h"
#include "Fireball.h"
#include <iostream>
#include <random>
#include <algorithm>

void SpriteController::addSprite(Sprite *sprite) {
    if (sprite->prior() == RenderPriority::BACKGROUND) {
        background_queue.push_back(sprite);
    } else {
        foreground_queue.push_back(sprite);
    }

    if (sprite->getID() == "enemy") {
        enemies.push_back(sprite);
    }

    if (sprite->collidable()) {
        collidable.push_back(sprite);
    }

    if (sprite->isInteractive()) {
        interactive.push_back(sprite);
    }

}

void SpriteController::addPlayer(Sprite *pl) {
    player = pl;
}


void SpriteController::update() {

    if (initializing_steps == INITIAL_STEPS_DEFAULT) {

        auto rng = std::default_random_engine{};
        std::shuffle(std::begin(background_queue), std::end(background_queue), rng);

        for (int i = 0; i < IN_ONE_TIME; i++) {
            background_queue[i]->DrawThis(screen);
        }
        initializing_steps--;
    } else if (initializing_steps > 0) {
        for (int i = (INITIAL_STEPS_DEFAULT - initializing_steps) * IN_ONE_TIME;
             i < (INITIAL_STEPS_DEFAULT - initializing_steps) * IN_ONE_TIME + IN_ONE_TIME; i++) {
            background_queue[i]->DrawThis(screen);
        }
        initializing_steps--;
    } else if (!level_over) {

        for (auto enemy : enemies) {
            auto realEnemy = dynamic_cast<Enemy*>(enemy);
            realEnemy->followPlayer(player);
        }

        screen.makeDefault();

        for (auto sprite : background_queue) {
            sprite->DrawThis(screen);
        }
        for (auto sprite : foreground_queue) {
            sprite->DrawThis(screen);
        }

        player->DrawThis(screen);
    } else if (level_over && need_draw) {
        auto last_sprite = new Sprite("last", won ? "../resources/win.png" : "../resources/lost.png",
                                      {WINDOW_WIDTH / 2 - 213, WINDOW_HEIGHT / 2 - 120}, RenderPriority::FOREGROUND);
        last_sprite->rotateVertically();
        addSprite(last_sprite);

        need_draw = false;

        screen.makeDefault();

        for (auto sprite : background_queue) {
            sprite->DrawThis(screen);
        }
        for (auto sprite : foreground_queue) {
            sprite->DrawThis(screen);
        }

        if (won) {
            player->DrawThis(screen);
        }
    } else if (level_over) {
        updates_to_die--;
    }

}

bool SpriteController::registerCollision(Sprite *first, Sprite *second) {
    if (level_over) {
        return false;
    }
    if (first->getID() == "player" && second->getID() == "wall") {
        //std::cout << "Wall collision registered" << std::endl;
        return false;
    } else if (first->getID() == "player" && second->getID() == "exit") {
        //std::cout << "You won!" << std::endl;
        won = true;
        level_over = true;
        need_draw = true;
        return true;
    } else if (first->getID() == "player" && second->getID() == "hole") {
        //std::cout << "You lost!" << std::endl;
        won = false;
        level_over = true;
        need_draw = true;
        return true;
    } else if (first->getID() == "player" && second->getID() == "door") {
        //std::cout << "Door collision" << std::endl;
        Door *door = dynamic_cast<Door *>(second);
        return door->isOpened();
    } else if (first->getID() == "enemy" && second->getID() == "wall") {
        return false;
    } else if (first->getID() == "enemy" && second->getID() == "door") {
        Door *door = dynamic_cast<Door *>(second);
        return door->isOpened();
    } else if (first->getID() == "enemy" && second->getID() == "player") {
        won = false;
        level_over = true;
        need_draw = true;
        return true;
    } else if (first->getID() == "enemy" && second->getID() == "hole") {
        auto enemy = dynamic_cast<Enemy *>(first);
        enemy->die();
        return false;
    } else if (first->getID() == "player_fireball" && second->getID() == "wall") {
        //std::cout << "Fireball Wall collision" << std::endl;
        auto fireball = dynamic_cast<Fireball *>(first);
        fireball->StartBreaking();
        second->cutSprite({32, 0}, {64, 32});
        return false;
    } else if (first->getID() == "player_fireball" && second->getID() == "enemy") {
        auto fireball = dynamic_cast<Fireball *>(first);
        fireball->StartBreaking();

        auto enemy = dynamic_cast<Enemy *>(second);
        enemy->die();
    }
    return true;
}

SpriteController::~SpriteController() {
    for (auto sprite : background_queue) {
        delete sprite;
    }
    for (auto sprite : foreground_queue) {
        delete sprite;
    }

    delete player;
}


