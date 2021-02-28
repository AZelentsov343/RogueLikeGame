//
// Created by azelentsov on 28.02.2021.
//

#ifndef MAIN_FLAME_H
#define MAIN_FLAME_H

#include "Sprite.h"
#include "SpriteController.h"


class Flame : public Sprite {
public:
    Flame(const std::string& file, Point coords);

    void onUpdate() override;

    void DrawThis(Image& screen) override;

    void setController(SpriteController* controller) {sc = controller; }

private:

    static bool validate_coords(int i, int j);

    int update_freq = 10;

    SpriteController* sc;

    std::map<Point, Pixel> normal_values;

    bool firstDraw = true;
};


#endif //MAIN_FLAME_H
