//
// Created by tobia on 18/01/2026.
//

#include "Move.h"
#include <string>




std::string Move::toUciString() const {
    char f = 'a' + (from % 8);
    char r = '1' + (from / 8);
    char t = 'a' + (to % 8);
    char s = '1' + (to / 8);
    return std::string{f,r,t,s};
}

Move Move::fromUciString(const std::string& s) {
    Move m{};
    m.from = (s[1]-'1')*8 + (s[0]-'a');
    m.to   = (s[3]-'1')*8 + (s[2]-'a');
    m.promotion = 0;

    // handle promotion
    if (s.length() == 5) {
        switch (s[4]) {
            case 'q': m.promotion = 4; break;
            case 'r': m.promotion = 3; break;
            case 'b': m.promotion = 2; break;
            case 'n': m.promotion = 1; break;
        }
    }
    return m;
}