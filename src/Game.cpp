#include "Game.hpp"
#include "raylib.h"

static const int CELL = 25;
static const int GRID_W = 20;
static const int GRID_H = 20;

Game::Game() {
    scene = Scene::MENU;
    mode = GameMode::CLASSIC;
    running = true;
}

void Game::ResetGame() {
    snake.Reset();
    while (!inputQueue.empty()) inputQueue.pop();
    food.Respawn(snake, GRID_W, GRID_H);

    paused = false;
    score = 0;
    timer = 0.0f;
    delay = GetBaseSpeed(mode);
    scene = Scene::GAME;
}

void Game::HandleInput() {
    if (scene == Scene::MENU) {
        if (IsKeyPressed(KEY_ONE)) { mode = GameMode::CLASSIC; ResetGame(); }
        if (IsKeyPressed(KEY_TWO)) { mode = GameMode::SPEED;   ResetGame(); }
        if (IsKeyPressed(KEY_THREE)) { mode = GameMode::NO_WALL; ResetGame(); }
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) running = false;
        return;
    }

    if (scene == Scene::GAME) {
        auto pushDir = [&](Direction d) {
            if (inputQueue.size() < 2)
                inputQueue.push(d);
        };

        if (IsKeyPressed(KEY_UP))    pushDir(Direction::UP);
        if (IsKeyPressed(KEY_DOWN))  pushDir(Direction::DOWN);
        if (IsKeyPressed(KEY_LEFT))  pushDir(Direction::LEFT);
        if (IsKeyPressed(KEY_RIGHT)) pushDir(Direction::RIGHT);

        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) running = false;
    }

    if (scene == Scene::GAME_OVER) {
        if (IsKeyPressed(KEY_R)) ResetGame();
        if (IsKeyPressed(KEY_M)) scene = Scene::MENU;
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) running = false;
    }
}

void Game::Update() {
    if (scene != Scene::GAME || paused) return;

    timer += GetFrameTime();
    if (timer < delay) return;
    timer = 0.0f;

    if (!inputQueue.empty()) {
        Direction d = inputQueue.front();
        inputQueue.pop();
        if (!snake.IsOpposite(snake.dir, d))
            snake.dir = d;
    }

    Vec2 next = snake.NextHead(snake.dir);

    if (IsWallDeadly(mode)) {
        if (next.x < 0 || next.x >= GRID_W ||
            next.y < 0 || next.y >= GRID_H) {
            scene = Scene::GAME_OVER;
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
        scene = Scene::GAME_OVER;
        return;
    }

    snake.MoveTo(next, grow);

    if (grow) {
        score += 10;
        food.Respawn(snake, GRID_W, GRID_H);
    }
}

void Game::RenderMenu() {
    DrawText("SNAKE GAME", 170, 100, 40, LIME);
    DrawText("1 - Classic", 200, 180, 20, RAYWHITE);
    DrawText("2 - Speed",   200, 210, 20, RAYWHITE);
    DrawText("3 - No Wall", 200, 240, 20, RAYWHITE);
    DrawText("Q / ESC - Quit", 180, 300, 18, GRAY);
}

void Game::RenderGame() {
    for (size_t i = 0; i < snake.body.size(); i++) {
        Color c = (i == 0) ? LIME : GREEN;
        DrawRectangle(
            snake.body[i].x * CELL,
            snake.body[i].y * CELL,
            CELL, CELL, c
        );
    }

    DrawRectangle(
        food.pos.x * CELL,
        food.pos.y * CELL,
        CELL, CELL, RED
    );

    DrawText(TextFormat("Score: %d", score), 10, GRID_H * CELL + 10, 20, RAYWHITE);

    if (paused)
        DrawText("PAUSED", 200, 200, 40, YELLOW);
}

void Game::RenderGameOver() {
    DrawText("GAME OVER", 180, 160, 40, RED);
    DrawText(TextFormat("Score: %d", score), 210, 210, 20, RAYWHITE);
    DrawText("R - Restart", 200, 250, 18, GRAY);
    DrawText("M - Menu",    200, 275, 18, GRAY);
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (scene == Scene::MENU) RenderMenu();
    else if (scene == Scene::GAME) RenderGame();
    else if (scene == Scene::GAME_OVER) RenderGameOver();

    EndDrawing();
}

void Game::Run() {
    while (running && !WindowShouldClose()) {
        HandleInput();
        Update();
        Render();
    }
}