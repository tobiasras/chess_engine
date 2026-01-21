//
// Created by tobias on 1/6/26.
//

#ifndef CHESS_ENGINE_BOARD_H
#define CHESS_ENGINE_BOARD_H
#include "Move.h"
#include <cstdint>
#include <string>

class Board {
public:
    void setup(const std::string &fenString);
    void reset();

    void makeMove(const Move &move);
    void undoMove(const Move &move);

    // helpers
    uint64_t whitePieces() const;
    uint64_t blackPieces() const;
    uint64_t occupied() const;
    bool isInCheck() const;

    // debugging
    void boardToText();

private:
    void undoCaptureLikeMove(const Move &move);
    void setPiece(const char &piece, size_t index);
    char getPieceFromIndex(const size_t &index);
    uint64_t& getBoardFromPiece(const char &piece);

    // current board
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

    // previous move info

    char prevPieceCaptured{};
    size_t prevCaptureIndex{};
    size_t prevHalfMoves{};



};






#endif // CHESS_ENGINE_BOARD_H
