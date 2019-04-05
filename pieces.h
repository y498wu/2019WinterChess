#ifndef PIECES_H
#define PIECES_H

#include <vector>
#include <string>
#include "position.h"

class Board;

class Pieces{
		
protected:		
	Board *theBoard;
	bool White;
	Position Location;
	std::vector<Position> LegalMoves;
	bool Protected;
	Pieces *Pinned;
	int availableMoveCount;
	
public: 
	
	//non virtual methods, these will behave the same for every piece
	bool canMove(Position target) const;
	Position getPos() const;
	bool isWhite() const;
	void setPos(Position newPos);
	void setProtected(bool val);
	void setPinned(Pieces* pin);
	void resetProtectedPinned(); //Resets protected and pinned fields, should be called before updateMoves
	bool isProtected() const;
	Pieces* isPinned() const;
	int getMoveCount() const;
	std::vector<Position> getLegalMoves() const;

	//virtual methods, these need to be defined in each piece
	virtual std::string checkType() const = 0;
	virtual void updateMoves() = 0;	
	virtual ~Pieces();
 
};


#endif
