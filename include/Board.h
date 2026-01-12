//
// Created by tobias on 1/6/26.
//

#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H
#include <cstdint>

class Board {
public:
    uint64_t whitePawns{};
    uint64_t blackPawns{};
    uint64_t whiteKnights{};
    uint64_t blackKnights{};
    uint64_t whiteBishops{};
    uint64_t blackBishops{};
    uint64_t whiteQueens{};
    uint64_t blackQueens{};
    uint64_t whiteKings{};
    uint64_t blackKings{};
    uint64_t whiteRooks{};
    uint64_t blackRooks{};
    bool whiteTurn{true};

    int enPassantSquare{-1};
    int moveSinceLastCapture{0};

    int halfMove {0};
    int fullMoves {1};

    bool whiteCanCastleKingSide{false};
    bool whiteCanCastleQueenSide{false};
    bool blackCanCastleKingSide{false};
    bool blackCanCastleQueenSide{false};

    void setup(const std::string &fenString);


private:
    void setPiece(const char &piece, size_t &x, size_t &y);
};

#endif // CHESS_ENGINE_BOARD_H
