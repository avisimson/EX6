/*
 * Game.h
 *
 *  Created on: Nov 05, 2017
 *      Author: avi simson
 */
#ifndef REVERSI_GAME_H
#define REVERSI_GAME_H
#include "Board.h"
#include "ReversiGame.h"
#include "GameType.h"
class Game {
    //class has game type variable to be able to run all
    // games that implement GameType.
    private:
        GameType* game;
    public:
        Game(GameType* game1);
        ~Game();
        void Run();
};
#endif //REVERSI_GAME_H