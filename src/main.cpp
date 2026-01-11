#include <iostream>

#include "UCI.h"

#ifdef _WIN32
#include <windows.h>
#endif


int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    UCI uci = UCI("debug.txt");
    uci.start();
    return 0;
}
