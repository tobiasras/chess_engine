#include <iostream>
#include <ostream>

#include "Board.h"

#include <vector>
#include <_bsd_types.h>

namespace {
    void setBitBoard(uint64_t &board, size_t x, size_t y) {
        board |= 1ULL << (y * 8 + x);
    }

    // chess pos e4
    int chessPosToindex(std::string chessPos) {
        const int x = chessPos[0] - 'a';
        const int y = chessPos[1] - '1';
        if (x > 7 || y > 7)
            throw std::out_of_range("Chess position out of bounds: " + chessPos);
        return y * 8 + x;
    }
}


// example fenstring;  "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
void Board::setup(const std::string &fenString) {
    // Split fen string into sections:
    std::vector<std::string> sections;
    const std::string d = " ";
    size_t p = 0;
    size_t dPos;
    while ((dPos = fenString.find(d, p)) != std::string::npos) {
        std::string token = fenString.substr(p, dPos - p);
        sections.push_back(token);
        p = dPos + d.length();
    }
    sections.push_back(fenString.substr(p));
    // sanity check:
    if (sections.size() != 6) {
        throw std::invalid_argument("invalid fen string: " + fenString);
    }

    // piece placement field:
    std::string piecePlacementField = sections[0];
    size_t x = 0;
    size_t y = 7;
    for (size_t i = 0; i < piecePlacementField.length(); i++) {
        char current = piecePlacementField[i];
        if (current == '/') {
            y -= 1;
            x = 0;
        } else if (std::isdigit(current)) {
            int digit = current - '0';
            x += digit;
        } else {
            setPiece(current, x, y);
        }
    }


    // Side to move
    std::string playerToMove = sections[1];
    if (playerToMove.length() != 1) {
        throw std::invalid_argument("Side to move: invalid side to move, not a single character" + fenString);
    }
    if (playerToMove != "w" && playerToMove != "b") {
        throw std::invalid_argument("Side to move: not a valid player side should be (w or b) " + fenString);
    }
    this->whiteTurn = playerToMove == "w";


    // Castling availability
    std::string castlingRights = sections[2];
    this->whiteCanCastleKingSide = false;
    this->whiteCanCastleQueenSide = false;
    this->blackCanCastleKingSide = false;
    this->blackCanCastleQueenSide = false;

    if (castlingRights != "-") {
        for (size_t i = 0; i < castlingRights.length(); i++) {
            char current = castlingRights[i];
            bool isWhite = std::isupper(current);
            switch (std::tolower(current)) {
                case 'q':
                    if (isWhite) {
                        this->whiteCanCastleQueenSide = true;
                    } else
                        this->blackCanCastleQueenSide = true;

                    break;
                case 'k':
                    if (isWhite) {
                        this->whiteCanCastleKingSide = true;
                    } else
                        this->blackCanCastleKingSide = true;
                    break;
                default:
                    throw std::invalid_argument("Castling availability: not valid argument");
            }
        }
    }

    // En passant target square
    std::string enPassant = sections[3];
    if (enPassant != "-") {
        int index = chessPosToindex(enPassant);
        this->enPassantSquare = index;
    } else {
        this->enPassantSquare = -1;
    }

    // Halfmove clock
    std::string halfMoveSection = sections[4];
    this -> halfMove = std::stoi(halfMoveSection);

    // Fullmove number
    std::string fullMoveSection = sections[5];
    this -> fullMoves = std::stoi(fullMoveSection);
}

void Board::setPiece(const char &piece, size_t &x, size_t &y) {
    bool isWhite = std::isupper(piece);

    switch (std::tolower(piece)) {
        case 'r':
            if (isWhite) {
                setBitBoard(this->whiteRooks, x, y);
            } else {
                setBitBoard(this->blackRooks, x, y);
            }
            break;
        case 'n':
            if (isWhite) {
                setBitBoard(this->whiteKnights, x, y);
            } else {
                setBitBoard(this->blackKnights, x, y);
            }
            break;
        case 'b':
            if (isWhite) {
                setBitBoard(this->whiteBishops, x, y);
            } else {
                setBitBoard(this->blackBishops, x, y);
            }
            break;
        case 'q':
            if (isWhite) {
                setBitBoard(this->whiteQueens, x, y);
            } else {
                setBitBoard(this->blackQueens, x, y);
            }
            break;
        case 'k':
            if (isWhite) {
                setBitBoard(this->whiteKings, x, y);
            } else {
                setBitBoard(this->blackKings, x, y);
            }
            break;
        case 'p':
            if (isWhite) {
                setBitBoard(this->whitePawns, x, y);
            } else {
                setBitBoard(this->blackPawns, x, y);
            }
            break;
        default:
            throw std::invalid_argument("invalid piece");
    }
}
