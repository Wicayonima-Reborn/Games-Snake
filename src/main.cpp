#include "raylib.h"
#include "Game.hpp"

int main() {
    InitWindow(500, 600, "Snake - Multi Mode");
    SetTargetFPS(60);

    Game game;
    game.Run();

    CloseWindow();
    return 0;
}