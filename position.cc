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

void Position::setY(int val){
	this->y = val;
}

bool Position::equals(Position pos) const{
	if(this->x == pos.getX() && this->y == pos.getY()){ return true;}	
		
	return false;	
}

bool Position::isValid() const{
	if(this->x >= 0 && this->x <= 7 && this->y >= 0 && this->y <= 7){
		return true;
	}
	return false;
}
