#include "rook.h"  

Rook::~Rook(){LegalMoves.clear();}

std::string checkType() const{
	return "r";	
}

void Rook::updateMoves(){
	
	vector<Position> leftMoves;
	vector<Position> rightMoves;
	vector<Position> upMoves;
	vector<Position> downMoves;
	
	//step 1: move all possible legal moves into 4 temporary vector, one for each direction,
	//	make sure to have it in ordered fashion
	
	for(int x = this->Location.getX() - 1; x >= 0; --x){ 
		leftMoves.emplace_back(new Position(x, this->Location.getY()));
	}
	
	for(int x = this->Location.getX() + 1; x <= 7; ++x){ 
		rightMoves.emplace_back(new Position(x, this->Location.getY()));
	}
	
	for(int y = this->Location.getY() - 1; y >= 0; --y){ 
		upMoves.emplace_back(new Position(this->Location.getX(), y));
	}
	for(int y = this->Location.getY() + 1; y <= 7; ++y){ 
		downMoves.emplace_back(new Position(this->Location.getX(), y));
	}
	
	//step 2: check if there are pieces occupying any of the possible locations
	
	int size = leftMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(leftMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				leftMoves.erase(leftMoves.begin() + i, leftMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position
				leftMoves.erase(leftMoves.begin() + i + 1, leftMoves.end());
			}

			break;		
		}		
	}
	
	size = rightMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(rightMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);				
				rightMoves.erase(rightMoves.begin() + i, rightMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position
				rightMoves.erase(rightMoves.begin() + i + 1, rightMoves.end());
			}

			break;		
		}		
	}
	
	size = upMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(upMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				upMoves.erase(upMoves.begin() + i, upMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position
				upMoves.erase(upMoves.begin() + i + 1, upMoves.end());
			}

			break;		
		}		
	}
	
	size = downMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(downMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true); 				
				downMoves.erase(downMoves.begin() + i, downMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position
				downMoves.erase(downMoves.begin() + i + 1, downMoves.end());
			}

			break;		
		}		
	}
	
	// step 3: update LegalMoves
	
	this->LegalMoves.clear();
	
	for(auto i : leftMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	for(auto i : rightMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	for(auto i : upMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	for(auto i : downMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	leftMoves.clear();
	rightMoves.clear();
	upMoves.clear();
	downMoves.clear();
}
