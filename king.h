#ifndef KING_H
#define KING_H

#include "pieces.h"
#include "position.h"
#include <vector>
#include <string>

class King: public Pieces{
	Pieces* inCheck;
	bool inStaleMate;
	bool inCheckMate;
	
public: 
	
	void updateMoves() override;
	std::string checkType() const override;
	
	bool isInCheck() const;
	bool isInStaleMate() const;	
	bool isInCheckMate() const;
	void putInCheck(Pieces* check);
	Pieces* returnPieceCheck() const;
		
	King(Board *theBoard, bool White, Position Location);
	~King();
 
};


#endif
