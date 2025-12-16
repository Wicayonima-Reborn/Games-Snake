#include "Mode.hpp"

float GetBaseSpeed(GameMode mode) {
    switch (mode) {
        case GameMode::CLASSIC: return 0.15f;
        case GameMode::SPEED:   return 0.08f;
        case GameMode::NO_WALL: return 0.15f;
        default: return 0.15f;
    }
}

bool IsWallDeadly(GameMode mode) {
    return mode != GameMode::NO_WALL;
}

const char* GetModeName(GameMode mode) {
    switch (mode) {
        case GameMode::CLASSIC: return "CLASSIC";
        case GameMode::SPEED:   return "SPEED";
        case GameMode::NO_WALL: return "NO WALL";
        default: return "UNKNOWN";
    }
}