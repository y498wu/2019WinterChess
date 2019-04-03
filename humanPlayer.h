#ifdef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"

class HumanPlayer{
	// a pointer to the board the player is on
	Board* board;
	bool playerIsWhite;

public:
	int playerScore;

	// constructor
	HumanPlayer(bool playerIsWhite, Board* board);

	void makeMove(Position start, Position end, string pieceType);
}

#endif