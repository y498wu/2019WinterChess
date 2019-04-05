#include "computerPlayer.h"

ComputerPlayer::ComputerPlayer(bool playerIsWhite, Board* board, int difficulty): playerIsWhite{playerIsWhite}, 
																				  board{board}, 
																			      difficulty{difficulty},
																			      playerScore{0}{}

std::string ComputerPlayer::move(){
	
	if(difficulty == 1){
		
		King *my_king = this->playerIsWhite ? board->WhiteKing() : board->BlackKing();
				
		if(my_king->isInCheck()){//if king is under attack
			
			//step 1: check if the king can move away

			Vector<Position> possibleKingMoves = my_king->getLegalMoves();	
			
			if(possibleKingMoves.size() > 0){
				std::random_shuffle(possibleKingMoves.begin(), possibleKingMoves.end());
				Position start = my_king->getPos();
				Position end = possibleKingMoves.at(0);
				return board->makeMove(start, end, "");
				
			}else{
				//step 2: check if you can capture attacking piece
				Position attack_pos = my_king->returnPieceCheck()->getPos();
				
				for(int y = 0; y <= 7; y++){
					for(int x = 0; x <= 7; x++){
						Position current(x, y);
						Pieces* temp = this->board->atLocation(current);
					
						if(temp != nullptr){// if an ally piece can capture the attacking pos, capture it
							if((this->playerIsWhite && temp->isWhite()) || 
							(this->playerIsWhite == false && temp->isWhite() == false)){
								if(temp->canMove(attack_pos)){
									Position start = temp->getPos();
									Position end = possibleKingMoves.at(0);
									std::string queen = this->playerIsWhite() ? "Q" : "q";
									return board->makeMove(start, end, queen);
									
								}
							}
						}
					}
				}
				
				//step 3: check if a piece can block the enemy attack
				
				
			}
			
		}
		else{// if you're not in check
			Vector<Pieces*> movablePieces;
				
			//step 1: store pointers to all the ally pieces that can move in a vector
			for(int y = 0; y <= 7; y++){
				for(int x = 0; x <= 7; x++){
					Position current(x, y);
					Pieces* temp = this->board->atLocation(current);
		
					if(temp != nullptr){
						if((this->playerIsWhite && temp->isWhite()) || (this->playerIsWhite == false && temp->isWhite() == false)){
							if(temp->availableMoveCount() > 0){
								movablePieces.emplace_back(temp); 				
							}											
						}
					}				
				}			
			}		
		
			//step 2: pick a movable piece at random and then pick one of its possible moves
		
			std::random_shuffle(movablePieces.begin(), movablePieces.end());
		
			Piece *selectedPiece = movablePieces.at(0);
			Position start = selectedPiece->getPos();
		
			Vector<Position> possibleMoves = selectedPiece->getLegalMoves();
		
			//step 3: execute a possible legal move from the selected piece
		
			std::random_shuffle(possibleMoves.begin(), possibleMoves.end());
			Position end = possibleMoves.at(0);
			
			std::string queen = this->playerIsWhite() ? "Q" : "q";
			return board->makeMove(start, end, queen);
		}
		
	}
	else if(difficulty == 2){
		
		
		
		
	}
	
	
	
}

void setScore(float i){
	playerScore = i;
}

float getScore() const{
	return playerScore;		
}
