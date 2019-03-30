#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <utility>

#include "Position.h"
#include "Pieces.h"
#include "DisplaySuper.h"
#include "Player.h"
#include "board.h"

// we need the six types of pieces since we will allocate new pieces on board
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"

using namespace std;

void Board::addPiece(string pieceType, Position pos){
	bool isWhite;
	// check if the piece is white or blackß
	if (pieceType[0] <= 'Z'){
		isWhite = true;
	} else {
		isWhite = false;
	}

	// free the owner piece at pos
	delete pieces[pos.getX][pos.getY];

	// contruct a new piece pointer to the position on board
	if (pieceType == "K" || pieceType == "k"){
		// need to wait Eric for the constructor of King/Queen/...
		pieces[pos.getX][pos.getY] = new King(isWhite, pos);
	} else if (pieceType == "Q" || pieceType == "q"){
		pieces[pos.getX][pos.getY] = new Queen(isWhite, pos);
	} else if (pieceType == "R" || pieceType == "r"){
		pieces[pos.getX][pos.getY] = new Rook(isWhite, pos);
	} else if (pieceType == "H" || pieceType == "h"){
		pieces[pos.getX][pos.getY] = new Knight(isWhite, pos);
	} else if (pieceType == "B" || pieceType == "b"){
		pieces[pos.getX][pos.getY] = new Bishop(isWhite, pos);
	} else if (pieceType == "P" || pieceType == "p"){
		pieces[pos.getX][pos.getY] = new Pawn(isWhite, pos);
	}
}


