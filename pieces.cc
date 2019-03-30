#include "pieces.h"  

Pieces::~Pieces(){LegalMoves.clear();}

bool Pieces::canMove(Position target) const{
	
	for(auto i : this->LegalMoves){
		if(i.equals(target)){
			return true;		
		}
	}
	
	return false;
}
	
Position Pieces::getPos() const{
	return this->Location;	
}
	
void Pieces::setPos(Position newPos){
	this->Location = newPos;
}