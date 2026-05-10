#include "Game.h"

Game::Game()
    : window(sf::VideoMode({WIDTH, HEIGHT}), "Connect 4", sf::Style::Titlebar | sf::Style::Close),
      turn(HUMAN),
      winner(0),
      hoverCol(-1),
      gameOver(false),
      flashOn(false),
      statusText(font),
      btnText(font) 
{
    window.setFramerateLimit(60);

    font.openFromFile("C:/Windows/Fonts/arial.ttf");

    statusText.setFont(font);
    statusText.setCharacterSize(24);
    statusText.setFillColor(C_HUMAN);
    statusText.setString("Your turn!");
    statusText.setPosition({10, HEIGHT - 30});

    btnText.setFont(font);
    btnText.setCharacterSize(22);
    btnText.setFillColor(C_TEXT);
    btnText.setString("New Game");
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event -> is < sf::Event::Closed>()){
            window.close();
        }

        if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()) {
            const int col = mouseMoved->position.x / CELL;
            hoverCol = (col >= 0 && col < COLS) ? col : -1;
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button != sf::Mouse::Button::Left){
                continue;
            }

            const int mx = mousePressed->position.x;
            const int my = mousePressed->position.y;

            const sf::FloatRect btnRect({WIDTH / 2.f - 70.f, HEIGHT - 45.f}, {140.f, 35.f});
            if (gameOver && btnRect.contains(sf::Vector2f(static_cast<float>(mx), static_cast<float>(my)))) {
                resetGame();
                return;
            }

            if (!gameOver && turn == HUMAN){
                humanMove(mx / CELL);
            }
        }

        if (event -> is < sf::Event::MouseLeft>()){
            hoverCol = -1;
        }
    }
}

void Game::update() {
    if (!winCells.empty() && flashClock.getElapsedTime().asMilliseconds() > 350) {
        flashOn = !flashOn;
        flashClock.restart();
    }
}

void Game::render() {
    window.clear(C_BG);
    drawBoard();
    drawPreview();
    drawStatusBar();
    if (gameOver){
        drawRestartBtn();
    }
    window.display();
}

void Game::humanMove(int col) {
    if (!board.isValid(col)){
        return;
    }

    const int row = board.nextOpenRow(col);
    board.dropPiece(row, col, HUMAN);
    checkGameOver(HUMAN);

    if (!gameOver) {
        turn = AI_Player;
        statusText.setString("AI is thinking...");
        statusText.setFillColor(C_AI);
        render();
        aiMove();
    }
}

void Game::aiMove() {
    const int col = ai.getBestMove(board);
    const int row = board.nextOpenRow(col);
    board.dropPiece(row, col, AI_Player);
    checkGameOver(AI_Player);

    if (!gameOver) {
        turn = HUMAN;
        statusText.setString("Your turn! Click a column.");
        statusText.setFillColor(C_HUMAN);
    }
}

void Game::checkGameOver(int piece) {
    if (board.checkWin(piece)) {
        gameOver = true;
        winner = piece;
        winCells = board.getWinCells(piece);
        flashClock.restart();

        if (piece == HUMAN) {
            statusText.setString("You win!");
            statusText.setFillColor(C_HUMAN);
        }
        else {
            statusText.setString("AI wins!");
            statusText.setFillColor(C_AI);
        }
    }
    else if (board.isFull()) {
        gameOver = true;
        winner = 0;
        statusText.setString("It's a draw!");
        statusText.setFillColor(C_TEXT);
    }
}

void Game::resetGame() {
    board.reset();
    turn = HUMAN;
    winner = 0;
    hoverCol = -1;
    gameOver = false;
    flashOn = false;
    winCells.clear();

    statusText.setString("Your turn! Click a column.");
    statusText.setFillColor(C_HUMAN);
}

sf::Vector2f Game::cellCenter(int row, int col) const {
    return {col * CELL + CELL / 2.f, row * CELL + CELL / 2.f};
}

