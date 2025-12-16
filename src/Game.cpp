#include "Game.hpp"
#include "raylib.h"

static const int CELL = 25;
static const int GRID_W = 20;
static const int GRID_H = 20;

Game::Game() {
    mode = GameMode::CLASSIC;
    Reset();
}

void Game::Reset() {
    snake.Reset();
    food.Respawn(snake, GRID_W, GRID_H);
    paused = false;
    gameOver = false;
    running = true;
    score = 0;
    timer = 0.0f;
    delay = GetBaseSpeed(mode);
}

void Game::HandleInput() {
    if (IsKeyPressed(KEY_UP)    && snake.dir != Direction::DOWN)  snake.dir = Direction::UP;
    if (IsKeyPressed(KEY_DOWN)  && snake.dir != Direction::UP)    snake.dir = Direction::DOWN;
    if (IsKeyPressed(KEY_LEFT)  && snake.dir != Direction::RIGHT) snake.dir = Direction::LEFT;
    if (IsKeyPressed(KEY_RIGHT) && snake.dir != Direction::LEFT)  snake.dir = Direction::RIGHT;

    if (IsKeyPressed(KEY_P)) paused = !paused;
    if (IsKeyPressed(KEY_R)) Reset();

    if (IsKeyPressed(KEY_ONE))   { mode = GameMode::CLASSIC; Reset(); }
    if (IsKeyPressed(KEY_TWO))   { mode = GameMode::SPEED;   Reset(); }
    if (IsKeyPressed(KEY_THREE)) { mode = GameMode::NO_WALL; Reset(); }

    if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE))
        running = false;
}

void Game::Update() {
    if (paused || gameOver) return;

    timer += GetFrameTime();
    if (timer < delay) return;
    timer = 0.0f;

    Vec2 next = snake.NextHead();

    // ===== WALL LOGIC (FIXED) =====
    if (IsWallDeadly(mode)) {
        if (next.x < 0 || next.x >= GRID_W ||
            next.y < 0 || next.y >= GRID_H) {
            gameOver = true;
            return;
        }
    } else {
        // NO_WALL → wrap
        if (next.x < 0) next.x = GRID_W - 1;
        if (next.x >= GRID_W) next.x = 0;
        if (next.y < 0) next.y = GRID_H - 1;
        if (next.y >= GRID_H) next.y = 0;
    }

    bool grow = (next == food.pos);
    snake.MoveTo(next, grow);

    if (snake.HitSelf()) {
        gameOver = true;
        return;
    }

    if (grow) {
        score += 10;
        food.Respawn(snake, GRID_W, GRID_H);
    }
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto& s : snake.body) {
        DrawRectangle(s.x * CELL, s.y * CELL, CELL, CELL, GREEN);
    }

    DrawRectangle(food.pos.x * CELL, food.pos.y * CELL, CELL, CELL, RED);

    DrawText(TextFormat("Score: %d", score), 10, GRID_H * CELL + 10, 20, RAYWHITE);
    DrawText(TextFormat("Mode: %s", GetModeName(mode)), 10, GRID_H * CELL + 35, 18, GRAY);
    DrawText("1:Classic  2:Speed  3:NoWall  Q:Quit", 10, GRID_H * CELL + 55, 16, DARKGRAY);

    if (paused)
        DrawText("PAUSED", 180, 200, 40, YELLOW);

    if (gameOver)
        DrawText("GAME OVER - R to Restart", 70, 200, 30, RED);

    EndDrawing();
}

void Game::Run() {
    while (running && !WindowShouldClose()) {
        HandleInput();
        Update();
        Render();
    }
}