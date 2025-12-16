#pragma once
#include "Snake.hpp"

class Food {
public:
    Vec2 pos;
    void Respawn(const Snake& snake, int width, int height);
};