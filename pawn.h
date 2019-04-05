#ifndef PAWN_H
#define PAWN_H

#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class Pawn: public Pieces{
		
	bool hasMoved;
	
public: 
	
	Pawn(Board *theBoard, bool White, Position Location);
	void updateMoves() override;
	
	std::string checkType() const override;
	~Pawn();
 
};


#endif
