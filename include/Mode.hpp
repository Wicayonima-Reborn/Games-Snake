#pragma once

enum class GameMode {
    CLASSIC,
    SPEED,
    NO_WALL
};

inline float GetBaseSpeed(GameMode mode) {
    switch (mode) {
        case GameMode::CLASSIC: return 0.18f;
        case GameMode::SPEED:   return 0.12f;
        case GameMode::NO_WALL: return 0.15f;
    }
    return 0.15f;
}

inline const char* GetModeName(GameMode mode) {
    switch (mode) {
        case GameMode::CLASSIC: return "CLASSIC";
        case GameMode::SPEED:   return "SPEED";
        case GameMode::NO_WALL: return "NO WALL";
    }
    return "";
}

inline bool IsWallDeadly(GameMode mode) {
    return mode != GameMode::NO_WALL;
}