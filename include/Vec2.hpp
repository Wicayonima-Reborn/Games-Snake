#pragma once

struct Vec2 {
    int x;
    int y;
    bool operator==(const Vec2& o) const {
        return x == o.x && y == o.y;
    }
};