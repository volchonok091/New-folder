#include "implementation.h"
#include "aiplay.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Implementation::Implementation()
{
	//Default parameters for board
	Board::setArray(10, 12);
	Board::setWin(4);
	Board::Board::setPlayers('x', '*');
	useAI = true;

	//Default parameters 
	openInstance();
	if(useAI)
		a0.setup(getWidth(), getheight(), getPlayer1(), getPlayer2(), getPlace(), getWin());
	cout << "\e[1;1H\e[2J";
	cout << "To end and save the current game, type in -1, to output the current board to a text file, type -2\n";
}

void Implementation::openInstance()
{
	char input;
	int inInt;
	char deadCharacter;
	char player1, player2, temp;
	int inWin, inWidth, inheight;
	bool inUseAI;
	do
	{
		cout << "\e[1;1H\e[2J";
		reInput:
			cout << "Type new to open 'n' game or 'p' for previous instance: ";
			cin >> input;
		cout << "\e[1;1H\e[2J";
	} while (input != 'n' && input != 'p');
	if (input == 'n')
	{
		dataFile.open("data.c4x", ios::in | ios::out | ios::trunc);
		dataFile.close();
		cout << "Enter 0 to enter settings, enter 1 to procede to game: ";
		cin >> inInt;
		if (inInt == 0)
			configureSettings();
	}
	else if (input == 'p')
	{
		dataFile.open("data.c4x", ios::in);
		if (!dataFile)
		{	
			cout << "Error in finding data file, select 'n' to create new file\n";
			goto reInput;
		}
		dataFile >> deadCharacter >> inWidth >> inheight >> inWin >> player1 >> player2 >> inUseAI;
		if (!dataFile.eof())
		{
			if ((inWidth != Board::getWidth()) || (inheight != Board::getheight()))
				Board::setArray(inWidth, inheight);
			Board::setPlayers(player1, player2);
			Board::setWin(inWin);
			Implementation::useAI = inUseAI;
			for (int i = 0; i < Board::getheight(); i++)
			{
				for (int j = 0; j < Board::getWidth(); j++)
				{
					dataFile >> temp;
					if (temp != deadCharacter)
						Board::setPlace(temp, j, i);
					else
						Board::setPlace(' ', j, i);
				}
			}
		}
		dataFile.close();
	}
	else
		cout << "ERROR";
}

void Implementation::configureSettings()
{
	displaySettings();
	int input = -1;
	char charInput;
	int intInput;
	while (input != 6)
	{
		cout << "To change number of rows required to win, type 0\nTo change Player 1, type 1\n";
		cout << "To change Player 2, type 2\nTo change width, type 3\nTo change height, type 4\n";
		cout << "To toggle AI player, type 5\nTo exit type 6\nInput: ";
		cin >> input;
		if (input == 0)
		{
			cout << "Enter number of rows required to win: ";
			cin >> intInput;
			Board::setWin(intInput);
		}
		else if (input == 1)
		{
			redoP1:
			cout << "Enter player 1 character: ";
			cin >> charInput;
			if (charInput == Board::getPlayer2())
			{
				cout << "Player 1 must have a differant value to player 2\n";
				goto redoP1;
			}
			Board::setPlayers(charInput, Board::getPlayer2());
		}
		else if (input == 2)
		{
			redoP2:
			cout << "Enter player 2 character: ";
			cin >> charInput;
			if (charInput == Board::getPlayer1())
			{
				cout << "Player 1 must have a differant value to player 2\n";
				goto redoP2;
			}
			Board::setPlayers(Board::getPlayer1(), charInput);
		}
		else if (input == 3)
		{
			cout << "Enter width: ";
			cin >> intInput;
			Board::setArray(intInput, Board::getheight());
		}
		else if (input == 4)
		{
			cout << "Enter height: ";
			cin >> intInput;
			Board::setArray(Board::getWidth(), intInput);
		}
		else if (input == 5)
		{
			if (useAI)
				useAI = false;
			else
				useAI = true;
		}

		else if ((input < 0) || (input > 6))
			cout << "Enter a valid input";
		displaySettings();
	}
}

