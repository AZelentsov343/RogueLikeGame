#include <iostream>
#include "Player.h"
#include "shared.h"


bool Player::Moved() const {
    if (coords.x == old_coords.x && coords.y == old_coords.y)
        return false;
    else
        return true;
}

void Player::ProcessInput(MovementDir dir) {
    int move_dist = move_speed * 1;
    switch (dir) {
        case MovementDir::UP:
            while (move_dist > 0 && coords.y + move_dist + tileSize >= 1024) {
                move_dist--;
            }
            old_coords.y = coords.y;
            coords.y += move_dist;
            break;
        case MovementDir::DOWN:
            while (move_dist > 0 && coords.y - move_dist < 0) {
                move_dist--;
            }
            old_coords.y = coords.y;
            coords.y -= move_dist;

            break;
        case MovementDir::LEFT:
            while (move_dist > 0 && coords.x - move_dist < 0) {
                move_dist--;
            }
            old_coords.x = coords.x;
            coords.x -= move_dist;
            break;
        case MovementDir::RIGHT:
            while (move_dist > 0 && coords.x + move_dist + tileSize >= 1024) {
                move_dist--;
            }
            old_coords.x = coords.x;
            coords.x += move_dist;
            break;
        default:
            break;
    }
}

void Player::Draw(Image &screen) {
    std::cout << "Position " << coords.x << " " << coords.y <<  std::endl;
    /*if (Moved()) {
        for (int y = old_coords.y; y <= old_coords.y + tileSize; ++y) {
            for (int x = old_coords.x; x <= old_coords.x + tileSize; ++x) {
                Pixel curPixel = Pixel{static_cast<uint8_t>(y + x), static_cast<uint8_t>(y - x),
                                       static_cast<uint8_t>(y * x), 255};
                screen.PutPixel(x, y, curPixel);
            }
        }
        old_coords = coords;
    }*/

    for (int y = coords.y; y <= coords.y + tileSize; ++y) {
        for (int x = coords.x; x <= coords.x + tileSize; ++x) {
            Pixel curPixel = avatar.GetPixel(x - coords.x, y - coords.y);
            screen.PutPixel(x, y, curPixel);
        }
    }
}