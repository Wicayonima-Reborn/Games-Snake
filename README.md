# Games Snake

A modern Snake game written in **C++** using **raylib**, built with clean architecture and player-friendly controls.

This project is not just a basic Snake clone — it focuses on **good UX**, **clean code structure**, and **extensible design**.

---

##  Features

*  Classic Snake gameplay (grid-based)
*  **Queued input system** (smooth & fair controls)
*  Multiple game modes:

  * Classic
  * Speed
  * No Wall
*  Menu system & game states
*  Sound effects:

  * Eat food
  * Game over
  * Menu select
*  Dynamic speed progression based on score
*  Clean multi-file C++ architecture (`hpp` / `cpp`)
* 🪟 Windows build using MinGW + raylib

---

## Controls

### Menu

| Key     | Action       |
| ------- | ------------ |
| 1       | Classic mode |
| 2       | Speed mode   |
| 3       | No Wall mode |
| Q / Esc | Quit         |

### In Game

| Key        | Action              |
| ---------- | ------------------- |
| Arrow Keys | Move snake          |
| P          | Pause               |
| R          | Restart (Game Over) |
| M          | Back to menu        |
| Q / Esc    | Quit                |

---

## Input System

This game uses a **2-step queued input system** instead of classic single-frame input.

Benefits:

* Prevents unfair deaths caused by frame timing
* Allows quick direction changes (e.g. LEFT → UP)
* Feels responsive and modern while staying skill-based

---

## Project Structure

```
snake-raylib/
├─ assets/
│  └─ sfx/
│     ├─ eat.wav
│     ├─ GameOver.wav
│     └─ select.wav
├─ include/
│  ├─ Vec2.hpp
│  ├─ Snake.hpp
│  ├─ Food.hpp
│  ├─ Mode.hpp
│  ├─ Scene.hpp
│  └─ Game.hpp
├─ src/
│  ├─ main.cpp
│  ├─ Snake.cpp
│  ├─ Food.cpp
│  └─ Game.cpp
└─ README.md
```

---

## Build Instructions (Windows)

### Requirements

* MinGW (g++)
* raylib (installed & linked)
* Windows OS

### Compile

```bash
g++ src/*.cpp -Iinclude -o snake.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Run

```bash
./snake.exe
```

---

## 🔊 Audio Notes

* Sound effects use `.wav` format (recommended by raylib)
* Audio files must be placed relative to the executable:

```
assets/sfx/
```


---

Made with ❤️ and C++.