#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "MovingSprite.h"
#include "shared.h"


class Player : public MovingSprite {
public:
    Player(const std::string& file, Point coords, int move_speed = 4);

    void DrawThis(Image &screen) override;

    void onUpdate() override;

    void Interact();

private:
    int update_freq = 20u;

};

#endif //MAIN_PLAYER_H
