#include <iostream>
#include <utility>
#include "Player.h"
#include "shared.h"


Player::Player(std::string id, const std::string &file, Point coords, int move_speed)
        : MovingSprite(std::move(id), file, coords, RenderPriority::FOREGROUND, move_speed) {}