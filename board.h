#pragma once

/*
	This class provides the basic functions for the connect4 such as the 2d array to hold all of the values,
	the functions to print out the board and check if there is a winner. It doesn't actually set up the board
	and a seperate class is needed to set up the dimensions, what is required to win (4 in a row, 5 in a row
	etc) and what characters are used for player 1 and 2.
*/

class Board
{
private:
	char **place; //For a 2d array
	int height, width;
	char player1, player2;
	int win;
	///int retNumDigits(int in) { int nums = 0; do { in = in / 10; nums++; } while (in != 0); return nums; }
public:
	//Constructor & Destructor (Main constructor done in Implementation class)
	Board() {} 
	~Board() { for (int i = 0; i < width; i++)delete[] place[i]; delete[] place; }

	//Methods
	void printBoard();
	char addPiece(int inPlace, char player);
	bool checkWin(char checker);
	void setArray(int inWidth, int inheight);

	int retNumDigits(int in) { int nums = 0; do { in = in / 10; nums++; } while (in != 0); return nums; }

	//Get methods
	int getheight() { return height; }
	int getWidth() { return width; }
	char getPlayer1() { return player1; }
	char getPlayer2() { return player2; }
	char **getPlace() { return place; }
	int getWin() { return win; }

	//Set methods
	void setPlayers(char p1, char p2) { player1 = p1; player2 = p2; }
	void setWin(int inWin) { win = inWin; }
	void setPlace(char input, int x, int y) { place[x][y] = input; }
	void setWidth(int input) { width = input; }
	void setheight(int input) { height = input; }
};