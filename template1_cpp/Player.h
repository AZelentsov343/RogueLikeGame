#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "MovingSprite.h"
#include "shared.h"


struct Player : public MovingSprite {
    Player(std::string id, const std::string& file, Point coords, int move_speed = 4);

};

#endif //MAIN_PLAYER_H
