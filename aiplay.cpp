#include "aiplay.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

AiPlay::~AiPlay()
{
	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < width; k++)
			{
				delete place[i][j][k];
			}
		}
	}

	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			delete place[i][j];
		}
	}

	for (int i = 0; i < depth; i++)
	{
		delete place[i];
	}

	delete place;
}

void AiPlay::setup(int inWidth, int inheight, char inPlayer1, char inPlayer2, char **inPlace, int inWin)
{
	width = inWidth;
	height = inheight;
	player1 = inPlayer1;
	player2 = inPlayer2;
	originalPlace = inPlace;
	win = inWin;
	/*
	Player 0 is the AI player
	player 1 is the user
	*/
	depth = 3;
	place = new char***[depth];
	for (int i = 0; i < depth; i++)
		place[i] = new char**[2];
	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			place[i][j] = new char*[width];
		}
	}
	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < width; k++)
			{
				place[i][j][k] = new char[height];
			}
		}
	}
	setupScore();
}

bool AiPlay::addPiece(int inPlace, int playerNum, char player, int position)
{
	for (int i = 0; i < height; i++)
	{
		if (place[position][playerNum][inPlace][i] == ' ')
		{
			place[position][playerNum][inPlace][i] = player;
			return true;
		}
	}

	return false;
}

int AiPlay::checkWin(char checker, int playerNum, int position)
{
	int count = 0;
	int grandCount = 0;
	int cutoff = 0;
	int winReturn;

	if (position == 0)
		winReturn = -1000000;
	else
		winReturn = 10;

	//Right-left diagonal check 
	for (int i = width - 1; i >= win - 1; i--)
	{
		for (int j = height - 1; j >= win - 1; j--)
		{
			if (place[position][playerNum][i][j] == checker)
			{
				grandCount--;
				for (int k = 0; k < win; k++)
				{
					if (place[position][playerNum][i - k][j - k] == checker)
					{
						count++;
						grandCount++;
					}
					else
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return winReturn;
			}
		}
	}

	//Left-Right diagonal check 
	for (int i = 0; i < width - win; i++)
	{
		for (int j = height - 1; j >= win - 1; j--)
		{
			if (place[position][playerNum][i][j] == checker)
			{
				grandCount--;
				for (int k = 0; k < win; k++)
				{
					if (place[position][playerNum][i + k][j - k] == checker)
					{
						count++;
						grandCount++;
					}
					else
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return winReturn;
			}
		}
	}

	//Left-Right horizontal check
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width - win; i++)
		{
			if (place[position][playerNum][i][j] == checker)
			{
				grandCount--;
				cutoff = 0;
				for (int k = 0; k < win; k++)
				{
					if (place[position][playerNum][i + k][j] == checker)
					{
						count++;
						grandCount++;
					}
					else if (count != win)
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return winReturn;
			}
			else
				cutoff++;

			if (cutoff == (width - win))
				goto end3;
		}


		for (int i = (width - win); i < width; i++)
		{
			if (place[position][playerNum][i][j] == checker)
			{
				for (int l = 0; l < (width - i); l++)
				{
					if (place[position][playerNum][i + l][j] == checker)
					{
						grandCount++;
					}
				}
			}
			else
				cutoff++;
		}

		if (cutoff == width)
			goto end3;

		cutoff = 0;
	}
	end3:

	//Up-Down Check
	for (int j = 0; j < height - win; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (place[position][playerNum][i][j] == checker)
			{
				grandCount--;
				cutoff = 0;
				for (int k = 0; k < win; k++)
				{
					if (place[position][playerNum][i][j + k] == checker)
					{
						count++;
						grandCount++;
					}
					else
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return winReturn;
			}
			else
				cutoff++;
			if (cutoff == width)
				goto end4;
		}
	}
	end4:
	return grandCount;
}

void AiPlay::setupScore()
{
	score = new long long*[2];
	for (int i = 0; i < 2; i++)
		score[i] = new long long[width];

	for (int i = 0; i < width; i++)
		score[1][i] = 0;
	for (int i = 0; i < width; i++)
		score[0][i] = i;

}

int AiPlay::aiPlay()
{
	bool success;
	int position = 0;
	long long max;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < height; k++)
				place[0][0][j][k] = originalPlace[j][k];
		}

		success = addPiece(i, 0, player2, 0);
		if (!success)
			continue;
		score[1][i] = checkWin(player2, 0, 0)*-1;

		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < height; k++)
				place[0][1][j][k] = place[0][0][j][k];
		}

		player1Move(0, i);
	}

	max = score[1][0];

	for (int i = 1; i < width; i++)
	{
		if (score[1][i] > max)
		{
			position = score[0][i];
			max = score[1][i];
		}
	}
	
	return position;
}

void AiPlay::makeMove(int currDepth, int currPosition)
{
	bool success;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < height; k++)
				place[currDepth][0][j][k] = place[currDepth - 1][1][j][k];
		}

		success = addPiece(i, 0, player2, currDepth);
		if (!success)
			continue;
		score[1][currPosition] = (checkWin(player1, 0, currDepth)*-1) + score[1][currPosition];
		player1Move(currDepth, currPosition);
	}
}

void AiPlay::player1Move(int currDepth, int currPosition)
{
	bool success;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < width; j++)
		{
			for (int k = 0; k < height; k++)
				place[currDepth][1][j][k] = place[currDepth][0][j][k];
		}

		success = addPiece(i, 1, player1, currDepth);
		if (!success)
			continue;

		score[1][currPosition] = ((checkWin(player1, 1, currDepth))*-1) + score[1][currPosition];

		if (currDepth < (depth - 1))
			makeMove(currDepth + 1, currPosition);
	}
}
