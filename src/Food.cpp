#include "Food.hpp"
#include "raylib.h"
#include <algorithm>

void Food::Respawn(const Snake& snake, int width, int height) {
    do {
        pos = {
            GetRandomValue(0, width - 1),
            GetRandomValue(0, height - 1)
        };
    } while (std::find(snake.body.begin(), snake.body.end(), pos)
             != snake.body.end());
}