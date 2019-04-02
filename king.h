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
	bool inCheckMate;
	
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	bool isInCheck() const;
	bool isInCheckMate() const;
	void putInCheck(bool check);
	
	King(Board *theBoard, bool White, Position Location);
	~King();
 
};


#endif
