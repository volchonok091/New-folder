#include "implementation.h"

/*
	This program is connect 4, like the real board game, it is a two player game, the aim of the game
	is for one of the players to get four pieces in a row, be it sideways, upwards, or diagonal, this
	can be changed to three, five, six etc in a row as well.

	The default dimensions for the board is 10x12, this can be changed in the settings. Anything
	changed in the settings is saved in the save file if the game is ended without a winner.
*/

//NOTE: This program uses ANSI escape sequences

int main()
{
	Implementation b0;
	b0.play();
	getchar();
	return 0;
}