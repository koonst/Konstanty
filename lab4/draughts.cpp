#include "draughts.h"

#include <Windows.h>

void usleep(__int64 usec)
{
    HANDLE timer;
    LARGE_INTEGER ft;

    ft.QuadPart = -(10 * usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL);
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
}


Draughts::Draughts() {
    win.create(sf::VideoMode(size, size), "Draughts!");

    textures[0].loadFromFile("BOARD.png");
    textures[1].loadFromFile("RED_PAWN.png");
    textures[2].loadFromFile("RED_KING.png");
    textures[3].loadFromFile("BLACK_PAWN.png");
    textures[4].loadFromFile("BLACK_KING.png");
    textures[5].loadFromFile("Messages.png");

    sprites[0].setTexture(textures[0]);
    sprites[1].setTexture(textures[1]);
    sprites[2].setTexture(textures[2]);
    sprites[3].setTexture(textures[3]);
    sprites[4].setTexture(textures[4]);
    sprites[5].setTexture(textures[5]);

    side = false;
    player = !side;
}

void Draughts::play() 
{
    if (gameStart()) 
    {
        while (win.isOpen()) 
        {
            draw();
            win.display();
       
                if (player) 
                {
                    
                    playerMove();
                    usleep(100);
                }
                else
                {
                    cpuMove(side);
                }
            
                side = !side;
            //player = !player;


            
            
      
            if (gameOver(board.checkState(player)))
                return;
        }
    }
}

bool Draughts::gameStart() {
    sprites[5].setPosition(62, 330);
    if (side)
        sprites[5].setTextureRect(sf::IntRect(0, 0, 725, 200));
    else
        sprites[5].setTextureRect(sf::IntRect(0, 200, 725, 200));
    draw();
    win.draw(sprites[5]);
    win.display();
    sf::Event event;
    while (true) {
        if (win.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                return 0;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space)
                    return 1;
                else if (event.key.code == sf::Keyboard::Return)
                    side = !side;
                player = !player;
                if (side)
                    sprites[5].setTextureRect(sf::IntRect(0, 0, 725, 200));
                else
                    sprites[5].setTextureRect(sf::IntRect(0, 200, 725, 200));
                draw();
                win.draw(sprites[5]);
                win.display();
                break;
            }
        }
    }
}

int Draughts::gameOver(int state) {
    switch (state) {
    case 0:
        return 0;
    case -1:
        sprites[5].setTextureRect(sf::IntRect(0, 800, 725, 200));
        break;
    case 1:
        sprites[5].setTextureRect(sf::IntRect(0, 400, 725, 200));
        break;
    case 2:
        sprites[5].setTextureRect(sf::IntRect(0, 600, 725, 200));
        break;
    }
    sprites[5].setPosition(62, 330);
    draw();
    win.draw(sprites[5]);
    win.display();
    sf::Event event;
    while (true) {
        if (win.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                return 1;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Space) {
                    board.reset();
                    player = !side;
                    return !gameStart();
                }
            }
        }
    }
}

void Draughts::playerMove() 
{
    int first, second, moveResult{};
    do {
        if (moveResult == 0) 
        {
            if ((first = mouse()) == -1)
                return;
        }
        do
            if ((second = mouse()) == -1)
                return;
        while (second == first);

        moveResult = board.move(first / 10, first % 10, second / 10, second % 10, side);
        if (moveResult == 2) 
        {
            first = second;
            draw();
            win.display();
        }
    } while (moveResult != 1);
}

void Draughts::cpuMove(bool side1) 
{
    auto move = AI::getBestMove(3, board, side1 );
    for (auto& coords : move.coords) 
    {
        board.move(coords);
        draw();
        win.display();
        usleep(100);
    }
}

bool Draughts::handleEvents() 
{
    sf::Event event;
    while (win.pollEvent(event)) 
    {
        if (event.type == sf::Event::Closed) 
        {
            win.close();
            return true;
        }
    }
    return false;
}

int Draughts::mouse() 
{
    sf::Vector2i position;
    while (true) 
    {
        if (handleEvents())
            return -1;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
        {
            position = sf::Mouse::getPosition(win);
            if (position.x > 25 && position.x < 825 && position.y > 25 && position.y < 825) 
            {
                position.y -= 25;
                position.x -= 25;
                return (position.y - position.y % 100) / 10 + (position.x / 100);
            }
        }
    }
}

void Draughts::draw() 
{
    win.clear(sf::Color(41, 41, 41));
    win.draw(sprites[0]);
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 8; j++) 
        {
            switch (board.board[i][j]) 
            {
            case RED_PAWN:
                sprites[1].setPosition(35 + j * 100, 35 + i * 100);
                win.draw(sprites[1]);
                break;
            case RED_KING:
                sprites[2].setPosition(35 + j * 100, 35 + i * 100);
                win.draw(sprites[2]);
                break;
            case BLACK_PAWN:
                sprites[3].setPosition(35 + j * 100, 35 + i * 100);
                win.draw(sprites[3]);
                break;
            case BLACK_KING:
                sprites[4].setPosition(35 + j * 100, 35 + i * 100);
                win.draw(sprites[4]);
                break;
            }
        }
    }
}
