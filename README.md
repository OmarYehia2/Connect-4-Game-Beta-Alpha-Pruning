🔴🟡 Connect Four — AI with Minimax & Alpha-Beta Pruning

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B%2017-blue?style=for-the-badge&logo=cplusplus"/>
  <img src="https://img.shields.io/badge/GUI-SFML%202.5-green?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Algorithm-Minimax-orange?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Optimization-Alpha--Beta%20Pruning-red?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Platform-Windows-lightgrey?style=for-the-badge&logo=windows"/>
</p>

<p align="center">
  A fully playable <strong>Connect Four</strong> game built in C++ with an SFML graphical interface.
  The AI opponent uses the classic <strong>Minimax algorithm</strong> enhanced with
  <strong>Alpha-Beta Pruning</strong> to search game states efficiently and play at a strong level.
</p>

---

## 📸 Screenshots

Gameplay
<p align="center">
  <img src="https://github.com/user-attachments/assets/4e1b8ea4-e6eb-4e82-969c-5d51d8503ca3" width="500"/>
</p>

---

## 🎮 Features

- 🧠 **Smart AI** — Minimax with Alpha-Beta Pruning, looks 5 moves ahead
- 🖱️ **Smooth GUI** — Built with SFML, fully mouse-driven
- ✨ **Visual effects** — Piece glow, column hover highlight, floating preview piece
- 🏆 **Win animation** — Winning 4 pieces flash to highlight the result
- 🔄 **Instant restart** — New Game button appears after every match
- 📐 **Clean architecture** — Separated into Board, AI, Game, and Renderer classes

---

## 🧠 How the AI Works

### Minimax Algorithm
The AI simulates all possible future moves up to a set depth, alternating between:
- **Maximizer (AI)** — picks the move with the highest score
- **Minimizer (Human)** — picks the move with the lowest score (worst for AI)

### Alpha-Beta Pruning
An optimization that cuts branches that cannot affect the final decision:
- **Alpha** — best score the Maximizer is guaranteed so far
- **Beta** — best score the Minimizer is guaranteed so far
- If `alpha >= beta` → prune the branch ✂️

This reduces the number of nodes evaluated from ~100,000 to ~1,000 at depth 5.

### Heuristic Scoring
At non-terminal leaf nodes, the board is scored by evaluating every window of 4 cells:

| Pattern | Score |
|---|---|
| 4 AI pieces | +100 |
| 3 AI + 1 empty | +5 |
| 2 AI + 2 empty | +2 |
| 3 Human + 1 empty | -4 (block!) |
| Center column piece | +3 |

---

## 🗂️ Project Structure

```
connect4/
│
├── main.cpp          # Entry point — launches the game
├── Constants.h       # All constants: board size, colors, depth
├── Board.h / .cpp    # Board logic: drop piece, win detection, valid moves
├── AI.h    / .cpp    # Minimax + Alpha-Beta Pruning
├── Game.h  / .cpp    # Game loop, SFML rendering, event handling
```

---

## 🚀 Getting Started

### Prerequisites

- C++20 compatible compiler (GCC / MSVC / Clang)
- [SFML 3.10](https://www.sfml-dev.org/download.php)

### Build with g++

```bash
 C:\msys64\ucrt64\bin\g++.exe -g -mwindows -static-libgcc -static-libstdc++ -DSFML_STATIC `
>> "D:\AI Game\main.cpp" `
>> "D:\AI Game\Game\Game.cpp" `
>> "D:\AI Game\Board\Board.cpp" `
>> "D:\AI Game\AI\AI.cpp" `
>> -ID:\SFML-3.1.0\include -LD:\SFML-3.1.0\lib `
>> -o "D:\AI Game\Connect4.exe" `
>> -lsfml-graphics-s -lsfml-window-s -lsfml-system-s `
>> -lfreetype -lharfbuzz -lopengl32 -lgdi32 -lwinmm
./Connect4
```


## 🕹️ How to Play

| Action | Control |
|---|---|
| Drop a piece | Click on a column |
| See where you'll play | Hover over a column |
| Restart the game | Click **New Game** button |

- You are **RED 🔴** — the AI is **YELLOW 🟡**
- First to connect **4 in a row** (horizontal, vertical, or diagonal) wins!

---

## ⚙️ Configuration

All settings are in `Constants.h`:

```cpp
const int DEPTH = 5;   // AI difficulty: 3 = easy | 5 = medium | 7 = hard
const int ROWS  = 6;   // Board rows
const int COLS  = 7;   // Board columns
const int CELL  = 100; // Cell size in pixels
```

> ⚠️ Increasing `DEPTH` beyond 7 may cause noticeable lag.

---

## 📦 Dependencies

| Library | Version | Purpose |
|---|---|---|
| [SFML](https://www.sfml-dev.org/) | 3.10 | Window, rendering, events |
| C++ STL | C++20 | Vectors, algorithms |

---

## 🧩 Algorithm Complexity

| Metric | Without Pruning | With Alpha-Beta |
|---|---|---|
| Nodes at depth 5 | ~100,000 | ~1,000 |
| Time per move | ~2–3 sec | < 0.5 sec |
| Branching factor | 7 | ~3–4 (effective) |

---

## 📚 References

- [Minimax Algorithm — Wikipedia](https://en.wikipedia.org/wiki/Minimax)
- [Alpha-Beta Pruning — Wikipedia](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning)
- [SFML Documentation](https://www.sfml-dev.org/documentation/2.5.1/)

---

## 👨‍💻 Author

**Omar** — Computer Science Student

> *This project was built as a university assignment to demonstrate AI game-tree search algorithms.*

---

## 📄 License

This project is licensed under the **MIT License** — feel free to use, modify, and distribute.
