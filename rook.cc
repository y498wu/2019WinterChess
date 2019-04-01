#include "rook.h"  

Rook::~Rook(){LegalMoves.clear();}


Rook::Rook(Board *theBoard, bool White, Position Location): theBoard{theBoard},
															White{White},
															Location{Location},
															Protected{false},
															Pinned{nullptr},
															hasMoved{false}{}

std::string Rook::checkType() const{
	return this->White ? "R" : "r";
}

void Rook::updateMoves(){
	
	Pieces* isPin = nullptr;
	
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
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(leftMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							if(temp->isPinned() == nullptr){
								temp->setPinned(this);
								isPin = temp;
							}
						}
						
						break;
					}
				}
				}
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
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(rightMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							if(temp->isPinned() == nullptr){
								temp->setPinned(this);
								isPin = temp;
							}
						}
						
						break;
					}
				}
				}
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
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(upMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							if(temp->isPinned() == nullptr){
								temp->setPinned(this);
								isPin = temp;
							}
						}
						
						break;
					}
				}
				}
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
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
			
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(downMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							if(temp->isPinned() == nullptr){
								temp->setPinned(this);
								isPin = temp;
							}
						}
						
						break;
					}
				}
				}
				downMoves.erase(downMoves.begin() + i + 1, downMoves.end());	
			}

			break;		
		}		
	}
	
	// step 3: check for pinning
	
	if(this->Pinned != nullptr){
		if(this->Pinned->getPos().getX() == this->Location.getX()){
			leftMoves.clear();
			rightMoves.clear();
		}
		else if(this->Pinned->getPos().getY() == this->Location.getY()){
			upMoves.clear();
			downMoves.clear();
		}
		else{
			leftMoves.clear();
			rightMoves.clear();
			upMoves.clear();
			downMoves.clear();
		}
	}
	
	// step 4: update LegalMoves
	
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
	
	if(isPin != nullptr){
		isPin->updateMoves();
	}
}
