#pragma once

enum class GameMode {
    CLASSIC,
    SPEED,
    NO_WALL
};

float GetBaseSpeed(GameMode mode);
bool IsWallDeadly(GameMode mode);
const char* GetModeName(GameMode mode);