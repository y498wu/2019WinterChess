#include "king.h"  

King::~King(){LegalMoves.clear();}

std::string checkType() const{
	return "k";	
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
				temp->setProtected(true); //NEEED TO ADD THIS IN PROPOSE AS AN IDEA				
				possibleMoves.erase(possibleMoves.begin() + i);
				size = possibleMoves.size();
				i--;
			}
			else{ //this means that it is an enemy piece, check the protected field
				
			}		
		}		
	}
	
	// step 3: (special for the king): check if there are pieces attacking  
	
	
	// step 4: update LegalMoves
	
	this->LegalMoves.clear();
	
	for(auto i : possibleMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	possibleMoves.clear();
}
