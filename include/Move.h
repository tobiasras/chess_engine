//
// Created by tobia on 18/01/2026.
//

#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <cstdint>
#include <string>



enum Type {
    NOT_SET = 0,
    MOVE = 1,
    CAPTURE = 2,
    PROMOTION = 3,
    CASTLING = 4,
    EN_PASSANT = 5,
};

enum Promotion {
    NONE = 0,
    QUEEN = 1,
    ROOK = 2,
    KNIGHT = 3,
    BISHOP = 4,
};


struct Move {
    size_t from;
    size_t to;
    Promotion promotion {NONE};
    Type type {NOT_SET};

    Move fromUciString(const std::string& s);
    std::string toUciString() const;
};


#endif //CHESS_ENGINE_MOVE_H