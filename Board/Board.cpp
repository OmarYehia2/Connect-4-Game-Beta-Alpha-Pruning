#include "Board.h"

Board::Board(){
    reset();
}

void Board::reset() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            grid[i][j] = 0;
        }
    }
}

bool Board::isValid(int col) const {
    return col >= 0 && col < COLS && grid[0][col] == 0;
}

int Board::nextOpenRow(int col) const {
    for (int i = ROWS - 1; i >= 0; i--) {
        if (grid[i][col] == 0) {
            return i;
        }
    }
    return -1;
}

void Board::dropPiece(int row, int col, int piece) {
    grid[row][col] = piece;
}

bool Board::checkWin(int piece) const {
    // hor yaba
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(grid[i][j] == piece && grid[i][j + 1] == piece && grid[i][j + 2] == piece && grid[i][j + 3] == piece){
                return true;
            }
        }
    }
    // ver yaba
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS; j++){
            if(grid[i][j] == piece && grid[i + 1][j] == piece && grid[i + 2][j] == piece && grid[i + 3][j] == piece){
                return true;
            }
        }
    }
    // dig
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(grid[i][j] == piece && grid[i + 1][j + 1] == piece && grid[i + 2][j + 2] == piece && grid[i + 3][j + 3] == piece){
                return true;
            }
        }
    }
    for(int i = 3; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(grid[i][j] == piece && grid[i - 1][j + 1] == piece && grid[i - 2][j + 2] == piece && grid[i - 3][j + 3] == piece){
                return true;
            }
        }
    }

    return false;
}

bool Board::isFull() const{
    return getValidLocations().empty();
}

std::vector<int> Board::getValidLocations() const{
    std::vector<int> validLocations;
    for(int i = 0; i < COLS; i++){
        if(isValid(i)){
            validLocations.push_back(i);
        }
    }
    return validLocations;
}

std::vector<std::pair<int, int>> Board::getWinCells(int piece) const{
    std::vector<std::pair<int, int>> winCells;
    // hor yaba
    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(grid[i][j] == piece && grid[i][j + 1] == piece && grid[i][j + 2] == piece && grid[i][j + 3] == piece){
                winCells.push_back({i, j});
                winCells.push_back({i, j + 1});
                winCells.push_back({i, j + 2});
                winCells.push_back({i, j + 3});
            }
        }
    }
    // ver yaba
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS; j++){
            if(grid[i][j] == piece && grid[i + 1][j] == piece && grid[i + 2][j] == piece && grid[i + 3][j] == piece){
                winCells.push_back({i, j});
                winCells.push_back({i + 1, j});
                winCells.push_back({i + 2, j});
                winCells.push_back({i + 3, j});
            }
        }
    }
    // dig
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(grid[i][j] == piece && grid[i + 1][j + 1] == piece && grid[i + 2][j + 2] == piece && grid[i + 3][j + 3] == piece){
                winCells.push_back({i, j});
                winCells.push_back({i + 1, j + 1});
                winCells.push_back({i + 2, j + 2});
                winCells.push_back({i + 3, j + 3});
            }
        }
    }
    for(int i = 3; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){
            if(grid[i][j] == piece && grid[i - 1][j + 1] == piece && grid[i - 2][j + 2] == piece && grid[i - 3][j + 3] == piece){
                winCells.push_back({i, j});
                winCells.push_back({i - 1, j + 1});
                winCells.push_back({i - 2, j + 2});
                winCells.push_back({i - 3, j + 3});
            }
        }
    }
    return winCells;
}