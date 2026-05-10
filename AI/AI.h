#pragma once
#include "../Board/Board.h"
class AI
{
private:
    int scoreBoard(const Board& board);
    int minimax(Board board, int depth, int alpha, int beta, bool maximizingPlayer);
    int scoreWindow(int window[4], int player);
public:
    int getBestMove(Board board);
};

