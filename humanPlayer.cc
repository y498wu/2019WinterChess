#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"
#include "humanPlayer.h"

HumanPlayer::HumanPlayer(bool playerIsWhite, Board* board) : 
playerIsWhite{playerIsWhite}, board{board}, playerScore{0} {}

void HumanPlayer::makeMove(Position start, Position end, string pieceType){
	if (start->isValid() && end->isValid()){
		cout << "Your input position is incorrect!" << endl;
		return;
	}
	board->makeMove(Position start, Position end, string pieceType);
}
