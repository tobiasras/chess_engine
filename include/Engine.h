//
// Created by tobia on 18/01/2026.
//

#ifndef CHESS_ENGINE_ENGINE_H
#define CHESS_ENGINE_ENGINE_H

#include "Board.h"
#include "Move.h"
#include "string"


class Engine {
public:
    std::pair<Move, Move> bestMove(Board& board);

private:


};




#endif //CHESS_ENGINE_ENGINE_H