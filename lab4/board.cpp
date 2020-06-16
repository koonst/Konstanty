#include "board.h"

// Coords~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Coords::Coords(int x1_, int y1_, int x2_, int y2_) {
    x1 = x1_;
    y1 = y1_;
    x2 = x2_;
    y2 = y2_;
}
bool Coords::operator!= (const Coords& B) {
    if (this->x1 != B.x1 ||
        this->y1 != B.y1 ||
        this->x2 != B.x2 ||
        this->y2 != B.y2)
        return true;
    return false;
}

// Moves~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Move::Move(int x1, int y1, int x2, int y2) {
    coords.emplace_back(x1, y1, x2, y2);
}
Move::Move(Coords c) {
    coords.push_back(c);
}
void Move::add(Coords c) {
    coords.insert(coords.begin(), c);
}
bool Move::operator== (const Move& B) {
    if (this->coords.size() != B.coords.size())
        return false;
    else
        for (int i = 0; i < coords.size(); i++)
            if (this->coords[i] != B.coords[i])
                return false;
    return true;
}

// Board~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Board::Board() {
    reset();
}

void Board::reset() {
    drawCounter == 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (i % 2 != j % 2) {
                if (i < 3)
                    board[i][j] = RED_PAWN;
                else if (i > 4)
                    board[i][j] = BLACK_PAWN;
                else
                    board[i][j] = EMPTY;
            }
            else
                board[i][j] = EMPTY;
        }
    }
}

bool Board::checkCapture(int x, int y) {
    // red 0, black 1
    bool color = (board[x][y] == RED_PAWN || board[x][y] == RED_KING) ? 0 : 1;
    // check for pawns
    if (board[x][y] == RED_PAWN || board[x][y] == BLACK_PAWN) {
        for (int a : {-1, 1}) {
            for (int b : {-1, 1}) {
                int i = x + a;
                int j = y + b;
                if (i + a < 8 && i + a >= 0 && j + b < 8 && j + b >= 0) {
                    if (color) {
                        if (board[i][j] == RED_KING || board[i][j] == RED_PAWN)
                            if (board[i + a][j + b] == EMPTY)
                                return true;
                    }
                    else {
                        if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN)
                            if (board[i + a][j + b] == EMPTY)
                                return true;
                    }
                }
            }
        }
    }
    // check for kings
    else if (board[x][y] == RED_KING || board[x][y] == BLACK_KING) {
        for (int a : {-1, 1}) {
            for (int b : {-1, 1}) {
                int i = x + a;
                int j = y + b;
                while (i + a < 8 && i + a >= 0 && j + b < 8 && j + b >= 0) {
                    if (color) {
                        if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN)
                            break;
                        if (board[i][j] == RED_KING || board[i][j] == RED_PAWN) {
                            if (board[i + a][j + b] == EMPTY)
                                return true;
                            else
                                break;
                        }
                    }
                    else {
                        if (board[i][j] == RED_KING || board[i][j] == RED_PAWN)
                            break;
                        if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN) {
                            if (board[i + a][j + b] == EMPTY)
                                return true;
                            else
                                break;
                        }
                    }
                    i += a;
                    j += b;
                }
            }
        }
    }
    return false;
}

bool Board::checkCapture(bool color) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (color) {
                if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN)
                    if (checkCapture(i, j))
                        return true;
            }
            else {
                if (board[i][j] == RED_KING || board[i][j] == RED_PAWN)
                    if (checkCapture(i, j))
                        return true;
            }
        }
    }
    return false;
}

// get all viable sequences after first move
std::vector< Move > Board::getMoveSequences(Move move, Board b) {
    std::vector< Move > moves;
    if (b.move(move.coords[0]) == 1) {
        moves.emplace_back(move.coords[0]);
    }
    else {
        for (auto& m : b.getViableMoves(move.coords[0].x2, move.coords[0].y2)) {
            std::vector< Move > tmp = getMoveSequences(m, b);
            moves.insert(moves.end(), tmp.begin(), tmp.end());
        }
        for (auto& m : moves) {
            m.add(move.coords[0]);
        }
        return moves;
    }
}

// get all viable first moves for a color
std::vector< Move > Board::getViableMoves(bool color) {
    std::vector< Move > moves;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (color) {
                if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN) {
                    auto tmp = getViableMoves(i, j);
                    for (auto& m : tmp) {
                        auto tmp2 = getMoveSequences(m, *this);
                        moves.insert(moves.end(), tmp2.begin(), tmp2.end());
                    }
                }
            }
            else {
                if (board[i][j] == RED_KING || board[i][j] == RED_PAWN) {
                    auto tmp = getViableMoves(i, j);
                    for (auto& m : tmp) {
                        auto tmp2 = getMoveSequences(m, *this);
                        moves.insert(moves.end(), tmp2.begin(), tmp2.end());
                    }
                }
            }
        }
    }
    return moves;
}

