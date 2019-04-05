#ifndef BISHOP_H
#define BISHOP_H

#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class Bishop: public Pieces{
		
	void helper_RemoveInvalid(std::vector<Position> &vec);
	
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	Bishop(Board *theBoard, bool White, Position Location);
	~Bishop();
 
};


#endif
