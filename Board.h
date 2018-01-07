/*
 * Board.h
 *
 *  Created on: Oct 29, 2017
 *      Author: avi simson
 */
#ifndef BOARD_H_
#define BOARD_H_
//matrix is the board status.
class Board {
//board is the matrix of the game, and size is matrix length and width.
private:
    int size;
    char **board;
// constructor function and print function.
public:
    Board(char p1, char p2);
    ~Board();
    void printBoard();
    int getSize();
    char** getBoard();
    void setBoard(int row, int col, char val);
};
#endif /* BOARD_H_ */