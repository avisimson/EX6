#AviSimson205789100
a.out: Board.o main.o Game.o Player.o ReversiGame.o
	g++ main.o Board.o Game.o Player.o ReversiGame.o

Board.o: Board.cpp Board.h
	g++ -c Board.cpp

Game.o: Game.cpp Game.h Board.h ReversiGame.h GameType.h
	g++ -c Game.cpp

main.o: main.cpp Game.h
	g++ -c main.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp

ReversiGame.o: ReversiGame.cpp ReversiGame.h Board.h Player.h GameType.h
	g++ -c ReversiGame.cpp
