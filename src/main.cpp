#include <iostream>
#include "Board.h"



int main() {
    Board board;
    board.print();
    std::cout<< board.blackKings << std::endl;
    return 0;
}
