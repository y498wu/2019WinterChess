#include "king.h"  
#include "board.h"

using namespace std;

King::~King(){LegalMoves.clear();}


King::King(Board *theBoard, bool White, Position Location): Pieces(theBoard, White, Location),
															hasMoved{false},
															inCheck{nullptr},
															inStaleMate{false},
															inCheckMate{false}{}

std::string King::checkType() const{
	return this->White ? "K" : "k";
}

bool King::isInCheck() const{
	
	return (this->inCheck == nullptr) ? false : true;	
}

bool King::isInStaleMate() const{
	return this->inStaleMate;		
}

bool King::isInCheckMate() const{
	return this->inCheckMate;		
}

void King::putInCheck(Pieces* check){
	this->inCheck = check;
}


Pieces* King::returnPieceCheck() const{
	return this->inCheck;	
}


void King::updateMoves(){
	
	vector<Position> possibleMoves;
	
	//step 1: move all possible legal moves into a temporary vector
	//legal moves for the King are all around it in a 3 x 3 square 
	//not including ofc its current location and out of bounds locations
	for(int y = this->Location.getY() - 1; y <= this->Location.getY() + 1; ++y){ 
		for(int x = this->Location.getX() - 1; x <= this->Location.getX() + 1; ++x){ 
			if(x >= 0 && x <= 7 && y >= 0 && y <= 7){				
				possibleMoves.emplace_back(Position(x, y));						
			}		
		}		
	}
	
	//step 2: check if there are pieces occupying any of the possible locations
	
	int size = possibleMoves.size();
	
	for(int i = 0; i < size ; ++i){
		
		Pieces* temp =  this->theBoard->atLocation(possibleMoves.at(i));
		
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
			Pieces* temp = this->theBoard->atLocation(current);
		
			if(temp != nullptr){
				if((this->White && temp->isWhite() == false) || (this->White == false && temp->isWhite())){
					for(auto i = possibleMoves.begin(); i != possibleMoves.end(); ){
						if(temp->canMove(*i)){
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
	
	this->availableMoveCount = LegalMoves.size();
	possibleMoves.clear();
	
	//if no legal moves available for the king, might be in checkmate or stalemate
	if(this->availableMoveCount == 0){
		if(this->isInCheck()){
			this->inCheckMate = true; // assume its checkmate, check if attacking piece can be captured
			
			Position attack_pos = this->inCheck->getPos();
			
			for(int y = 0; y <= 7; y++){
				for(int x = 0; x <= 7; x++){
					Position current(x, y);
					Pieces* temp = this->theBoard->atLocation(current);
					
					if(temp != nullptr){// if an ally piece can capture the attacking pos, its not checkmate
						if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
							if(temp->canMove(attack_pos)){
								this->inCheckMate = false;
								break;
							}
						}
					}
					
					if(this->inCheckMate == false){
						break;
					}
				}
				
				if(this->inCheckMate == false){
					break;
				}
			}
			
			if(this->inCheckMate == true){//if its still in check, see if a piece can block the attack route
				
				vector<Position> preventAttack;
				Position tempDiff(attack_pos.getX() - this->Location.getX(), attack_pos.getY() - this->Location.getY());
				
				int absolute_x = (tempDiff.getX() > 0) ? tempDiff.getX() : -1*tempDiff.getX(); 
				int absolute_y = (tempDiff.getY() > 0) ? tempDiff.getY() : -1*tempDiff.getY(); 
				
				if(tempDiff.getY() == 0){//attacking piece has the same Y
					if(tempDiff.getX() > 1){		
						for(int start = this->Location.getX() + 1; start < attack_pos.getX(); ++start){
							Position temp( start, attack_pos.getY());
							preventAttack.emplace_back(temp);
						}
					}
					else if(tempDiff.getX() < -1){
						for(int start = this->Location.getX() - 1; start > attack_pos.getX(); --start){
							Position temp( start, attack_pos.getY());
							preventAttack.emplace_back(temp);
						}						
					}
				}
				else if(tempDiff.getX() == 0){//attacking piece has the same X
					if(tempDiff.getY() > 1){		
						for(int start = this->Location.getY() + 1; start < attack_pos.getY(); ++start){
							Position temp(attack_pos.getX(), start);
							preventAttack.emplace_back(temp);
						}
					}
					else if(tempDiff.getY() < -1){
						for(int start = this->Location.getY() - 1; start > attack_pos.getY(); --start){
							Position temp(attack_pos.getX(), start);
							preventAttack.emplace_back(temp);
						}						
					}					
				}
				else if(absolute_x == absolute_y){//attacking piece is diagonal
					if(tempDiff.getY() > 1 && tempDiff.getX() > 1){
						
						int y = this->Location.getY();
	
						for(int x = this->Location.getX() + 1; x < attack_pos.getX() ; ++x){ 
							y++;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
					else if(tempDiff.getY() > 1 && tempDiff.getX() < -1){
						
						int y = this->Location.getY();
	
						for(int x = this->Location.getX() - 1; x > attack_pos.getX() ; --x){ 
							y++;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
					else if(tempDiff.getY() < -1 && tempDiff.getX() > 1){
						
						int y = this->Location.getY();
	
						for(int x = this->Location.getX() + 1; x < attack_pos.getX() ; ++x){ 
							y--;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
					else if(tempDiff.getY() < -1 && tempDiff.getX() < -1){
						
						int y = this->Location.getY();
	
						for(int x = this->Location.getX() - 1; x > attack_pos.getX() ; --x){ 
							y--;
							Position temp(x, y);
							preventAttack.emplace_back(temp);
						}						
					}
				}		
				
				// now we have a vector preventAttack, if any ally piece can move there not checkmate
					
				for(int y = 0; y <= 7; y++){
					for(int x = 0; x <= 7; x++){
						Position current(x, y);
						Pieces* temp = this->theBoard->atLocation(current);
						if(temp != nullptr){
							if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
								for(auto i : preventAttack){// if an ally piece can move to a possible position in vector
									if(temp->canMove(i)){
										this->inCheckMate = false;
										break;
									}
								}
							}
						}
						
						if(this->inCheckMate == false){
							break;
						}
					}
					
					if(this->inCheckMate == false){
						break;
					}
				}		
			}			
			
		}else{
			this->inStaleMate = true; // assume its stalemate, check if ally pieces can move
			
			for(int y = 0; y <= 7; y++){
				for(int x = 0; x <= 7; x++){
					Position current(x, y);
					Pieces* temp = this->theBoard->atLocation(current);
		
					if(temp != nullptr){// if an ally piece has an available move then its not stalemate
						if((this->White && temp->isWhite()) || (this->White == false && temp->isWhite() == false)){
							if(temp->getMoveCount() > 0){
								this->inStaleMate = false;
								break;
							}
						}
					}
					
					if(this->inStaleMate == false){
						break;
					}
				}
				
				if(this->inStaleMate == false){
					break;
				}
			}			
		}	
	}
}
