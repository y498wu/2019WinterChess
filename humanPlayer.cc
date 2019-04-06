#include <vector>
#include <iostream>

#include "humanPlayer.h"
using namespace std;

HumanPlayer::HumanPlayer(bool playerIsWhite, Board* board) : 
board{board}, playerIsWhite{playerIsWhite}, playerScore{0} {}

std::string HumanPlayer::makeMove(Position start, Position end, string pieceType){
	if (start.isValid() == false && end.isValid() == false){
		return "invalid input";
	}
	return board->makeMove(start, end, pieceType);
}

void HumanPlayer::setScore(float i){
	playerScore = i;
}

float HumanPlayer::getScore() const{
	return playerScore;		
}
