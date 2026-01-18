

cmake_minimum_required(VERSION 3.10)
project(chess_engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(
        chess_engine
        src/main.cpp
        src/Board.cpp
        src/UCI.cpp
        include/Engine.h
        src/Engine.cpp
        include/Move.h
        src/Move.cpp
        include/Const.h
)

# Add the include folder for headers
# CLion will use this for indexing
target_include_directories(chess_engine
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)