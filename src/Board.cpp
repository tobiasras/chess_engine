#include <iostream>
#include "Board.h"
#include <vector>

namespace {
    void setBitBoard(uint64_t &board, size_t index) {
        board |= 1ULL << index;
    }

    // chess pos e4
    size_t chessPosToindex(std::string chessPos) {
        const int x = chessPos[0] - 'a';
        const int y = chessPos[1] - '1';
        if (x > 7 || y > 7)
            throw std::out_of_range("Chess position out of bounds: " + chessPos);
        return y * 8 + x;
    }

    std::string pieceCharAt(
        uint64_t whitePawns, uint64_t blackPawns,
        uint64_t whiteKnights, uint64_t blackKnights,
        uint64_t whiteBishops, uint64_t blackBishops,
        uint64_t whiteRooks, uint64_t blackRooks,
        uint64_t whiteQueens, uint64_t blackQueens,
        uint64_t whiteKings, uint64_t blackKings,
        int index) {
        if ((whitePawns >> index) & 1ULL) return "P";
        if ((blackPawns >> index) & 1ULL) return "p";
        if ((whiteKnights >> index) & 1ULL) return "N";
        if ((blackKnights >> index) & 1ULL) return "n";
        if ((whiteBishops >> index) & 1ULL) return "B";
        if ((blackBishops >> index) & 1ULL) return "b";
        if ((whiteRooks >> index) & 1ULL) return "R";
        if ((blackRooks >> index) & 1ULL) return "r";
        if ((whiteQueens >> index) & 1ULL) return "Q";
        if ((blackQueens >> index) & 1ULL) return "q";
        if ((whiteKings >> index) & 1ULL) return "K";
        if ((blackKings >> index) & 1ULL) return "k";
        return "."; // empty square
    }
}


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
            size_t index = y * 8 + x;
            setPiece(current, index);
            x++;
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
        size_t index = chessPosToindex(enPassant);
        this->enPassantSquare = index;
    } else {
        this->enPassantSquare = -1;
    }

    // Halfmove clock
    std::string halfMoveSection = sections[4];
    this->halfMove = std::stoi(halfMoveSection);

    // Fullmove clock
    std::string fullMoveSection = sections[5];
    this->fullMoves = std::stoi(fullMoveSection);
}


void Board::setPiece(const char &piece, size_t index) {
    bool isWhite = std::isupper(piece);
    switch (std::tolower(piece)) {
        case 'r':
            if (isWhite) {
                setBitBoard(this->whiteRooks, index);
            } else {
                setBitBoard(this->blackRooks, index);
            }
            break;
        case 'n':
            if (isWhite) {
                setBitBoard(this->whiteKnights, index);
            } else {
                setBitBoard(this->blackKnights, index);
            }
            break;
        case 'b':
            if (isWhite) {
                setBitBoard(this->whiteBishops, index);
            } else {
                setBitBoard(this->blackBishops, index);
            }
            break;
        case 'q':
            if (isWhite) {
                setBitBoard(this->whiteQueens, index);
            } else {
                setBitBoard(this->blackQueens, index);
            }
            break;
        case 'k':
            if (isWhite) {
                setBitBoard(this->whiteKings, index);
            } else {
                setBitBoard(this->blackKings, index);
            }
            break;
        case 'p':
            if (isWhite) {
                setBitBoard(this->whitePawns, index);
            } else {
                setBitBoard(this->blackPawns, index);
            }
            break;
        default:
            throw std::invalid_argument("invalid piece");
    }
}



// todo
/*
 *add castling, movecounter, last capture
 */

// move: e3e5
void Board::makeMove(const std::string &move) {
    this->whiteTurn = !whiteTurn;



    size_t startPos = chessPosToindex(move.substr(0, 2));
    size_t endPos = chessPosToindex(move.substr(2, 2));
    char piece = getPieceFromIndex(startPos);
    uint64_t &board = getBoardFromPiece(piece);

    // check if it was a capture
    // here




    // very important that it is no called on empty square
    // remove piece from start
    board ^= (1ULL << startPos);
    if (move.length() == 4) {
        board |= (1ULL << endPos);
    } else if (move.length() == 5) {
        char pieceToPromote = move[4];
        if (this->whiteTurn) {
            pieceToPromote = std::toupper(pieceToPromote);
        }
        uint64_t &boardForPromotion = getBoardFromPiece(pieceToPromote);
        boardForPromotion |= (1ULL << endPos);
    } else {
        throw std::invalid_argument("invalid move");
    }
}


uint64_t &Board::getBoardFromPiece(const char &piece) {
    switch (piece) {
        case 'P': return whitePawns;
        case 'p': return blackPawns;
        case 'N': return whiteKnights;
        case 'n': return blackKnights;
        case 'B': return whiteBishops;
        case 'b': return blackBishops;
        case 'R': return whiteRooks;
        case 'r': return blackRooks;
        case 'Q': return whiteQueens;
        case 'q': return blackQueens;
        case 'K': return whiteKings;
        case 'k': return blackKings;
        default:
            throw std::invalid_argument("Invalid piece");
    }
}

char Board::getPieceFromIndex(size_t &index) {
    if ((whitePawns >> index) & 1ULL) return 'P';
    if ((blackPawns >> index) & 1ULL) return 'p';
    if ((whiteKnights >> index) & 1ULL) return 'N';
    if ((blackKnights >> index) & 1ULL) return 'n';
    if ((whiteBishops >> index) & 1ULL) return 'B';
    if ((blackBishops >> index) & 1ULL) return 'b';
    if ((whiteRooks >> index) & 1ULL) return 'R';
    if ((blackRooks >> index) & 1ULL) return 'r';
    if ((whiteQueens >> index) & 1ULL) return 'Q';
    if ((blackQueens >> index) & 1ULL) return 'q';
    if ((whiteKings >> index) & 1ULL) return 'K';
    if ((blackKings >> index) & 1ULL) return 'k';
}


// debug
void Board::boardToText() {
    std::cout << "Board state:\n";
    for (int rank = 7; rank >= 0; rank--) {
        std::cout << rank + 1 << " "; // print rank
        for (int file = 0; file < 8; file++) {
            int index = rank * 8 + file;
            std::cout << pieceCharAt(
                whitePawns, blackPawns,
                whiteKnights, blackKnights,
                whiteBishops, blackBishops,
                whiteRooks, blackRooks,
                whiteQueens, blackQueens,
                whiteKings, blackKings,
                index
            ) << " ";
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n"; // file letters
    std::cout << "Side to move: " << (whiteTurn ? "white" : "black") << "\n";
    std::cout << "Castling rights: "
            << (whiteCanCastleKingSide ? "K" : "")
            << (whiteCanCastleQueenSide ? "Q" : "")
            << (blackCanCastleKingSide ? "k" : "")
            << (blackCanCastleQueenSide ? "q" : "")
            << "\n";
    std::cout << "En passant square: ";
    if (enPassantSquare == -1) std::cout << "-";
    else std::cout << enPassantSquare;
    std::cout << "\n";
    std::cout << "Halfmove clock: " << halfMove << "\n";
    std::cout << "Fullmove number: " << fullMoves << "\n";
}
