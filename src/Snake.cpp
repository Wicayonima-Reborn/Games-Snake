#include "Snake.hpp"

Snake::Snake() {
    Reset();
}

void Snake::Reset() {
    body.clear();
    body.push_back({10, 10});
    dir = Direction::RIGHT;
}

Vec2 Snake::NextHead() const {
    Vec2 h = body.front();
    if (dir == Direction::UP)    h.y--;
    if (dir == Direction::DOWN)  h.y++;
    if (dir == Direction::LEFT)  h.x--;
    if (dir == Direction::RIGHT) h.x++;
    return h;
}

void Snake::MoveTo(const Vec2& newHead, bool grow) {
    body.push_front(newHead);
    if (!grow)
        body.pop_back();
}

bool Snake::HitSelf() const {
    for (size_t i = 1; i < body.size(); i++) {
        if (body[i] == body.front())
            return true;
    }
    return false;
}