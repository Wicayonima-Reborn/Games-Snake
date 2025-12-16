#pragma once
#include <deque>

struct Vec2 {
    int x;
    int y;
    bool operator==(const Vec2& o) const {
        return x == o.x && y == o.y;
    }
};

enum class Direction {
    UP, DOWN, LEFT, RIGHT
};

class Snake {
public:
    std::deque<Vec2> body;
    Direction dir;

    Snake();

    void Reset();
    Vec2 NextHead() const;

    void MoveTo(const Vec2& newHead, bool grow);

    bool HitSelf() const;
};