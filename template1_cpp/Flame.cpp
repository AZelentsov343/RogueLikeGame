//
// Created by azelentsov on 28.02.2021.
//

#include "Flame.h"


Flame::Flame(const std::string &file, Point coords) : Sprite("flame", file, coords, RenderPriority::FOREGROUND) {
    cutSprite({0, 0}, {32, 32});
}

void Flame::DrawThis(Image &screen) {
    Sprite::DrawThis(screen);
    int radius = 128;

    Point center = Point{coords.x + width / 2, coords.y + height / 2};
    for (int i = center.x - radius; i < center.x + radius; i++) {
        for (int j = center.y - radius; j < center.y + radius; j++) {
            double dist = std::sqrt((i - center.x) * (i - center.x) + (j - center.y) * (j - center.y));
            if (dist < tileSize / 2) {
                continue;
            }
            if (!validate_coords(i, j)) {
                continue;
            }
            Pixel pix = screen.GetPixel(i, j);
            if (firstDraw) {
                for (Sprite* pointer : sc->which[{i, j}]) {
                    pointer->makeLight();
                }
            }
            if (pix == Pixel{0, 0, 0, 0}) {
                continue;
            }

            if (dist < radius / 4) {
                uint8_t red = static_cast<int>(pix.r) + 64 >= 255 ? 255 : pix.r + 64;
                uint8_t green = static_cast<int>(pix.g) + 32 >= 255 ? 255 : pix.g + 32;
                Pixel newPix = Pixel{red, green, pix.b, pix.a};
                screen.PutPixel(i, j, newPix);
            } else if (dist < radius / 2) {
                uint8_t red = static_cast<int>(pix.r) + 32 >= 255 ? 255 : pix.r + 32;
                uint8_t green = static_cast<int>(pix.g) + 16 >= 255 ? 255 : pix.g + 16;
                Pixel newPix = Pixel{red, green, pix.b, pix.a};
                screen.PutPixel(i, j, newPix);
            } else if (dist < radius) {
                uint8_t red = static_cast<int>(pix.r) + 16 >= 255 ? 255 : pix.r + 16;
                uint8_t green = static_cast<int>(pix.g) + 8 >= 255 ? 255 : pix.g + 8;
                Pixel newPix = Pixel{red, green, pix.b, pix.a};
                screen.PutPixel(i, j, newPix);
            }
        }
    }
    firstDraw = false;
    need_redraw = true;
}

void Flame::onUpdate() {
    Sprite::onUpdate();

    if (updates % update_freq == 0) {
        cutSprite({(start.x + 32) % 128, start.y}, {(start.x + 32) % 128 + 32, finish.y});
    }

}

bool Flame::validate_coords(int i, int j) {
    return !(i < 0 || i >= WINDOW_WIDTH || j < 0 || j >= WINDOW_HEIGHT);
}