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

Board::Board(int WIDTH, int HEIGHT) : WIDTH{8}, HEIGHT{8}
{
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			pieces[i][j] = nullptr;
		}
	}
}

void Board::addPiece(string pieceType, Position pos){
	bool isWhite;
	// check if the piece is white or blackß
	if (pieceType[0] <= 'Z'){
		isWhite = true;
	} else {
		isWhite = false;
	}

    // if there is already a piece at pos, throw an error
	if(pieces[pos.getX][pos.getY]){
		throw("There is already a piece at this position!");
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

Piece* Board::atLocation(Position pos){
	return pieces[pos.getX][pos.getY];
}

void Board::makeMove(Position start, Position end, string pieceType){
	// if there is already a piece at Position end, throw an error
	if(pieces[end.getX][end.getY]){
		throw("There is already a piece at Position end!");
	}
	
}


