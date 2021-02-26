//
// Created by azelentsov on 25.02.2021.
//

#ifndef MAIN_SPRITECONTROLLER_H
#define MAIN_SPRITECONTROLLER_H

#include <vector>

#include "Sprite.h"

#define INITIAL_STEPS_DEFAULT 255
#define IN_ONE_TIME ((WINDOW_HEIGHT * WINDOW_WIDTH) / (tileSize * tileSize) / INITIAL_STEPS_DEFAULT)


class SpriteController {
public:
    explicit SpriteController() : screen(WINDOW_WIDTH, WINDOW_HEIGHT, 4) {}

    void addSprite(Sprite* sprite);

    void addPlayer(Sprite* player);

    bool registerCollision(Sprite* first, Sprite* second);

    Pixel* Data() const { return screen.Data(); }

    Image curScreen() const { return screen; }

    void update();

    std::vector<Sprite*> collidable;

    std::vector<Sprite*> interactive;

    Sprite* getPlayer() const { return player; }

    bool died() const { return updates_to_die <= 0; }

    bool didPass() const { return won; }

    bool isUpdating() const { return updating || initializing_steps > 0 || level_over; }

    ~SpriteController();

private:

    Image screen;

    Sprite* player = nullptr;

    std::vector<Sprite*> background_queue;

    std::vector<Sprite*> foreground_queue;

    bool level_over = false;

    bool need_draw = true;

    bool won = true;

    bool updating = false;

    int initializing_steps = INITIAL_STEPS_DEFAULT;

    int updates_to_die = 200;

};


#endif //MAIN_SPRITECONTROLLER_H
