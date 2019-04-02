#include "queen.h"  

Queen::~Queen(){LegalMoves.clear();}


Queen::Queen(Board *theBoard, bool White, Position Location): theBoard{theBoard},
															White{White},
															Location{Location},
															Protected{false},
															Pinned{nullptr}{}

std::string Queen::checkType() const{
	return this->White ? "B" : "b";
}

void Queen::updateMoves(){
	
	Pieces* isPin = nullptr;
	
	vector<Position> leftUpMoves;
	vector<Position> rightUpMoves;
	vector<Position> leftDownMoves;
	vector<Position> rightDownMoves;
	vector<Position> leftMoves;
	vector<Position> rightMoves;
	vector<Position> upMoves;
	vector<Position> downMoves;
	
	//step 1: move all possible legal moves into 8 temporary vectors, one for each direction,
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
	
	//step 2: check if there are pieces occupying any of the possible locations (in the 8 directions)
	
	int size = leftUpMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard.atLocation(leftUpMoves.at(i));
		
		if(temp != nullptr){//if there is a piece at the possible location
			if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
				temp->setProtected(true);			
				leftUpMoves.erase(leftUpMoves.begin() + i, leftUpMoves.end());
				
			}
			else{ //this means that it is an enemy piece, can move to its position, check for pinning
			
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(leftUpMoves.at(j));
					
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
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(rightUpMoves.at(j));
					
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
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(leftDownMoves.at(j));
					
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
				if(temp->checkType() = "K" || temp->checkType() = "k"){
					King* tempKing = temp;
					tempKing->putInCheck(true);
				}else{
				for(int j = i+1; j < size; j++){//check if the king is the next piece behind temp
					Pieces* isKing = this->theBoard.atLocation(rightDownMoves.at(j));
					
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
				rightDownMoves.erase(rightDownMoves.begin() + i + 1, rightDownMoves.end());	
			}

			break;		
		}		
	}
	
	size = leftMoves.size();
	
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
			leftUpMoves.clear();
			rightUpMoves.clear();;
			leftDownMoves.clear();;
			rightDownMoves.clear();;
		}
		else if(this->Pinned->getPos().getY() == this->Location.getY()){
			upMoves.clear();
			downMoves.clear();
			leftUpMoves.clear();
			rightUpMoves.clear();;
			leftDownMoves.clear();;
			rightDownMoves.clear();;
		}
		
		else if(this->Pinned->getPos().getX() < this->Location.getX() && this->Pinned->getPos().getY() < this->Location.getY()){
			rightUpMoves.clear();
			leftDownMoves.clear();
			leftMoves.clear();
			rightMoves.clear();
			upMoves.clear();
			downMoves.clear();
		}
		else if(this->Pinned->getPos().getX() > this->Location.getX() && this->Pinned->getPos().getY() > this->Location.getY()){
			rightUpMoves.clear();
			leftDownMoves.clear();
			leftMoves.clear();
			rightMoves.clear();
			upMoves.clear();
			downMoves.clear();
		}
		else{
			leftUpMoves.clear();
			rightDownMoves.clear();
			leftMoves.clear();
			rightMoves.clear();
			upMoves.clear();
			downMoves.clear();
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
	
	leftUpMoves.clear();
	rightUpMoves.clear();
	leftDownMoves.clear();
	rightDownMoves.clear();
	leftMoves.clear();
	rightMoves.clear();
	upMoves.clear();
	downMoves.clear();
	
	if(isPin != nullptr){
		isPin->updateMoves();
	}
}
