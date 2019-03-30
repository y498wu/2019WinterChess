#ifndef PIECES_H
#define PIECES_H

#include "pieces.cc"
#include "position.h"
#include <vector>

class Pieces{
		
	Board *theBoard;
	bool isWhite;
	Position Location;
	vector<Position> LegalMoves;
	
public: 
	
	//non virtual methods, these will behave the same for every piece
	bool canMove(Position target) const;
	Position getPos() const;
	void setPos(Position newPos);
	
	//virtual methods, these need to be defined in each piece
	virtual void updateMoves() = 0;	
	virtual ~Pieces();
 
};


#endif
