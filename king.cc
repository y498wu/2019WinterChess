#include "king.h"  

King::~King(){LegalMoves.clear();}

King::King(Board *theBoard, bool White, Position Location): theBoard{theBoard},
															White{White},
															Location{Location},
															Protected{false},
															Pinned{nullptr},
															hasMoved{false},
															inCheck{false}{}

std::string King::checkType() const{
	return this->White ? "K" : "k";
}

bool King::isInCheck() const{
	return this->inCheck;	
}

bool King::isInCheckMate() const{
	return this->inCheckMate;		
}

void King::putInCheck(bool check){
	this->inCheck = check;
}

void King::putInCheckMate(bool check){
	this->inCheckMate = check;
}


void King::updateMoves(){
	
	vector<Position> possibleMoves;
	
	//step 1: move all possible legal moves into a temporary vector
	//legal moves for the King are all around it in a 3 x 3 square 
	//not including ofc its current location and out of bounds locations
	for(int y = this->Location.getY() - 1; y <= this->Location.getY() + 1; ++y){ 
		for(int x = this->Location.getX() - 1; x <= this->Location.getX() + 1; ++x){ 
			if(x >= 0 && x <= 7 && y >= 0 && y <= 7){				
				possibleMoves.emplace_back(new Position(x, y));						
			}		
		}		
	}
	
	//step 2: check if there are pieces occupying any of the possible locations
	
	int size = possibleMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(possibleMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);		
				possibleMoves.erase(possibleMoves.begin() + i);
				size = possibleMoves.size();
				i--;
			}
			else if(temp->isProtected()){ //this means that it is an enemy piece, check the protected field
				possibleMoves.erase(possibleMoves.begin() + i);
				size = possibleMoves.size();
				i--;					
			}		
		}		
	}
	
	// step 3: (special for the king): check if there are pieces attacking possible spots that king can move to 
	
	for(int y = 0; y <= 7; y++){
		for(int x = 0; x <= 7; x++){
			Position current(x, y);
			Pieces* temp = this->theBoard.atLocation(current);
		
			if(temp != nullptr){
				if((this->White && temp->isWhite() == false) || (this->White == false && temp->isWhite())){
					for(auto i = possibleMoves.begin(); i != possibleMoves.end(); ){
						if(temp->canMove(i)){
							i = possibleMoves.erase(i);
						}
						else{
							++i;
						}
					}
				}
			}
		}
	}
	// step 4: update LegalMoves
	
	this->LegalMoves.clear();
	
	for(auto i : possibleMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	possibleMoves.clear();
	
	if(LegalMoves.size() == 0 && this->inCheck){
		//might be checkmate
		
	}
}
