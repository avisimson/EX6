/*
 * ReversiGame.h
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson
 */
#ifndef REVERSI_REVERSIGAME_H
#define REVERSI_REVERSIGAME_H
#include "Board.h"
#include "Player.h"
#include "GameType.h"
class ReversiGame: public GameType {
    //class has a board, space left in board, matrix of x,y of
    // possible moves and 2 players.
private:
    Board* board;
    Player* player1;
    Player* player2;
    int space;
    int** possiblePoints;
public:
    ReversiGame(char p1, char p2);
    ~ReversiGame();
    void playGame();
    bool playOneTurn(Player* player);
    void scoreGame();
    void checkPossibleMoves(Player* player);
    bool checkUp(Player* player, int i, int j, bool flip);
    bool checkDown(Player* player, int i, int j, bool flip);
    bool checkLeft(Player* player, int i, int j, bool flip);
    bool checkRight(Player* player, int i, int j, bool flip);
    bool checkUpLeft(Player* player, int i, int j, bool flip);
    bool checkUpRight(Player* player, int i, int j, bool flip);
    bool checkDownLeft(Player* player, int i, int j, bool flip);
    bool checkDownRight(Player* player, int i, int j, bool flip);
};
#endif //REVERSI_REVERSIGAME_H
