#include "position.h"  

Position::Position(int x, int y) : x{x}, y{y} {}

int Position::getX() const{
	return this->x;
}

int Position::getY() const{
	return this->y;
}

void Position::setX(int val){
	this->x = val;
}

void Position::getX(int val){
	this->y = val;
}

bool Position::equals(Position pos) const{
	if(this->x == pos.getX() && this->y == pos.getY()){ return true;}	
		
	return false;	
}