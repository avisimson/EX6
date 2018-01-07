#include <iostream>
#include "Game.h"
using namespace std;
//program creates reversi game board and prints it as output.
int main() {
    GameType* reversi = new ReversiGame('X', 'O');
    Game* game = new Game(reversi);
    game->Run();
    delete game;
}