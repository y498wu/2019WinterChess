#include <vector>
#include <iostream>

#include "humanPlayer.h"
#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"

HumanPlayer::HumanPlayer(bool playerIsWhite, Board* board) : 
playerIsWhite{playerIsWhite}, board{board}, playerScore{0} {}

std::string HumanPlayer::makeMove(Position start, Position end, string pieceType){
	if (start->isValid() && end->isValid()){
		return "invalid input";
	}
	return board->makeMove(Position start, Position end, string pieceType);
}

void HumanPlayer::setScore(float i){
	playerScore = i;
}

float HumanPlayer::getScore() const{
	return playerScore;		
}
