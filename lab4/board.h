#pragma once
#ifndef BOARD_H_ 
#define BOARD_H_

#include <vector>
#include <cmath>

// struct for move coords
struct Coords {
    int x1 : 4;
    int y1 : 4;
    int x2 : 4;
    int y2 : 4;
    Coords(int x1_, int y1_, int x2_, int y2_);
    bool operator!= (const Coords& B);
};

// all coords that make moves
struct Move {
    std::vector< Coords > coords;
    Move() {}
    Move(int x1, int y1, int x2, int y2);
    Move(Coords c);
    void add(Coords c);
    bool operator== (const Move& B);
};

// all viable field's states
enum Pawns {
    EMPTY,
    RED_PAWN,
    BLACK_PAWN,
    RED_KING,
    BLACK_KING
};

class Board {
public:
    Pawns board[8][8];
    // for game judging
    int drawCounter;
    int redP, blackP, redK, blackK;
    Board();
    void reset();
    // returns 1 if capture available
    bool checkCapture(int x, int y);
    bool checkCapture(bool color);
    // returns all variations of the move
    std::vector< Move > getMoveSequences(Move move, Board b);
    // return viable first moves
    std::vector< Move > getViableMoves(bool color);
    std::vector< Move > getViableMoves(int x, int y);
    // capture pawn or king from between those coords
    void capture(int x1, int y1, int x2, int y2);
    // returns 0 if wrong move, 1 if finished, and 2 if there is still a capture to do
    int move(Coords m);
    int move(Move m);
    int move(int x1, int y1, int x2, int y2, bool color);
    // returns 0 if game continues 1 if red won, 2 if black won, -1 if tie 
    int checkState(bool color);
    // evaluate board situation, param color defines currently moving side
    int evaluateField(int x, int y);
    int evaluateBoard(bool color, bool side);
};

#endif