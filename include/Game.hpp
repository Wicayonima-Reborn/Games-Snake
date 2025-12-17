#pragma once
#include <queue>
#include "Snake.hpp"
#include "Food.hpp"
#include "Mode.hpp"
#include "Scene.hpp"
#include "raylib.h"

class Game {
public:
    Game();
    void Run();

private:
    void HandleInput();
    void Update();
    void Render();

    void ResetGame();
    void RenderMenu();
    void RenderGame();
    void RenderGameOver();

    Snake snake;
    Food food;
    std::queue<Direction> inputQueue;

    Scene scene;
    GameMode mode;

    bool paused;
    bool running;

    int score;
    float timer;
    float delay;

    Sound sfxEat;
    Sound sfxGameOver;
    Sound sfxSelect;
};