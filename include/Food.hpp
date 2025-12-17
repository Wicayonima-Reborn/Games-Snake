#pragma once
#include "Vec2.hpp"
#include "Snake.hpp"

class Food {
public:
    Vec2 pos;
    void Respawn(const Snake& snake, int w, int h);
};