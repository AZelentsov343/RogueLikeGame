//
// Created by azelentsov on 27.02.2021.
//

#ifndef MAIN_PATHFINDING_H
#define MAIN_PATHFINDING_H

#include "SpriteController.h"
#include <stack>
#include <map>
#include <queue>

struct GraphNode {
    Point coords;
    GraphNode *prev;
    MovementDir moveHere;

    bool operator<(GraphNode other) const {
        return coords < other.coords;
    }
};

class PathFinding {
public:
    PathFinding(SpriteController *_spriteController, int _move_speed)
            : spriteController(_spriteController), move_speed(_move_speed){}

    std::stack<MovementDir> findPath(Point from, Point to) const ;

    Point makeFakeMove(Point current, MovementDir dir) const;

    static bool intersects(Sprite *other, Point new_coords) ;

private:
    SpriteController *spriteController;
    int move_speed;


};


#endif //MAIN_PATHFINDING_H
