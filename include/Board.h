//
// Created by tobias on 1/6/26.
//

#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H
#include <cstdint>

class Board {
public:
    void setup(const std::string &fenString);
    void makeMove(const std::string &move);
    void reset();
    // debugging
    void boardToText();

private:
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

    size_t enPassantSquare{65};

    size_t halfMove {0};
    size_t fullMoves {1};

    bool whiteCanCastleKingSide{false};
    bool whiteCanCastleQueenSide{false};
    bool blackCanCastleKingSide{false};
    bool blackCanCastleQueenSide{false};

    void setPiece(const char &piece, size_t index);
    char getPieceFromIndex(size_t &index);
    uint64_t& getBoardFromPiece(const char &piece);

};






#endif // CHESS_ENGINE_BOARD_H
