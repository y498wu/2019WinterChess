#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"
#include "humanPlayer.h"

HumanPlayer::HumanPlayer(bool playerIsWhite, Board* board) : 
playerIsWhite{playerIsWhite}, board{board}, playerScore{0} {}

std::string HumanPlayer::makeMove(Position start, Position end, string pieceType){
	if (start->isValid() && end->isValid()){
		return "invalid input";
	}
	return board->makeMove(Position start, Position end, string pieceType);
}

void setScore(float i){
	playerScore = i;
}

float getScore() const{
	return playerScore;		
}
