#include "UCI.h"

#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>


UCI::UCI(const std::string &debugFilename) : logFile(debugFilename, std::ios::out | std::ios::trunc),
                                             debugFilename(debugFilename) {
}

void UCI::start() {
    // clear log file
    std::string command;
    while (std::getline(std::cin, command)) {
        log("GUI", command);
        if (command == "quit") {
            break;
        }
        handleCommand(command);
    }
}

void UCI::handleCommand(const std::string &command) {
    std::vector<std::string> tokens;

    const std::string delim = " ";
    size_t pos = 0;
    size_t delimPos;
    while ((delimPos = command.find(delim, pos)) != std::string::npos) {
        tokens.push_back(command.substr(pos, delimPos - pos));
        pos = delimPos + delim.size();
    }
    tokens.push_back(command.substr(pos));

    if (tokens[0] == "uci") {
        handleCommandUCI();
    } else if (tokens[0] == "isready") {
        answer("readyok");
    } else if (tokens[0] == "ucinewgame") {
        // this command does not need a response
    } else if (tokens[0] == "position") {
        handleCommandPosition(tokens);
    } else if (tokens[0] == "go") {
        handleCommandGo(tokens);
    } else {
        answer("invalid command");
    }
}

void UCI::handleCommandGo(std::vector<std::string> &tokens) {
    answer("bestmove e2e4 ponder e7e5");
}


void UCI::handleCommandPosition(std::vector<std::string> &tokens) {

    if (tokens[1] == "startpos") {
        const std::string fenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"; // default chess pos
        board.setup(fenString);
        // if moves then perform them
    } else if (tokens[1] == "fen") {
        std::string fenString;
        // start with token 2, since 0, is pos, 1 is fen then the actual string starts:
        for (size_t i = 2; i < tokens.size(); i++) {
            fenString += tokens[i] + " ";
        }
        fenString.pop_back(); // removes last ""
        board.setup(fenString);
    }

    // makes moves
    for (size_t i = 2; i < tokens.size(); i++) {
        if (tokens[i] == "moves") {
            for (size_t j = i + 1; j < tokens.size(); j++) {
                this->board.makeMove(tokens[j]);
            }
            break;
        }
    }

    // for debug
    board.boardToText();
}


void UCI::handleCommandUCI() {
    answer("id name chess");
    answer("id author Tobias Juul Rasmussen");
    answer("uciok");
}


void UCI::log(const std::string &who, const std::string &msg) {
    if (logFile.is_open()) {
        logFile << std::left
                << std::setw(12) << ("[" + who + "]")
                << msg
                << '\n';
        logFile.flush();
    }
}

void UCI::answer(const std::string &response) {
    log("ENGINE", response);
    std::cout << response << std::endl;
}
