//
// Created by azelentsov on 27.02.2021.
//

#include "PathFinding.h"
#include "shared.h"

#include <set>
#include <queue>
#include <iostream>


std::stack<MovementDir> PathFinding::findPath(Point from, Point to) const {

    from.x -= from.x % tileSize;
    from.y -= from.y % tileSize;
    to.x -= to.x % tileSize;
    to.y -= to.y % tileSize;

    std::vector<GraphNode*> graph_nodes;

    std::queue<GraphNode*> search_q;

    std::set<Point> visited = {from};

    auto initial = new GraphNode{from, nullptr, MovementDir::UP};

    search_q.push(initial);
    graph_nodes.push_back(initial);

    GraphNode* needed;

    while (true) {
        //std::cout << search_q.size() << std::endl;

        if (search_q.empty()) {
            return std::stack<MovementDir>();
        }
        GraphNode *node = search_q.front();
        search_q.pop();


        if (node->coords == to) {
            needed = node;
            break;
        }

        Point next = makeFakeMove(node->coords, MovementDir::UP);
        next.x -= next.x % 32;
        next.y -= next.y % 32;

        if (visited.find(next) == visited.end()) {
            auto gr = new GraphNode{next, node, MovementDir::UP};
            visited.insert(next);
            graph_nodes.push_back(gr);
            search_q.push(gr);
        }

        next = makeFakeMove(node->coords, MovementDir::DOWN);
        next.x -= next.x % 32;
        next.y -= next.y % 32;
        if (visited.find(next) == visited.end()) {

            auto gr = new GraphNode{next, node, MovementDir::DOWN};
            visited.insert(next);
            graph_nodes.push_back(gr);
            search_q.push(gr);
        }

        next = makeFakeMove(node->coords, MovementDir::LEFT);
        next.x -= next.x % 32;
        next.y -= next.y % 32;
        if (visited.find(next) == visited.end()) {

            auto gr = new GraphNode{next, node, MovementDir::LEFT};
            visited.insert(next);
            graph_nodes.push_back(gr);
            search_q.push(gr);
        }

        next = makeFakeMove(node->coords, MovementDir::RIGHT);
        next.x -= next.x % 32;
        next.y -= next.y % 32;
        if (visited.find(next) == visited.end()) {

            auto gr = new GraphNode{next, node, MovementDir::RIGHT};
            visited.insert(next);
            graph_nodes.push_back(gr);
            search_q.push(gr);
        }
    }

    std::stack<MovementDir> res;


    while (needed->prev) {
        for (int j = 0; j < tileSize / move_speed; j++) {
            res.push(needed->moveHere);
        }
        needed = needed->prev;
    }

    for (auto p : graph_nodes) {
        delete p;
    }

    return res;
}

Point PathFinding::makeFakeMove(Point current, MovementDir dir) const {
    int move_dist = tileSize;
    switch (dir) {
        case MovementDir::UP:
            while (move_dist > 0 && current.y + move_dist + tileSize >= WINDOW_HEIGHT) {
                move_dist--;
            }

            for (auto sprite : spriteController->collidable) {

                if (sprite->collidable() && intersects(sprite, {current.x, current.y + move_dist})) {
                    move_dist = spriteController->registerCollision(sprite, nullptr, true) ? move_dist : 0;
                }
            }

            current.y += move_dist;
            break;
        case MovementDir::DOWN:
            while (move_dist > 0 && current.y - move_dist < 0) {
                move_dist--;
            }

            for (auto sprite : spriteController->collidable) {
                if (sprite->getID() == "enemy") {
                    continue;
                }
                if (sprite->collidable() && intersects(sprite, {current.x, current.y - move_dist})) {
                    move_dist = spriteController->registerCollision(sprite, nullptr, true) ? move_dist : 0;
                }
            }
            current.y -= move_dist;

            break;
        case MovementDir::LEFT:
            while (move_dist > 0 && current.x - move_dist < 0) {
                move_dist--;
            }
            for (auto sprite : spriteController->collidable) {
                if (sprite->getID() == "enemy") {
                    continue;
                }
                if (sprite->collidable() && intersects(sprite, {current.x - move_dist, current.y})) {
                    move_dist = spriteController->registerCollision(sprite, nullptr, true) ? move_dist : 0;
                }
            }
            current.x -= move_dist;
            break;
        case MovementDir::RIGHT:
            while (move_dist > 0 && current.x + move_dist + tileSize >= WINDOW_WIDTH) {
                move_dist--;
            }
            for (auto sprite : spriteController->collidable) {
                if (sprite->getID() == "enemy") {
                    continue;
                }
                if (sprite->collidable() && intersects(sprite, {current.x + move_dist, current.y})) {
                    move_dist = spriteController->registerCollision(sprite, nullptr, true) ? move_dist : 0;
                }
            }
            current.x += move_dist;
            break;
        default:
            break;
    }

    return current;
}

bool PathFinding::intersects(Sprite *other, Point new_coords) {
    if (other->getCoords().x + other->getWidth() <= new_coords.x + 16 || new_coords.x + tileSize <= other->getCoords().x + 16) {
        return false;
    }
    if (other->getCoords().y + other->getHeight() <= new_coords.y + 16 || new_coords.y + tileSize <= other->getCoords().y + 16) {
        return false;
    }
    return true;
}