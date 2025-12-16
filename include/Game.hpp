#pragma once
#include "Snake.hpp"
#include "Food.hpp"
#include "Mode.hpp"

class Game {
public:
    Game();
    void Run();

private:
    void HandleInput();
    void Update();
    void Render();
    void Reset();

    Snake snake;
    Food food;

    GameMode mode;
    bool paused;
    bool gameOver;
    bool running;

    int score;
    float timer;
    float delay;
};