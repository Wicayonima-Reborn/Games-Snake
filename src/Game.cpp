#include "Game.hpp"

static const int CELL = 25;
static const int GRID = 20;

static float GetSpeedByScore(GameMode mode, int score) {
    float base = GetBaseSpeed(mode);
    float speed = base - (score / 50) * 0.01f;
    if (speed < 0.06f) speed = 0.06f;
    return speed;
}

Game::Game() {
    InitAudioDevice();

    sfxEat      = LoadSound("assets/sfx/eat.wav");
    sfxGameOver = LoadSound("assets/sfx/GameOver.wav");
    sfxSelect   = LoadSound("assets/sfx/select.wav");

    scene = Scene::MENU;
    mode = GameMode::CLASSIC;
    running = true;
}

void Game::ResetGame() {
    snake.Reset();
    while (!inputQueue.empty()) inputQueue.pop();
    food.Respawn(snake, GRID, GRID);

    score = 0;
    paused = false;
    timer = 0;
    delay = GetBaseSpeed(mode);
    scene = Scene::GAME;
}

void Game::HandleInput() {
    if (scene == Scene::MENU) {
        if (IsKeyPressed(KEY_ONE))  { PlaySound(sfxSelect); mode = GameMode::CLASSIC; ResetGame(); }
        if (IsKeyPressed(KEY_TWO))  { PlaySound(sfxSelect); mode = GameMode::SPEED;   ResetGame(); }
        if (IsKeyPressed(KEY_THREE)){ PlaySound(sfxSelect); mode = GameMode::NO_WALL; ResetGame(); }
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) running = false;
        return;
    }

    if (scene == Scene::GAME) {
        auto push = [&](Direction d){
            if (inputQueue.size() < 2) inputQueue.push(d);
        };

        if (IsKeyPressed(KEY_UP)) push(Direction::UP);
        if (IsKeyPressed(KEY_DOWN)) push(Direction::DOWN);
        if (IsKeyPressed(KEY_LEFT)) push(Direction::LEFT);
        if (IsKeyPressed(KEY_RIGHT)) push(Direction::RIGHT);

        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) running = false;
    }

    if (scene == Scene::GAME_OVER) {
        if (IsKeyPressed(KEY_R)) ResetGame();
        if (IsKeyPressed(KEY_M)) scene = Scene::MENU;
    }
}

void Game::Update() {
    if (scene != Scene::GAME || paused) return;

    timer += GetFrameTime();
    if (timer < delay) return;
    timer = 0;

    if (!inputQueue.empty()) {
        Direction d = inputQueue.front();
        inputQueue.pop();
        if (!snake.IsOpposite(snake.dir, d))
            snake.dir = d;
    }

    Vec2 next = snake.NextHead(snake.dir);

    if (IsWallDeadly(mode)) {
        if (next.x < 0 || next.x >= GRID || next.y < 0 || next.y >= GRID) {
            PlaySound(sfxGameOver);
            scene = Scene::GAME_OVER;
            return;
        }
    } else {
        if (next.x < 0) next.x = GRID - 1;
        if (next.x >= GRID) next.x = 0;
        if (next.y < 0) next.y = GRID - 1;
        if (next.y >= GRID) next.y = 0;
    }

    bool grow = (next == food.pos);

    if (snake.WillHitSelf(next, grow)) {
        PlaySound(sfxGameOver);
        scene = Scene::GAME_OVER;
        return;
    }

    snake.MoveTo(next, grow);

    if (grow) {
        PlaySound(sfxEat);
        score += 10;
        delay = GetSpeedByScore(mode, score);
        food.Respawn(snake, GRID, GRID);
    }
}

void Game::RenderMenu() {
    DrawText("SNAKE GAME", 170, 120, 40, LIME);
    DrawText("1 - Classic", 200, 200, 20, RAYWHITE);
    DrawText("2 - Speed", 200, 230, 20, RAYWHITE);
    DrawText("3 - No Wall", 200, 260, 20, RAYWHITE);
}

void Game::RenderGame() {
    for (size_t i = 0; i < snake.body.size(); i++) {
        DrawRectangle(
            snake.body[i].x * CELL,
            snake.body[i].y * CELL,
            CELL, CELL,
            i == 0 ? LIME : GREEN
        );
    }

    DrawRectangle(food.pos.x * CELL, food.pos.y * CELL, CELL, CELL, RED);
    DrawText(TextFormat("Score: %d", score), 10, GRID * CELL + 10, 20, RAYWHITE);
    DrawText(GetModeName(mode), 10, GRID * CELL + 35, 18, GRAY);

    if (paused)
        DrawText("PAUSED", 200, 200, 40, YELLOW);
}

void Game::RenderGameOver() {
    DrawText("GAME OVER", 180, 180, 40, RED);
    DrawText("R - Restart", 200, 230, 18, GRAY);
    DrawText("M - Menu", 200, 255, 18, GRAY);
}

void Game::Render() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (scene == Scene::MENU) RenderMenu();
    else if (scene == Scene::GAME) RenderGame();
    else RenderGameOver();

    EndDrawing();
}

void Game::Run() {
    while (running && !WindowShouldClose()) {
        HandleInput();
        Update();
        Render();
    }

    UnloadSound(sfxEat);
    UnloadSound(sfxGameOver);
    UnloadSound(sfxSelect);
    CloseAudioDevice();
}