// get all viable first moves for a pawn
std::vector< Move > Board::getViableMoves(int x, int y) {
    bool color;
    std::vector< Move > moves;
    // if a field is empty return empty vector
    if (board[x][y] == EMPTY)
        return moves;
    if (board[x][y] == RED_PAWN || board[x][y] == RED_KING) {
        color = 0;
    }
    else {
        color = 1;
    }
    // If a capture is possible on the other move just return empty vector
    if (checkCapture(color) != checkCapture(x, y))
        return moves;
    // Check for pawns
    if (board[x][y] == RED_PAWN || board[x][y] == BLACK_PAWN) {
        // If there are no capturing opportunities
        if (!checkCapture(x, y)) {
            int xdir = color ? -1 : 1;
            if (y < 7)
                if (board[x + xdir][y + 1] == EMPTY)
                    moves.push_back(Move(x, y, x + xdir, y + 1));
            if (y > 0)
                if (board[x + xdir][y - 1] == EMPTY)
                    moves.push_back(Move(x, y, x + xdir, y - 1));
            // If there are captures available
        }
        else {
            for (int a : {-1, 1}) {
                for (int b : {-1, 1}) {
                    int i = x + a;
                    int j = y + b;
                    if (i + a < 8 && i + a >= 0 && j + b < 8 && j + b >= 0) {
                        if (color) {
                            if (board[i][j] == RED_KING || board[i][j] == RED_PAWN)
                                if (board[i + a][j + b] == EMPTY)
                                    moves.push_back(Move(x, y, i + a, j + b));
                        }
                        else {
                            if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN)
                                if (board[i + a][j + b] == EMPTY)
                                    moves.push_back(Move(x, y, i + a, j + b));
                        }
                    }
                }
            }
        }
        // Check for Kings
    }
    else {
        // flag if the move is a capture
        bool captureFlag = checkCapture(x, y);
        // for each direction
        for (int a : {-1, 1}) {
            for (int b : {-1, 1}) {
                int i = x + a;
                int j = y + b;
                // move until there is an obstacle on a path
                while (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
                    //if not capturing add those moves
                    if (board[i][j] == EMPTY) {
                        if (!captureFlag)
                            moves.push_back(Move(x, y, i, j));
                    }
                    else if (color) {
                        // break if an ally on path
                        if (board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN)
                            break;
                        // add all moves possible after a capture
                        else if ((board[i][j] == RED_KING || board[i][j] == RED_PAWN) && captureFlag) {
                            do {
                                i += a;
                                j += b;
                                if (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
                                    if (board[i][j] == EMPTY)
                                        moves.push_back(Move(x, y, i, j));
                                    else
                                        break;
                                }
                                else
                                    break;
                            } while (true);
                            break;
                        }
                        else
                            break;
                    }
                    else {
                        // break if an ally on path
                        if (board[i][j] == RED_KING || board[i][j] == RED_PAWN)
                            break;
                        // add all moves possible after a capture
                        if ((board[i][j] == BLACK_KING || board[i][j] == BLACK_PAWN) && captureFlag) {
                            do {
                                i += a;
                                j += b;
                                if (i >= 0 && j >= 0 && i <= 7 && j <= 7) {
                                    if (board[i][j] == EMPTY)
                                        moves.push_back(Move(x, y, i, j));
                                    else
                                        break;
                                }
                                else
                                    break;
                            } while (true);
                            break;
                        }
                        else
                            break;
                    }
                    i += a;
                    j += b;
                }
            }
        }
    }
    return moves;
}

// capture pawn or king from between those coords
void Board::capture(int x1, int y1, int x2, int y2) {
    // mark direction
    int a = (x1 < x2) ? 1 : -1;
    int b = (y1 < y2) ? 1 : -1;
    // for all fields through the way
    for (int i = x1 + a, j = y1 + b; i != x2, j != y2; i += a, j += b) {
        // clear it
        board[i][j] = EMPTY;
    }
}

// returns 0 if wrong move, 1 if finished, and 2 if there is still a capture to do
int Board::move(Coords m) {
    bool color = (board[m.x1][m.y1] == RED_KING || board[m.x1][m.y1] == RED_PAWN) ? 0 : 1;
    return move(m.x1, m.y1, m.x2, m.y2, color);
}

