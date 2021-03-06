//
// Created by azelentsov on 26.02.2021.
//

#ifndef MAIN_DOOR_H
#define MAIN_DOOR_H

#include "Sprite.h"


class Door : public Sprite {
public:
    Door(const std::string& file, Point coords);

    void Interact();

    bool isOpened() const { return opened; }

    void Open();

    void Close();

private:

    bool opened = false;

};


#endif //MAIN_DOOR_H
