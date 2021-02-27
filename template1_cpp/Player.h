#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "MovingSprite.h"
#include "shared.h"


class Player : public MovingSprite {
public:
    Player(const std::string& file, Point coords, int move_speed = 4);

    void onUpdate() override;

    void move(MovementDir dir) override;

    void Interact();

    void ThrowFireball();

private:
    int update_freq = 20u;

    MovementDir lastMoveDir;

};

#endif //MAIN_PLAYER_H
