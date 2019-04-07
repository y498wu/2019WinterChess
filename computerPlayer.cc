#include "computerPlayer.h"
#include <algorithm>
#include <iostream>

using namespace std;

ComputerPlayer::ComputerPlayer(bool playerIsWhite, Board* board, int difficulty): board{board}, 
																				  playerIsWhite{playerIsWhite}, 																				  
																			      difficulty{difficulty},
																			      playerScore{0}{}

string ComputerPlayer::move(){
	
	if(difficulty == 1){
		
		King *my_king = this->playerIsWhite ? board->WhiteKing() : board->BlackKing();
				
		if(my_king->isInCheck()){//if king is under attack
			
			//step 1: check if the king can move away

			vector<Position> possibleKingMoves = my_king->getLegalMoves();	
			Position attack_pos = my_king->returnPieceCheck()->getPos();
		
			if(possibleKingMoves.size() > 0){
				random_shuffle(possibleKingMoves.begin(), possibleKingMoves.end());
				Position start = my_king->getPos();
				Position end = possibleKingMoves.at(0);
				cout << "Moving: " << start.getX() << ", " << start.getY() << endl;
				cout << "To: " << end.getX() << ", " << end.getY() << endl; 
				return board->makeMove(start, end, "");
				
			}else{
				//step 2: check if you can capture attacking piece
				
				for(int y = 0; y <= 7; y++){
					for(int x = 0; x <= 7; x++){
						Position current(x, y);
						Pieces* temp = this->board->atLocation(current);
					
						if(temp != nullptr){// if an ally piece can capture the attacking pos, capture it
							if((this->playerIsWhite && temp->isWhite()) || 
							(this->playerIsWhite == false && temp->isWhite() == false)){
								if(temp->canAttack(attack_pos)){
		
									Position start = temp->getPos();
									Position end = attack_pos;
									string queen = this->playerIsWhite ? "Q" : "q";
									cout << "Moving: " << start.getX() << ", " << start.getY() << endl;
									cout << "To: " << end.getX() << ", " << end.getY() << endl; 
									return board->makeMove(start, end, queen);
									
								}
							}
						}
					}
				}
				
				//step 3: check if a piece can block the enemy attack
		
				vector<Position> preventAttack;
				Position tempDiff(attack_pos.getX() - my_king->getPos().getX(), attack_pos.getY() - my_king->getPos().getY());
				
				int absolute_x = (tempDiff.getX() > 0) ? tempDiff.getX() : -1*tempDiff.getX(); 
				int absolute_y = (tempDiff.getY() > 0) ? tempDiff.getY() : -1*tempDiff.getY(); 
				
				if(tempDiff.getY() == 0){//attacking piece has the same Y
					if(tempDiff.getX() > 1){		
						for(int start = my_king->getPos().getX() + 1; start < attack_pos.getX(); ++start){
							Position temp( start, attack_pos.getY());
							preventAttack.emplace_back(temp);
						}
					}
					else if(tempDiff.getX() < -1){
						for(int start = my_king->getPos().getX() - 1; start > attack_pos.getX(); --start){
							Position temp( start, attack_pos.getY());
							preventAttack.emplace_back(temp);
						}						
					}
				}
				else if(tempDiff.getX() == 0){//attacking piece has the same X
					if(tempDiff.getY() > 1){		
						for(int start = my_king->getPos().getY() + 1; start < attack_pos.getY(); ++start){
							Position temp(attack_pos.getX(), start);
							preventAttack.emplace_back(temp);
						}
					}
					else if(tempDiff.getY() < -1){
						for(int start = my_king->getPos().getY() - 1; start > attack_pos.getY(); --start){
							Position temp(attack_pos.getX(), start);
							preventAttack.emplace_back(temp);
						}						
					}					
				}
				else if(absolute_x == absolute_y){//attacking piece is diagonal
					if(tempDiff.getY() > 1 && tempDiff.getX() > 1){
						
						int y = my_king->getPos().getY();
	
						for(int x = my_king->getPos().getX() + 1; x < attack_pos.getX() ; ++x){ 
							y++;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
					else if(tempDiff.getY() > 1 && tempDiff.getX() < -1){
						
						int y = my_king->getPos().getY();
	
						for(int x = my_king->getPos().getX() - 1; x > attack_pos.getX() ; --x){ 
							y++;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
					else if(tempDiff.getY() < -1 && tempDiff.getX() > 1){
						
						int y = my_king->getPos().getY();
	
						for(int x = my_king->getPos().getX() + 1; x < attack_pos.getX() ; ++x){ 
							y--;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
					else if(tempDiff.getY() < -1 && tempDiff.getX() < -1){
						
						int y = my_king->getPos().getY();
	
						for(int x = my_king->getPos().getX() - 1; x > attack_pos.getX() ; --x){ 
							y--;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
				}		
									
				for(int y = 0; y <= 7; y++){
					for(int x = 0; x <= 7; x++){
						Position current(x, y);
						Pieces* temp = this->board->atLocation(current);
						if(temp != nullptr){
							if((my_king->isWhite() && temp->isWhite()) || (my_king->isWhite() == false && temp->isWhite() == false)){
								for(auto i : preventAttack){// if an ally piece can move to a possible position in vector
									if(temp->canMove(i)){
										Position start = temp->getPos();
										Position end = i;
										string queen = this->playerIsWhite ? "Q" : "q";
										cout << "Moving: " << start.getX() << ", " << start.getY() << endl;
										cout << "To: " << end.getX() << ", " << end.getY() << endl; 
										return board->makeMove(start, end, queen);
									}
								}
							}
						}
					}					
				}		
					
				
			}
			
		}
		else{// if you're not in check
			vector<Pieces*> movablePieces;
				
			//step 1: store pointers to all the ally pieces that can move in a vector
			for(int y = 0; y <= 7; y++){
				for(int x = 0; x <= 7; x++){
					Position current(x, y);
					Pieces* temp = this->board->atLocation(current);
		
					if(temp != nullptr){
						if((this->playerIsWhite && temp->isWhite()) || (this->playerIsWhite == false && temp->isWhite() == false)){
							if(temp->getMoveCount() > 0){
								movablePieces.emplace_back(temp); 				
							}											
						}
					}				
				}			
			}		
		
			//step 2: pick a movable piece at random and then pick one of its possible moves
		
			random_shuffle(movablePieces.begin(), movablePieces.end());
		
			Pieces *selectedPiece = movablePieces.at(0);
			Position start = selectedPiece->getPos();
		
			vector<Position> possibleMoves = selectedPiece->getLegalMoves();
		
			//step 3: execute a possible legal move from the selected piece
		
			random_shuffle(possibleMoves.begin(), possibleMoves.end());
			Position end = possibleMoves.at(0);
			
			string queen = this->playerIsWhite ? "Q" : "q";
			cout << "Moving: " << start.getX() << ", " << start.getY() << endl;
			cout << "To: " << end.getX() << ", " << end.getY() << endl; 
			return board->makeMove(start, end, queen);
		}
		
	}
	else if(difficulty == 2){
		
		
		
		return "diff 2";
	}
	
	return "not diff 1";
}

void ComputerPlayer::setScore(float i){
	playerScore = i;
}

float ComputerPlayer::getScore() const{
	return playerScore;		
}
