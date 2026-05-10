#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "../Board/Board.h"
#include "../AI/AI.h"
#include "../Constants.h"

class Game {
public:
    Game();
    void run();
private:
    sf::RenderWindow window;
    Board board;
    AI ai;
    int turn, winner, hoverCol;
    bool gameOver;

    std::vector<std::pair<int, int>> winCells;
    sf::Clock flashClock;
    bool flashOn;
    sf::Font font;
    sf::Text statusText, btnText;

    void processEvents();
    void update();
    void render();
    
    void humanMove(int col);
    void aiMove();
    void checkGameOver(int piece);
    void resetGame();

    void drawBoard();
    void drawPiece(int row, int col, int piece, bool highlight);
    void drawPreview();
    void drawStatusBar();
    void drawRestartBtn();

    sf::Vector2f cellCenter(int row, int col) const;
};
