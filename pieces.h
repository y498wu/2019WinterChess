#ifndef PIECES_H
#define PIECES_H

#include "pieces.cc"
#include "position.h"
#include <vector>
#include <string>

class Pieces{
		
	Board *theBoard;
	bool White;
	Position Location;
	vector<Position> LegalMoves;
	bool Protected;
	Piece *pinned;
	
public: 
	
	//non virtual methods, these will behave the same for every piece
	bool canMove(Position target) const;
	Position getPos() const;
	bool isWhite() const;
	void setPos(Position newPos);
	
	
	//virtual methods, these need to be defined in each piece
	virtual std::string checkType() const = 0;
	virtual void updateMoves() = 0;	
	virtual ~Pieces();
 
};


#endif
