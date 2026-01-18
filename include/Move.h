//
// Created by tobia on 18/01/2026.
//

#ifndef CHESS_ENGINE_MOVE_H
#define CHESS_ENGINE_MOVE_H

#include <cstdint>
#include <string>





struct Move {
    uint8_t from;
    uint8_t to;
    uint8_t promotion;

    Move fromUciString(const std::string& s);
    std::string toUciString() const;
};


#endif //CHESS_ENGINE_MOVE_H