int Board::move(Move m) {
    bool color = (board[m.coords[0].x1][m.coords[0].y1] == RED_KING ||
        board[m.coords[0].x1][m.coords[0].y1] == RED_PAWN) ? 0 : 1;
    int i{};
    while (move(m.coords[i]) == 2)
        i++;
    return 1;
}

int Board::move(int x1, int y1, int x2, int y2, bool color) {
    // check if player moved right color
    if ((color && (board[x1][y1] == RED_KING || board[x1][y1] == RED_PAWN)) ||
        (!color && (board[x1][y1] == BLACK_KING || board[x1][y1] == BLACK_PAWN)))
        return 0;

    bool captureFlag = false;
    // if given move is in viable moves for that pawn/king
    for (auto& move : getViableMoves(x1, y1)) {
        if (move == Move(x1, y1, x2, y2)) {
            // if a move included capture
            if (checkCapture(color)) {
                capture(x1, y1, x2, y2);
                captureFlag = true;
            }
            board[x2][y2] = board[x1][y1];
            board[x1][y1] = EMPTY;
            // if there is still a capture for this pawn/king
            if (captureFlag && checkCapture(x2, y2))
                return 2;
            // if a move ended in a promote
            else if ((!color && x2 == 7) || (color && x2 == 0))
                board[x2][y2] = color ? BLACK_KING : RED_KING;
            return 1;
        }
    }
    return 0;
}

// returns 0 if game continues 1 if red won, 2 if black won, -1 if tie 
int Board::checkState(bool color) {
    int redPawns{}, blackPawns{}, redKings{}, blackKings{};
    bool redMoves{}, blackMoves{};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
            case EMPTY:
                break;
            case RED_PAWN:
                if (!redMoves)
                    if (getViableMoves(i, j).size() != 0)
                        redMoves = true;
                redPawns++;
                break;
            case BLACK_PAWN:
                if (!blackMoves)
                    if (getViableMoves(i, j).size() != 0)
                        blackMoves = true;
                blackPawns++;
                break;
            case RED_KING:
                if (!redMoves)
                    if (getViableMoves(i, j).size() != 0)
                        redMoves = true;
                redKings++;
                break;
            case BLACK_KING:
                if (!blackMoves)
                    if (getViableMoves(i, j).size() != 0)
                        blackMoves = true;
                blackKings++;
                break;
            }
        }
    }
    if ((blackPawns || blackKings) && (redPawns || redKings) && ((color && blackMoves) || (!color && redMoves))) {
        if (blackKings && redKings &&
            blackPawns == blackP &&
            redPawns == redP &&
            blackKings == blackK &&
            redKings == redK) {
            if (++drawCounter == 30)
                return -1;
            else
                drawCounter = 0;
        }
        blackP = blackPawns;
        redP = redPawns;
        blackK = blackKings;
        redK = redKings;
        return 0;
    }
    else if ((!blackPawns && !blackKings) || (color && !blackMoves))
        return 1;
    else if ((!redPawns && !redKings) || (!color && !redMoves))
        return 2;
}

// evaluate value of a field
// pawn 7 points
// last row + 0
// semi last row + 1
// 3rd row + 2
// > 4th row + 3
// king 25 points
// anything almost connected with left or right border + 1 point 
// directly connected +2
// capture oportunity + 15
int Board::evaluateField(int x, int y) {
    int score{};
    switch (board[x][y]) {
    case EMPTY:
        break;
    case RED_PAWN:
        score += 7;
        if (x > 0) {
            score += 2;
            if (x > 1) {
                score++;
                if (x > 2)
                    score++;;
            }
        }
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6)
                score++;
        }
        score += 15;
        break;
    case BLACK_PAWN:
        score += 7;
        if (x < 7) {
            score += 2;
            if (x < 6) {
                score++;
                if (x < 5)
                    score++;
            }
        }
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6)
                score++;
        }
        score += 15;
        break;
    case RED_KING:
        score += 25;
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6)
                score++;
        }
        score += 15;
        break;
    case BLACK_KING:
        score += 25;
        if (y < 2 || y > 5) {
            score++;
            if (y < 1 || y > 6)
                score++;
        }
        score += 15;
        break;
    }
    return score;
}

// returns value depending on game state and sum of field values
int Board::evaluateBoard(bool color, bool side) {
    switch (checkState(color)) {
    case -1:
        return 0;
    case 0:
        break;
    case 1:
        return side ? -10000 : 10000;
    case 2:
        return side ? 10000 : -10000;
    }
    int black{}, red{};
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == RED_KING || board[i][j] == RED_PAWN)
                red += evaluateField(i, j);
            else if (board[i][j] != EMPTY)
                black += evaluateField(i, j);
        }
    }
    if (side)
        return black - red;
    else
        return red - black;
}
