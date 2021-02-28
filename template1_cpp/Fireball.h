//
// Created by azelentsov on 27.02.2021.
//

#ifndef MAIN_FIREBALL_H
#define MAIN_FIREBALL_H

#include "MovingSprite.h"


class Fireball : public MovingSprite {
public:

    Fireball(const std::string& id, const std::string& file, Point coords, MovementDir direction, int move_speed = 8);

    void onUpdate() override;

    void DrawThis(Image& screen) override;

    void StartBreaking();

    void move(MovementDir dir) override;

private:

    int movesToBreak = 3;

    bool breaking = false;

    MovementDir direction;

    int update_freq = 15;

};


#endif //MAIN_FIREBALL_H
