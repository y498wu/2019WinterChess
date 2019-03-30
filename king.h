#ifndef KING_H
#define KING_H

#include "king.cc"
#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class King: public Pieces{
		
	bool hasMoved;
	bool inCheck;

public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	~King();
 
};


#endif
