#ifndef BISHOP_H
#define BISHOP_H

#include "bishop.cc"
#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class Bishop: public Pieces{
		
	void helper_RemoveInvalid(vector<Position> &vec);
	
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	Bishop(Board *theBoard, bool White, Position Location);
	~Bishop();
 
};


#endif
