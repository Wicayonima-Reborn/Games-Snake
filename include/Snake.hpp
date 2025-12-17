#pragma once
#include <deque>
#include "Vec2.hpp"

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake {
public:
    std::deque<Vec2> body;
    Direction dir;

    Snake();
    void Reset();

    Vec2 NextHead(Direction d) const;
    void MoveTo(const Vec2& next, bool grow);

    bool WillHitSelf(const Vec2& next, bool grow) const;
    bool IsOpposite(Direction a, Direction b) const;
};