void Game::drawBoard() {
    sf::RectangleShape bg(sf::Vector2f(static_cast<float>(WIDTH), static_cast<float>(HEIGHT)));
    bg.setPosition({0.f, 0.f});
    bg.setFillColor(C_BOARD);
    window.draw(bg);

    if (hoverCol >= 0 && !gameOver) {
        sf::RectangleShape hl(sf::Vector2f(static_cast<float>(CELL), static_cast<float>(HEIGHT)));
        hl.setPosition({static_cast<float>(hoverCol * CELL), 0.f});
        hl.setFillColor(sf::Color(255, 255, 255, 20));
        window.draw(hl);
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            bool highlight = false;
            for (auto &cell : winCells) {
                if (cell.first == i && cell.second == j) {
                    highlight = true;
                    break;
                }
            }

            drawPiece(i, j, board.grid[i][j], highlight && flashOn);
        }
    }
}

void Game::drawPiece(int row, int col, int piece, bool highlight) {
    auto [cx, cy] = cellCenter(row, col);

    sf::Color color = C_EMPTY;
    if (piece == HUMAN){
        color = highlight ? C_HUMAN_HL : C_HUMAN;
    }
    else if (piece == AI_Player){
        color = highlight ? C_AI_HL : C_AI;
    }

    if (piece != 0) {
        sf::CircleShape shadow(RADIUS + 4.f);
        shadow.setOrigin({RADIUS + 4.f, RADIUS + 4.f});
        shadow.setPosition({cx + 2.f, cy + 2.f});
        shadow.setFillColor(sf::Color(0, 0, 0, 120));
        window.draw(shadow);
    }

    sf::CircleShape circle(RADIUS);
    circle.setOrigin({RADIUS, RADIUS});
    circle.setPosition({cx, cy});
    circle.setFillColor(color);
    window.draw(circle);

    if (piece != 0 && !highlight) {
        sf::CircleShape shine(8.f);
        shine.setOrigin({8.f, 8.f});
        shine.setPosition({cx - RADIUS * 0.35f, cy - RADIUS * 0.35f});
        shine.setFillColor(sf::Color(255, 255, 255, 80));
        window.draw(shine);
    }
}

void Game::drawPreview() {
    if (hoverCol < 0 || turn != HUMAN || gameOver){
        return;
    }

    const float cx = hoverCol * CELL + CELL / 2.f;
    const float cy = CELL / 2.f;

    sf::CircleShape circle(RADIUS);
    circle.setOrigin({RADIUS, RADIUS});
    circle.setPosition({cx, cy});
    circle.setFillColor(C_HUMAN);
    window.draw(circle);

    sf::CircleShape shine(8.f);
    shine.setOrigin({8.f, 8.f});
    shine.setPosition({cx - RADIUS * 0.35f, cy - RADIUS * 0.35f});
    shine.setFillColor(sf::Color(255, 255, 255, 80));
    window.draw(shine);
}

void Game::drawStatusBar() {
    window.draw(statusText);

    for (int i = 0; i < COLS; i++) {
        sf::Text num(font);
        num.setCharacterSize(13);
        num.setFillColor(sf::Color(80, 100, 180));
        num.setString(std::to_string(i));
        num.setPosition({i * CELL + CELL / 2.f - 4.f, HEIGHT - 20.f});
        window.draw(num);
    }
}

void Game::drawRestartBtn() {
    sf::RectangleShape btn(sf::Vector2f(140.f, 35.f));
    btn.setPosition({WIDTH / 2.f - 70.f, HEIGHT - 45.f});
    btn.setFillColor(C_BTN);
    btn.setOutlineColor(sf::Color(80, 100, 200));
    btn.setOutlineThickness(2.f);
    window.draw(btn);

    btnText.setPosition({WIDTH / 2.f - 40.f, HEIGHT - 40.f});
    window.draw(btnText);
}
