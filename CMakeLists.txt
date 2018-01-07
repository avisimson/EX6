cmake_minimum_required(VERSION 3.8)
project(untitled)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Player.cpp Player.h ReversiGame.h ReversiGame.cpp GameType.h Game.h Game.cpp Board.cpp Board.h)
add_executable(untitled ${SOURCE_FILES} main.cpp)