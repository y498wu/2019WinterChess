#include "bishop.h"  

Bishop::~Bishop(){LegalMoves.clear();}


Bishop::Bishop(Board *theBoard, bool White, Position Location): theBoard{theBoard},
															White{White},
															Location{Location},
															Protected{false},
															Pinned{nullptr}{}

std::string Bishop::checkType() const{
	return this->White ? "B" : "b";
}

void Bishop::updateMoves(){
	
	vector<Position> leftUpMoves;
	vector<Position> rightUpMoves;
	vector<Position> leftDownMoves;
	vector<Position> rightDownMoves;
	
	//step 1: move all possible legal moves into 4 temporary vector, one for each direction,
	//	make sure to have it in ordered fashion
	
	int y = this->Location.getY();
	
	for(int x = this->Location.getX() - 1; x >= 0; --x){
		y--;
		
		if(y < 0){
			break;
		}
		
		leftUpMoves.emplace_back(new Position(x, y));
	}
	
	y = this->Location.getY();
	
	for(int x = this->Location.getX() + 1; x <= 7; ++x){ 
		y--;
		
		if(y < 0){
			break;
		}
		
		rightUpMoves.emplace_back(new Position(x, y));
	}
	
	y = this->Location.getY();
	
	for(int x = this->Location.getX() - 1; x >= 0; --x){
		y++;
		
		if(y > 7){
			break;
		}
		
		leftDownMoves.emplace_back(new Position(x, y));
	}
	
	y = this->Location.getY();
	
	for(int x = this->Location.getX() + 1; x <= 7; ++x){ 
		y++;
		
		if(y > 7){
			break;
		}
		
		rightDownMoves.emplace_back(new Position(x, y));
	}
	
	//step 2: check if there are pieces occupying any of the possible locations
	
	int size = leftUpMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(leftUpMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				leftUpMoves.erase(leftUpMoves.begin() + i, leftUpMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(leftUpMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							temp->setPinned(this);
							temp->updateMoves();
						}
						
						break;
					}
				}
				
				leftUpMoves.erase(leftUpMoves.begin() + i + 1, leftUpMoves.end());	
			}

			break;		
		}		
	}
	
	size = rightUpMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(rightUpMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				rightUpMoves.erase(rightUpMoves.begin() + i, rightUpMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(rightUpMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							temp->setPinned(this);
							temp->updateMoves();
						}
						
						break;
					}
				}
				
				rightUpMoves.erase(rightUpMoves.begin() + i + 1, rightUpMoves.end());	
			}

			break;		
		}		
	}
	
	size = leftDownMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(leftDownMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				leftDownMoves.erase(leftDownMoves.begin() + i, leftDownMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(leftDownMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							temp->setPinned(this);
							temp->updateMoves();
						}
						
						break;
					}
				}
				
				leftDownMoves.erase(leftDownMoves.begin() + i + 1, leftDownMoves.end());	
			}

			break;		
		}		
	}
	
	size = rightDownMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(rightDownMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				rightDownMoves.erase(rightDownMoves.begin() + i, rightDownMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(rightDownMoves.at(j));
					
					//if the first piece behind temp is the enemy king
					if(isKing != nullptr ){
						if((isKing->checkType() == "k" && this->White) || isKing->checkType() == "K" && this->White == false){
							temp->setPinned(this);
							temp->updateMoves();
						}
						
						break;
					}
				}
				
				rightDownMoves.erase(rightDownMoves.begin() + i + 1, rightDownMoves.end());	
			}

			break;		
		}		
	}
	
	// step 3: check for pinning
	
	if(this->Pinned != nullptr){
		if(this->Pinned->getPos().getX() == this->Location.getX() || this->Pinned->getPos().getY() == this->Location.getY()){
			leftUpMoves.clear();
			rightUpMoves.clear();
			leftDownMoves.clear();
			rightDownMoves.clear();
		}
		else{
			if(this->Pinned->getPos().getX() < this->Location.getX() && this->Pinned->getPos().getY() < this->Location.getY()){
				rightUpMoves.clear();
				leftDownMoves.clear();
			}
			else if(this->Pinned->getPos().getX() > this->Location.getX() && this->Pinned->getPos().getY() > this->Location.getY()){
				rightUpMoves.clear();
				leftDownMoves.clear();
			}
			else{
				leftUpMoves.clear();
				rightDownMoves.clear();
			}
		}
	}
	
	// step 4: update LegalMoves
	
	this->LegalMoves.clear();
	
	for(auto i : leftUpMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	for(auto i : rightUpMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	for(auto i : leftDownMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	for(auto i : rightDownMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	leftUpMoves.clear();
	rightUpMoves.clear();
	leftDownMoves.clear();
	rightDownMoves.clear();
}
