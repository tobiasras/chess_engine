//
// Created by tobias on 1/6/26.
//

#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H

class Board {
public:
    long whitePawns{};
    long blackPawns{};
    long whiteKnights{};
    long blackKnights{};
    long whiteBishops{};
    long blackBishops{};
    long whiteQueens{};
    long blackQueens{};
    long whiteKings{};
    long blackKings{};
    long whiteRooks{};
    long blackRooks{};
    bool whiteTurn{true};

    int enPassantSquare{-1};
    int moveSinceLastCapture{0};

    bool whiteCanCastleKingSide{false};
    bool whiteCanCastleQueenSide{false};
    bool blackCanCastleKingSide{false};
    bool blackCanCastleQueenSide{false};

    void reset();
    void print();
};

#endif // CHESS_ENGINE_BOARD_H
