#include "pieces.h"  

Pieces::~Pieces(){LegalMoves.clear();}

Pieces::Pieces(Board *theBoard, bool White, Position Location): theBoard{theBoard},
															White{White},
															Location{Location},
															LegalMoves{},
															Protected{false},
															Pinned{nullptr},
															availableMoveCount{0}, 
															hasMoved{false}{}

bool Pieces::canMove(Position target) const{
	
	for(auto i : this->LegalMoves){
		if(i.equals(target)){
			return true;		
		}
	}
	
	return false;
}

bool Pieces::canAttack(Position target) const{
	
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

bool Pieces::isWhite() const{
	return this->White;
}

void Pieces::setProtected(bool val){
	this->Protected = val;
}

void Pieces::setPinned(Pieces* pin){
	this->Pinned = pin;
}

void Pieces::resetProtectedPinned(){
	this->Protected = false;
	this->Pinned = nullptr;
	
}

bool Pieces::isProtected() const{
	return this->Protected;
}

Pieces* Pieces::isPinned() const{
	return this->Pinned;
}

int Pieces::getMoveCount() const{
	return this->availableMoveCount;
}

std::vector<Position> Pieces::getLegalMoves() const{
	return this->LegalMoves;
}
	