void Implementation::displaySettings()
{
	cout << "\e[1;1H\e[2J";
	cout << "Number of rows required for win: " << Board::getWin() << endl;
	cout << "Player 1 piece: " << Board::getPlayer1() << endl;
	cout << "Player 2 piece: " << Board::getPlayer2() << endl;
	cout << "Width of board: " << Board::getWidth() << endl;
	cout << "height of board: " << Board::getheight() << endl;
	if (useAI)
		cout << "AI player is enabled\n\n";
	else
		cout << "AI player is not enabled\n\n";
}

void Implementation::play()
{
	char returnValue;
	bool message;
	for (;;)
	{
		//Player 1
	p1:
		Board::printBoard();
		returnValue = playHelper(false);
		if (returnValue == 'e')
			break;
		else if (returnValue == 'w')
		{
			message = false;
			break;
		}
		else if (returnValue == 'f')
			goto p1;
		cout << "\e[1;1H\e[2J";
		//Player 2
	p2:
		Board::printBoard();
		if (!useAI)
			returnValue = playHelper(true);
		else
			returnValue = (Board::addPiece(a0.AiPlay::aiPlay(), getPlayer2()));

		if (returnValue == 'e')
			break;
		else if (returnValue == 'w')
		{
			message = true;
			break;
		}
		else if (returnValue == 'f')
			goto p2;
		cout << "\e[1;1H\e[2J";
	}
	cout << "\e[1;1H\e[2J";
	Board::printBoard();

	if (returnValue == 'e')
		saveFile();
	else if (returnValue == 'w')
	{
		if (message&&useAI)
			cout << "The AI has won\n";
		else if (message)
			cout << "Player " << getPlayer2() << " has won\n";
		else
			cout << "Player " << getPlayer1() << " has won\n";
	}
}

char Implementation::playHelper(bool player)
{
	int place;
	char playerChar;
	if (!player)
		playerChar = getPlayer1();
	else
		playerChar = getPlayer2();
start:
	cout << "Enter place for " << playerChar << ": ";
	cin >> place;
	if ((place < -2) || (place >= getWidth()))
	{
		cout << "Enter a valid place\n";
		goto start;
	}
	else if (place == -2)
	{
		outputScreen();
		goto start;
	}
	else if (place == -1)
		return 'e';
	else
		return(Board::addPiece(place, playerChar));
}

void Implementation::saveFile()
{
	char deadCharacter = 'x';
	if ((Board::getPlayer1() == deadCharacter) || (Board::getPlayer2() == deadCharacter))
	{
		deadCharacter = 'y';
		if ((Board::getPlayer1() == deadCharacter) || (Board::getPlayer2() == deadCharacter))
			deadCharacter = 'z';
	}
	dataFile.open("data.c4x", ios::out | ios::trunc);
	dataFile << deadCharacter << " ";
	dataFile << Board::getWidth() << " " << Board::getheight() << " " << Board::getWin() << " ";
	dataFile << Board::getPlayer1() << " " << Board::getPlayer2() << " " << Implementation::useAI << endl;
	for (int i = 0; i < Board::getheight(); i++)
	{
		for (int j = 0; j < Board::getWidth(); j++)
		{
			if (Board::getPlace()[j][i] != ' ')
				dataFile << Board::getPlace()[j][i];
			else
				dataFile << deadCharacter;
			dataFile << " ";
		}
		dataFile << endl;
	}
}

void Implementation::outputScreen()
{
	outputFile.open("output.txt", ios::out | ios::trunc);

	for (int j = Board::getheight() - 1; j > -1; j--)
	{
		outputFile << "|";
		for (int i = 0; i < Board::getWidth(); i++)
		{
			outputFile << Board::getPlace()[i][j];
			for (int k = 0; k < Board::retNumDigits(i); k++)
				outputFile << " ";
		}
		outputFile << "|";
		outputFile << endl;
	}
	outputFile << " ";
	for (int i = 0; i < Board::getWidth(); i++)
		outputFile << i << " ";
	outputFile << endl;
	
	outputFile.close();
}