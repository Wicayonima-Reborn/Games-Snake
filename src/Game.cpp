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
    while (!inputQueue.empty()) inputQueue.pop();

    food.Respawn(snake, GRID_W, GRID_H);
    paused = false;
    gameOver = false;
    running = true;
    score = 0;
    timer = 0.0f;
    delay = GetBaseSpeed(mode);
}

void Game::HandleInput() {
    auto pushDir = [&](Direction d) {
        if (inputQueue.size() < 2) {
            inputQueue.push(d);
        }
    };

    if (IsKeyPressed(KEY_UP))    pushDir(Direction::UP);
    if (IsKeyPressed(KEY_DOWN))  pushDir(Direction::DOWN);
    if (IsKeyPressed(KEY_LEFT))  pushDir(Direction::LEFT);
    if (IsKeyPressed(KEY_RIGHT)) pushDir(Direction::RIGHT);

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

    // 🔥 AMBIL SATU INPUT DARI QUEUE
    if (!inputQueue.empty()) {
        Direction nextDir = inputQueue.front();
        inputQueue.pop();

        if (!snake.IsOpposite(snake.dir, nextDir)) {
            snake.dir = nextDir;
        }
    }

    Vec2 next = snake.NextHead(snake.dir);

    // ===== WALL LOGIC =====
    if (IsWallDeadly(mode)) {
        if (next.x < 0 || next.x >= GRID_W ||
            next.y < 0 || next.y >= GRID_H) {
            gameOver = true;
            return;
        }
    } else {
        if (next.x < 0) next.x = GRID_W - 1;
        if (next.x >= GRID_W) next.x = 0;
        if (next.y < 0) next.y = GRID_H - 1;
        if (next.y >= GRID_H) next.y = 0;
    }

    bool grow = (next == food.pos);

    if (snake.WillHitSelf(next, grow)) {
        gameOver = true;
        return;
    }

    snake.MoveTo(next, grow);

    if (grow) {
        score += 10;
        food.Respawn(snake, GRID_W, GRID_H);
    }
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    for (size_t i = 0; i < snake.body.size(); i++) {
        Color color = (i == 0) ? LIME : GREEN;
        DrawRectangle(
            snake.body[i].x * CELL,
            snake.body[i].y * CELL,
            CELL,
            CELL,
            color
        );
    }

    DrawRectangle(
        food.pos.x * CELL,
        food.pos.y * CELL,
        CELL,
        CELL,
        RED
    );

    DrawText(TextFormat("Score: %d", score), 10, GRID_H * CELL + 10, 20, RAYWHITE);
    DrawText(TextFormat("Mode: %s", GetModeName(mode)), 10, GRID_H * CELL + 35, 18, GRAY);
    DrawText("Input: QUEUED (2-step)", 10, GRID_H * CELL + 55, 16, DARKGRAY);

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