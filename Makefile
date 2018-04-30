make all:
	tictactoe

tictactoe:
	g++ -g -Wall -std=c++11 tictactoe.cpp -o tictactoe

clean :
	rm tictactoe