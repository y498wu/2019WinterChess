#include "pawn.h"  

Pawn::~Pawn(){LegalMoves.clear();}


Pawn::Pawn(Board *theBoard, bool White, Position Location): theBoard{theBoard},
															White{White},
															Location{Location},
															Protected{false},
															Pinned{nullptr},
															hasMoved{false}{}

std::string Pawn::checkType() const{
	return this->White ? "P" : "p";
}

void Pawn::updateMoves(){
		
	vector<Position> possibleForwardMoves;
	vector<Position> possibleAttackMoves;
		
	//step 1: move all possible legal moves into a temporary vector,
	
	if(this->White){
	
		int x = this->Location.getX();
		int y = this->Location.getY() - 1;
	
		possibleForwardMoves.emplace_back(new Position(x, y));
		
		if(this->hasMoved == false){
			y = this->Location.getY() - 2;
	
			possibleForwardMoves.emplace_back(new Position(x, y));
		}
		
		y = this->Location.getY() - 1;
		x = this->Location.getX() - 1;
		
		if(x >= 0 && x <= 7){
			possibleAttackMoves.emplace_back(new Position(x, y);
		}
		
		y = this->Location.getY() - 1;
		x = this->Location.getX() + 1;
		
		if(x >= 0 && x <=7){
			possibleAttackMoves.emplace_back(new Position(x, y);
		}
	}
	else{
		
		int x = this->Location.getX();
		int y = this->Location.getY() + 1;
	
		possibleForwardMoves.emplace_back(new Position(x, y));
		
		if(this->hasMoved == false){
			x = this->Location.getX();
			y = this->Location.getY() + 2;
	
			possibleForwardMoves.emplace_back(new Position(x, y));
		}
		
		y = this->Location.getY() + 1;
		x = this->Location.getX() - 1;
		
		if(x >= 0 && x <= 7){
			possibleAttackMoves.emplace_back(new Position(x, y);
		}
		
		y = this->Location.getY() + 1;
		x = this->Location.getX() + 1;
		
		if(x >= 0 && x <= 7){
			possibleAttackMoves.emplace_back(new Position(x, y);
		}
		
	}
	
	//step 2: check if there are pieces occupying any of the possible locations
	
	int size = possibleForwardMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(possibleForwardMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			possibleForwardMoves.erase(possibleForwardMoves.begin() + i, possibleForwardMoves.end());
		}			
	}
	//check for the attack on left and right
		
	size = possibleAttackMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(possibleAttackMoves.at(i));
		
		if(temp == nullptr){
			possibleAttackMoves.erase(possibleAttackMoves.begin() + i);
			size = possibleMoves.size();
			i--;
		}		
		else{//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				possibleAttackMoves.erase(possibleAttackMoves.begin() + i);
				size = possibleMoves.size();
				i--;
				
			}
			else if(temp->checkType() = "K" || temp->checkType() = "k"){
				King* tempKing = temp;
				tempKing->putInCheck(true);
			}
		}
		
	}
			
	// step 3: check for pinning
	
	if(this->Pinned != nullptr){
		possibleMoves.clear();
	}
	
	// step 4: update LegalMoves
	
	this->LegalMoves.clear();
	
	for(auto i : possibleForwardMoves){
		this->LegalMoves.emplace_back(i);
	}

	for(auto i : possibleAttackMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	possibleForwardMoves.clear();
	possibleAttackMoves.clear();
	
}
