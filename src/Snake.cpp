#include "Snake.hpp"

Snake::Snake() {
    Reset();
}

void Snake::Reset() {
    body.clear();
    body.push_back({10, 10});
    dir = Direction::RIGHT;
}

bool Snake::IsOpposite(Direction a, Direction b) const {
    return (a == Direction::UP    && b == Direction::DOWN) ||
           (a == Direction::DOWN  && b == Direction::UP)   ||
           (a == Direction::LEFT  && b == Direction::RIGHT)||
           (a == Direction::RIGHT && b == Direction::LEFT);
}

Vec2 Snake::NextHead(Direction useDir) const {
    Vec2 h = body.front();
    if (useDir == Direction::UP)    h.y--;
    if (useDir == Direction::DOWN)  h.y++;
    if (useDir == Direction::LEFT)  h.x--;
    if (useDir == Direction::RIGHT) h.x++;
    return h;
}

void Snake::MoveTo(const Vec2& newHead, bool grow) {
    body.push_front(newHead);
    if (!grow)
        body.pop_back();
}

bool Snake::WillHitSelf(const Vec2& next, bool grow) const {
    size_t limit = grow ? body.size() : body.size() - 1;
    for (size_t i = 0; i < limit; i++) {
        if (body[i] == next)
            return true;
    }
    return false;
}