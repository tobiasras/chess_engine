//
// Created by tobia on 08/01/2026.
//

#ifndef CHESS_ENGINE_UCI_H
#define CHESS_ENGINE_UCI_H

#include <string>
#include <fstream>
#include <vector>

#include "Board.h"
#include "Engine.h"

class UCI {

public:
     explicit UCI(const std::string& debugFilename);
     void start();

private:
     std::ofstream logFile;
     std::string debugFilename;

     Board board;
     Engine engine;

     void handleCommand(const std::string& command);
     void handleCommandUCI();
     void handleCommandPosition(std::vector<std::string> &tokens);
     void handleCommandGo(std::vector<std::string> &tokens);

     void log(const std::string &who, const std::string &msg);
     void answer(const std::string& response);
};




#endif //CHESS_ENGINE_UCI_H