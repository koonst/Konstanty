#pragma once
#ifndef DRAUGHTS_H
#define DRAUGHTS_H

#include <io.h>
#include <SFML/Graphics.hpp>
#include "board.h"
#include "ai.h"

const int size = 850;

class Draughts {
    // 0 human 1 AI
    bool player;
    bool side;

    sf::RenderWindow win;
    sf::Texture textures[6];
    sf::Sprite sprites[6];

    Board board;

public:

    Draughts();

    void play();
 
    bool gameStart();

    int gameOver(int state);

    void playerMove();

    void cpuMove(bool second = false);
 
    bool handleEvents();
 
    int mouse();

    void draw();
};

#endif
