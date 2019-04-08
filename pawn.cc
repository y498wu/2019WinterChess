#include "pawn.h"  
#include "board.h"

using namespace std;

Pawn::~Pawn(){LegalMoves.clear();}

Pawn::Pawn(Board *theBoard, bool White, Position Location): Pieces(theBoard, White, Location), AttackMoves{} {}

std::string Pawn::checkType() const{
	return this->White ? "P" : "p";
}

bool Pawn::canAttack(Position target) const{
	
	for(auto i : this->AttackMoves){
		if(i.equals(target)){
			return true;		
		}
	}
	
	return false;
}

void Pawn::updateMoves(){
	
	availableAttackCount = 0; 
	
	vector<Position> possibleForwardMoves;
	vector<Position> possibleAttackMoves;
		
	//step 1: move all possible legal moves into a temporary vector,
	
	if(this->White){
	
		int x = this->Location.getX();
		int y = this->Location.getY() - 1;
		
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
			possibleForwardMoves.emplace_back(Position(x, y));
		}
		
		if(this->hasMoved == false){
			y = this->Location.getY() - 2;
			
			if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
				possibleForwardMoves.emplace_back(Position(x, y));
			}
		}
		
		y = this->Location.getY() - 1;
		x = this->Location.getX() - 1;
		
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
			possibleAttackMoves.emplace_back(Position(x, y));
		}
		
		y = this->Location.getY() - 1;
		x = this->Location.getX() + 1;
		
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
			possibleAttackMoves.emplace_back(Position(x, y));
		}
	}
	else{
		
		int x = this->Location.getX();
		int y = this->Location.getY() + 1;
	
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
			possibleForwardMoves.emplace_back(Position(x, y));
		}
		
		if(this->hasMoved == false){
			x = this->Location.getX();
			y = this->Location.getY() + 2;
			
			if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
				possibleForwardMoves.emplace_back(Position(x, y));
			}
		}
		
		y = this->Location.getY() + 1;
		x = this->Location.getX() - 1;
		
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
			possibleAttackMoves.emplace_back(Position(x, y));
		}
		
		y = this->Location.getY() + 1;
		x = this->Location.getX() + 1;
		
		if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
			possibleAttackMoves.emplace_back(Position(x, y));
		}
		
	}
	this->AttackMoves.clear();
	for(auto i : possibleAttackMoves){
		this->AttackMoves.emplace_back(i);
	}
	
	//step 2: check if there are pieces occupying any of the possible locations
	int size = possibleForwardMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard->atLocation(possibleForwardMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			possibleForwardMoves.erase(possibleForwardMoves.begin() + i, possibleForwardMoves.end());
			break;
			
		}			
	}
	//check for the attack on left and right

	size = possibleAttackMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard->atLocation(possibleAttackMoves.at(i));
		
		if(temp == nullptr){
			possibleAttackMoves.erase(possibleAttackMoves.begin() + i);
			size = possibleAttackMoves.size();
			i--;
		}		
		else{//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				possibleAttackMoves.erase(possibleAttackMoves.begin() + i);
				size = possibleAttackMoves.size();
				i--;
				
			}
			else if((temp->checkType() == "K") || (temp->checkType() == "k")){
				King* tempKing = dynamic_cast<King*>(temp);
				tempKing->putInCheck(this);
			}else{
				availableAttackCount++;
			}
		}
		
	}
		
	// step 3: check for pinning
	
	if(this->Pinned != nullptr){
		if(this->Pinned->getPos().getX() == this->Location.getX()){
			possibleAttackMoves.clear();
		}
		else if(this->Pinned->getPos().getY() == this->Location.getY()){
			possibleForwardMoves.clear();
			possibleAttackMoves.clear();
		}
		else{
			
			possibleForwardMoves.clear();
			
			size = possibleAttackMoves.size();
	
			for(int i = 0; i < size ; ++i){
				Position current_pos = possibleAttackMoves.at(i);
				
				if(current_pos.equals(this->Pinned->getPos()) == false){
					possibleAttackMoves.erase(possibleAttackMoves.begin() + i);
					size = possibleAttackMoves.size();
					i--;
				}
			}				
		}	
	}
	
	// step 4: update LegalMoves

	this->LegalMoves.clear();
	
	for(auto i : possibleForwardMoves){
		this->LegalMoves.emplace_back(i);
	}

	for(auto i : possibleAttackMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	this->availableMoveCount = LegalMoves.size();
	possibleForwardMoves.clear();
	possibleAttackMoves.clear();
	
}
