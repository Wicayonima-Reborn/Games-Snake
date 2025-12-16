# Games Snake

Simple Snake game written in C++ using raylib.

## Features
- Classic Snake gameplay
- Multiple game modes (Classic, Speed, No Wall)
- Pause & Restart
- Cross-platform (Windows / Linux)

## Build (Windows - MSYS2)
```bash
g++ src/*.cpp -Iinclude -o snake.exe -lraylib -lopengl32 -lgdi32 -lwinmm