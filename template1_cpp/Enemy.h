//
// Created by azelentsov on 27.02.2021.
//

#ifndef MAIN_ENEMY_H
#define MAIN_ENEMY_H
#include <stack>
#include "MovingSprite.h"
#include "PathFinding.h"

class Enemy : public MovingSprite {
public:
    Enemy(const std::string& file, Point coords, int move_speed = 4);

    void move(MovementDir dir) override;

    void onUpdate() override;

    void followPlayer(Sprite* _player) { player = _player; }

    void chase();

    void die() { valid = false; makeUncollidable(); };

    void ThrowFireball(MovementDir dir);


private:

    int decisionCount = 0;

    std::stack<MovementDir> moves_stack;

    int fireballCooldown = 0;

    Sprite* player = nullptr;

    int update_freq = 20u;

    MovementDir lastMoveDir;

};


#endif //MAIN_ENEMY_H
