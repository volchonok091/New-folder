#pragma once
#include "board.h"
#include "aiplay.h"
#include <fstream>
using namespace std;

/*
	This class inherits the Board class, it adds features like functions to configure settings
	like changing the pieces, changing the amount of diagonals to in etc. It also provides an
	option to save the current play, along with the settings into a file called 'data.c4x'g
*/

class Implementation : public Board
{
private:
	fstream dataFile;//Saves instance and closes game
	fstream outputFile;//Outputs screen to a text file
	AiPlay a0;
	bool useAI;
public:
	//Constructor
	Implementation();

	//Methods
	void openInstance();//Reads from a file
	void configureSettings();
	void displaySettings();
	void play();
	char playHelper(bool player);
	void saveFile();//Writes to a file
	void outputScreen();

	//Get methods for Board
	int getheight() { return 12; }
	int getWidth() { return 10; }
	char getPlayer1() { return 'x'; }
	char getPlayer2() { return '*'; }
	char **getPlace() { return Board::getPlace(); }
	int getWin() { return 4; }
};