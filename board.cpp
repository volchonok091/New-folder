#include "board.h"
#include <iostream>
using namespace std;

void Board::printBoard()
{
	for (int j = height - 1; j > -1; j--)
	{
		cout << "|";
		for (int i = 0; i < width; i++)
		{
			cout << place[i][j];
			for (int k = 0; k < retNumDigits(i); k++)
				cout << " ";
		}
		cout << "|";
		cout << endl;
	}
	cout << " ";
	for (int i = 0; i < width; i++)
		cout << i << " ";
	cout << endl;
}

char Board::addPiece(int inPlace, char player)//Add a piece to the board and return if the player has won
{
	for (int i = 0; i < height; i++)
	{
		if (place[inPlace][i] == ' ')
		{
			place[inPlace][i] = player;
			if (checkWin(player))
			{
				///cout << "Win\n";
				///system("pause");
				return 'w';//Player has won

			}
			return 't';//Player has not won, but piece is successfully placed
		}
	}

	return 'f';
}

bool Board::checkWin(char checker)//Check to see if the player has won
{
	int count = 0;
	//Right-left diagonal check 
	for (int i = width - 1; i >= win - 1; i--)
	{
		for (int j = height - 1; j >= win - 1; j--)
		{
			if (place[i][j] == checker)
			{
				for (int k = 0; k < win; k++)
				{
					if (place[i - k][j - k] == checker)
						count++;
					else
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return true;
			}
			if (count == win)
				return true;
		}
	}

	//Left-Right diagonal check 
	for (int i = 0; i < width - win; i++)
	{
		for (int j = height - 1; j >= win - 1; j--)
		{
			if (place[i][j] == checker)
			{
				for (int k = 0; k < win; k++)
				{
					if (place[i + k][j - k] == checker)
						count++;
					else
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return true;
			}
			if (count == win)
				return true;
		}
	}

	//Left-Right horizontal check
	for (int i = 0; i < width - win; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (place[i][j] == checker)
			{
				for (int k = 0; k < win; k++)
				{
					if (place[i + k][j] == checker)
						count++;
					else if (count != win)
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return true;
			}
			if (count == win)
				return true;
		}
	}

	//Up-Down Check
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height - win; j++)
		{
			if (place[i][j] == checker)
			{
				for (int k = 0; k < win; k++)
				{
					if (place[i][j+k] == checker)
						count++;
					else
					{
						count = 0;
						break;
					}
				}
				if (count == win)
					return true;
			}
			if (count == win)
				return true;
		}
	}
	return false;
}

void Board::setArray(int inWidth, int inheight)
{
	for (int i = 0; i < width; i++)
		delete[] place[i];
	delete[] place;

	height = inheight;
	width = inWidth;

	place = new char*[inWidth];
	for (int i = 0; i < inWidth; i++)
		place[i] = new char[inheight];
	for (int i = 0; i < inheight; i++)
	{
		for (int j = 0; j <inWidth; j++)
			place[j][i] = ' ';
	}

}
