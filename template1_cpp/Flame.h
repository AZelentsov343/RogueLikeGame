//
// Created by azelentsov on 28.02.2021.
//

#ifndef MAIN_FLAME_H
#define MAIN_FLAME_H

#include "Sprite.h"


class Flame : public Sprite {
public:
    Flame(const std::string& file, Point coords);

    void onUpdate() override;

    void DrawThis(Image& screen) override;

private:

    static bool validate_coords(int i, int j);

    int update_freq = 10;
};


#endif //MAIN_FLAME_H
