#pragma once
#include <vector>
#include "../Constants.h"

class Board
{
public:
    Board();
    int grid[ROWS][COLS];
    void reset();
    bool isValid(int col) const;
    int nextOpenRow(int col) const;
    void dropPiece(int row, int col, int piece);
    bool checkWin(int player) const;
    bool isFull() const;
    std::vector<int> getValidLocations() const;
    std::vector<std::pair<int, int>> getWinCells(int piece) const;
};
