#include "AI.h"
#include <climits>
#include <algorithm>

int AI::scoreBoard(const Board& board) {
    int score = 0, player = AI_Player; // AI
    
    // Mid Col & Hor
    for(int i = 0; i < ROWS; i++){
        score += (board.grid[i][COLS >> 1] == player ? 3 : 0);
        for(int j = 0; j < COLS - 3; j++){
            int window[4] = {board.grid[i][j], board.grid[i][j + 1], board.grid[i][j + 2], board.grid[i][j + 3]};
            score += scoreWindow(window, player);
        }
    }

    // Ver
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS; j++){
            int window[4] = {board.grid[i][j], board.grid[i + 1][j], board.grid[i + 2][j], board.grid[i + 3][j]};
            score += scoreWindow(window, player);
        }
    }

    // Diag
    for(int i = 0; i < ROWS - 3; i++){
        for(int j = 0; j < COLS - 3; j++){
            int window[4] = {board.grid[i][j], board.grid[i + 1][j + 1], board.grid[i + 2][j + 2], board.grid[i + 3][j + 3]};
            score += scoreWindow(window, player);
        }
    }
    for(int i = 3; i < ROWS; i++){
        for(int j = 0; j < COLS - 3; j++){
            int window[4] = {board.grid[i][j], board.grid[i - 1][j + 1], board.grid[i - 2][j + 2], board.grid[i - 3][j + 3]};
            score += scoreWindow(window, player);
        }
    }

    return score;
}

int AI::scoreWindow(int window[4], int player) {
    int opponent = player == HUMAN ? AI_Player : HUMAN;
    int countPlayer = std::count(window, window + 4, player);
    int countOpponent = std::count(window, window + 4, opponent);
    int countEmpty = 4 - countPlayer - countOpponent;

    if(countPlayer == 4){ // 4 pieces = win
        return 100;
    }
    if(countPlayer == 3 && countEmpty == 1){ // 3 pieces and 1 mfesh = good move
        return 5;
    }
    if(countPlayer == 2 && countEmpty == 2){ // 2 pieces and 2 mfesh = ok move
        return 2;
    }
    if(countOpponent == 3 && countEmpty == 1){ // 3 opponent pieces and 1 mfesh = bad move
        return -4;
    }
    return 0;
}

int AI::minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer) {
    if(board.checkWin(AI_Player)){
        return INT_MAX;
    }
    if(board.checkWin(HUMAN)){
        return INT_MIN;
    }
    if(board.isFull()){
        return 0;
    }
    if(depth == 0){
        return scoreBoard(board);
    }

    auto cols = board.getValidLocations();
    int best = cols[0];
    if(maximizingPlayer){
        int maximum = INT_MIN;
        for(auto &col : cols){
            Board tmp = board;
            tmp.dropPiece(tmp.nextOpenRow(col), col, AI_Player);
            int ret = minimax(tmp, depth - 1, alpha, beta, false);
            if(ret > maximum){
                maximum = ret;
                best = col;
            }
            alpha = std::max(alpha, maximum);
            if(alpha >= beta){ // Cut 3lashan el opponent 3andoh move asghar aw y3adel 3ala el move bta3o
                break;
            }
        } 
        return maximum;
    }
    else{
        int minimum = INT_MAX;
        for(auto &col : cols){
            Board tmp = board;
            tmp.dropPiece(tmp.nextOpenRow(col), col, HUMAN);
            int ret = minimax(tmp, depth - 1, alpha, beta, true);
            if(ret < minimum){
                minimum = ret;
                best = col;
            }
            beta = std::min(beta, minimum);
            if(alpha >= beta){ // Cut 3lashan el opponent 3andoh move akbar aw y3adel 3ala el move bta3o
                break;
            }
        } 
        return minimum;
    }
}

int AI::getBestMove(Board board) {
    auto cols = board.getValidLocations();
    int best = cols[0], maximum = INT_MIN;
    for(auto &col : cols){
        Board tmp = board;
        tmp.dropPiece(tmp.nextOpenRow(col), col, AI_Player);
        int ret = minimax(tmp, DEPTH - 1, INT_MIN, INT_MAX, false);
        if(ret > maximum){
            maximum = ret;
            best = col;
        }
    }
    return best;
}