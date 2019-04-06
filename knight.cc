#include "knight.h"  
#include "board.h"

using namespace std;

Knight::~Knight(){LegalMoves.clear();}


Knight::Knight(Board *theBoard, bool White, Position Location): Pieces(theBoard, White, Location){}

std::string Knight::checkType() const{
	return this->White ? "H" : "h";
}

void Knight::updateMoves(){
		
	vector<Position> possibleMoves;
		
	//step 1: move all possible legal moves into a temporary vector,
	
	int x = this->Location.getX() - 2;
	int y = this->Location.getY() - 1;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() - 1;
	y = this->Location.getY() - 2;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() + 2;
	y = this->Location.getY() - 1;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() + 1;
	y = this->Location.getY() - 2;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() - 2;
	y = this->Location.getY() + 1;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() - 1;
	y = this->Location.getY() + 2;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() + 2;
	y = this->Location.getY() + 1;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
	}
	
	x = this->Location.getX() + 1;
	y = this->Location.getY() + 2;
	
	if(x >= 0 && x <= 7 && y >= 0 && y <= 7){
		possibleMoves.emplace_back(Position(x, y));
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
			else if(temp->checkType() == "K" || temp->checkType() == "k"){
				King* tempKing = dynamic_cast<King*>(temp);
				tempKing->putInCheck(this);
			}
		}	
				
	}
		
	// step 3: check for pinning
	
	if(this->Pinned != nullptr){
		possibleMoves.clear();
	}
	
	// step 4: update LegalMoves
	
	this->LegalMoves.clear();
	
	for(auto i : possibleMoves){
		this->LegalMoves.emplace_back(i);
	}
	
	this->availableMoveCount = LegalMoves.size();
	possibleMoves.clear();
	
}
