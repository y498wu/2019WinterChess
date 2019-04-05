#ifndef ROOK_H
#define ROOK_H

#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class Rook: public Pieces{
		
	bool hasMoved;
	
	void helper_RemoveInvalid(std::vector<Position> &vec);
	

public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	Rook(Board *theBoard, bool White, Position Location);
	~Rook();
 
};


#endif
