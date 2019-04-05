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
	float playerScore;

public:	

	// constructor
	HumanPlayer(bool playerIsWhite, Board* board);

	std::string makeMove(Position start, Position end, string pieceType);
	
	void setScore(float i);
	float getScore() const;
};

#endif