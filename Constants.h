#pragma once

// Board
const int ROWS = 6;
const int COLS = 7;
const int HUMAN = 1;
const int AI_Player = 2;
const int DEPTH = 5; // Difficulty level 

// Graphics
const int CELL = 100;
const int RADIUS = 40;
const int WIDTH = COLS * CELL;
const int HEIGHT = ROWS * CELL;

// Colors
#include <SFML/Graphics.hpp>
const sf::Color C_BG        (10,  12,  20);
const sf::Color C_BOARD     (15,  25,  80);
const sf::Color C_EMPTY     (7,   9,   15);
const sf::Color C_HUMAN     (220, 50,  50);
const sf::Color C_AI        (240, 200, 30);
const sf::Color C_HUMAN_HL  (255, 120, 120);
const sf::Color C_AI_HL     (255, 235, 120);
const sf::Color C_TEXT      (220, 230, 255);
const sf::Color C_BTN       (30,  45,  130);
 