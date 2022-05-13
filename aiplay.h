#pragma once
#include <iostream>

class AiPlay
{
private:
	char ****place;
	long long **score;
	int depth;
	int height, width, win;
	char player1, player2;
	char **originalPlace;

	

	//Private Methods
	bool addPiece(int inPlace, int playerNum, char player, int position);
	int checkWin(char checker, int playerNum, int position);
	void setupScore();
	void makeMove(int currDepth, int currPosition);
	void player1Move(int currDepth, int currPosition);

	
public:
	//Public Methods
	void setup(int inWidth, int inheight, char inPlayer1, char inPlayer2, char **inPlace, int inWin);
	int aiPlay();

	//Constructor and destructor
	///AiPlay();
	~AiPlay();
};
