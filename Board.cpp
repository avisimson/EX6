/*
 * Board.cpp
 *
 *  Created on: Oct 29, 2017
 *      Author: avi simson
 */
#include <iostream>
#include "Board.h"
using namespace std;
// constructor. put initial board status on matrix.
//parameters-p1, p2 are player 1 and 2 names.
Board :: Board(char p1, char p2) {
    cout << "Enter board size." << endl;
    cin >> size;
    // row and col 0 are for the board numbers.
    size = size + 1;
    // memory allocation for board matrix.
    board = new char*[size];
    int i;
    for (i = 0; i < size; i++) {
        board[i] = new char[size];
    }
    //put spaces in all matrix values.
    for (i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';
        }
    }
    //writing the col and row numbers in the matrix.
    int num = 0;
    for (i = 1; i < size; i++) {
        board[0][i] = '0' + i % 10;
        board[i][0] = '0' + i % 10;
    }
    //initialize placings for players in matrix.
    board[size / 2][size / 2] = p1;
    board[size / 2 + 1][size / 2 + 1] = p1;
    board[size / 2][size / 2 + 1] = p2;
    board[size / 2 + 1][size / 2] = p2;
}
//destructor for board-delete metrix from memory heap.
Board :: ~Board() {
    for (int i = 0; i < size; i++) {
        delete board[i];
    }
    delete board;
}
// function prints board on output screen.
void Board :: printBoard() {
    int j;
    for (int i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            cout << board[i][j];
            cout << " | ";
        }
        cout << "" <<endl;
        for (j = 0; j < size; j++) {
            cout << "----";
        }
        cout << "" << endl;
    }
}
//function returns the matrix size without the numbers row and column.
int Board :: getSize() {
    return size - 1;
}
//function returns matrix of the game.
char** Board :: getBoard() {
    return board;
}
//parameters: row, col are numbers of row and column in matrix,
// val is the value we put in.
//function changes a value inside matrix according to row and column.
void Board :: setBoard(int row, int col, char val) {
    board[row][col] = val;
}