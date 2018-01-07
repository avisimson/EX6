/*
 * Player.cpp
 *
 *  Created on: Nov 10, 2017
 *      Author: avi simson
 */
#include <iostream>
#include "Player.h"
using namespace std;
//constructor-gets name and type and initializing player with them.
Player :: Player(char name1, char type1) {
    name = name1;
    type = type1;
}
// destructor-remove player from heap.
Player :: ~Player() {};
//function returns players name(usually X or O.
char Player :: getName() {
    return name;
}
//function returns player type-'C' or 'H',
char Player ::getType() {
    return type;
}