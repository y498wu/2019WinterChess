#ifndef KING_H
#define KING_H

#include "king.cc"
#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class King: public Pieces{
	bool hasMoved;
	Piece* inCheck;
	bool inStaleMate;
	bool inCheckMate;
	
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	bool isInCheck() const;
	bool isInStaleMate() const;
	bool isInCheckMate() const;
	void putInCheck(Piece* check);
	Piece* returnPieceCheck() const;
		
	King(Board *theBoard, bool White, Position Location);
	~King();
 
};


#endif
