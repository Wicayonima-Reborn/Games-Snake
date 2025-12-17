#include "Food.hpp"
#include "raylib.h"

void Food::Respawn(const Snake& snake, int w, int h) {
    bool valid;
    do {
        valid = true;
        pos.x = GetRandomValue(0, w - 1);
        pos.y = GetRandomValue(0, h - 1);
        for (auto& s : snake.body) {
            if (s == pos) {
                valid = false;
                break;
            }
        }
    } while (!valid);
}