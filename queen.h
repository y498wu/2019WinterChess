#ifndef QUEEN_H
#define QUEEN_H

#include "queen.cc"
#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class Queen: public Pieces{
		
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	Queen(Board *theBoard, bool White, Position Location);
	~Queen();
 
};


#endif
