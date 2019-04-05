#ifndef KNIGHT_H
#define KNIGHT_H

#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class Knight: public Pieces{
	
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	Knight(Board *theBoard, bool White, Position Location);
	~Knight();
 
};


#endif
