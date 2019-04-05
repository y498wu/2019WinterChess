#ifdef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H

#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"

class ComputerPlayer{

	Board* board;
	bool playerIsWhite;
	int difficulty;
	float playerScore;
	

public:

	ComputerPlayer(bool playerIsWhite, Board* board, int difficulty);
	std::string move();
	
	void setScore(float i);
	float getScore() const;
};


#endif
