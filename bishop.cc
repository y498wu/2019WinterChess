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


void Bishop::helper_RemoveInvalid(vector<Position> &vec){
	
	int size = vec.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard->atLocation(vec.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				vec.erase(vec.begin() + i, vec.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
			
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = dynamic_cast<King*>(temp);
					tempKing->putInCheck(this);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(vec.at(j));
					
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
				vec.erase(vec.begin() + i + 1, vec.end());	
			}

			break;		
		}		
	}
}

void Bishop::updateMoves(){
	
	Pieces* isPin = nullptr;
	
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
	
	helper_RemoveInvalid(leftUpMoves);
	helper_RemoveInvalid(rightUpMoves);
	helper_RemoveInvalid(leftDownMoves);
	helper_RemoveInvalid(rightDownMoves);
	
	// step 3: check for pinning
	
	if(this->Pinned != nullptr){
		if(this->Pinned->getPos().getX() == this->Location.getX() || this->Pinned->getPos().getY() == this->Location.getY()){
			leftUpMoves.clear();
			rightUpMoves.clear();
			leftDownMoves.clear();
			rightDownMoves.clear();
		}
		else if(this->Pinned->getPos().getX() < this->Location.getX() && this->Pinned->getPos().getY() < this->Location.getY()){
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
	
	this->availableMoveCount = LegalMoves.size();
	leftUpMoves.clear();
	rightUpMoves.clear();
	leftDownMoves.clear();
	rightDownMoves.clear();
	
	if(isPin != nullptr){
		isPin->updateMoves();
	}
	
}
