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

Board::Board(int WIDTH, int HEIGHT) : WIDTH{8}, HEIGHT{8},
hasSetup{false}, hasPlay{false}, whiteScore{0}, blackScore{0}, 
textOrGraphic{true}, isWhiteTurn{true},
{
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			pieces[i][j] = nullptr;
		}
	}
}

// get the Piece* at pos
Piece* Board::atLocation(Position pos){
	return pieces[pos.getY][pos.getX];
}

// start setup mode
void Board::setupStart(){
	// if the play has started without setup, throw an error
	if(hasPlay){
		throw("The game starts without being set up!");
	}
	hasSetup = true;
}

// add a piece during setup stage
void Board::addPieceSetup(string pieceType, Position pos){
	// check if the setup stage has started
	if (!hasSetup){
		throw("The setup stage has not started! Call setupStart method!");
	}

	bool isWhite;
	// check if the piece is white or black
	if (pieceType[0] <= 'Z'){
		isWhite = true;
	} else {
		isWhite = false;
	}

    // if there is already a piece at pos, free this owner
	if(atLocation(pos)){
		delete pieces[pos.getY][pos.getX];
	}

	// contruct a new piece pointer to the position on board
	if (pieceType == "K" || pieceType == "k"){
		// need to wait Eric for the constructor of King/Queen/...
		atLocation(pos) = new King(this, isWhite, pos);
	} else if (pieceType == "Q" || pieceType == "q"){
		atLocation(pos) = new Queen(this, isWhite, pos);
	} else if (pieceType == "R" || pieceType == "r"){
		atLocation(pos) = new Rook(this, isWhite, pos);
	} else if (pieceType == "H" || pieceType == "h"){
		atLocation(pos) = new Knight(this, isWhite, pos);
	} else if (pieceType == "B" || pieceType == "b"){
		atLocation(pos) = new Bishop(this, isWhite, pos);
	} else if (pieceType == "P" || pieceType == "p"){
		atLocation(pos) = new Pawn(this, isWhite, pos);
	}
}

// remove a piece during the setup stage
void Board::removePieceSetup(Position pos){
	// check if the setup stage has started
	if (!hasSetup){
		throw("The setup stage has not started! Call setupStart method!");
	}

	if(atLocation(pos)){
		delete pieces[pos.getY][pos.getX];
	}
}

// determine whose turn to go next
void colourSetup(bool isWhite){
	// check if the setup stage has started
	if (!hasSetup){
		throw("The setup stage has not started! Call setupStart method!");
	}

	if(isWhite){
		isWhiteTurn = true;
	} else {
		isWhiteTurn = false;
	}
}

void originalSetup(){
	// set the black side at row #0
	pieces[0][0] = new Rook(this, false, Position(0, 0));
	pieces[0][1] = new Knight(this, false, Position(1, 0));
	pieces[0][2] = new Bishop(this, false, Position(2, 0));
	pieces[0][3] = new Queen(this, false, Position(3, 0));
	pieces[0][4] = new King(this, false, Position(4, 0));
	pieces[0][5] = new Bishop(this, false, Position(5, 0));
	pieces[0][6] = new Knight(this, false, Position(6, 0));
	pieces[0][7] = new Rook(this, false, Position(7, 0));
	// set the black side at row #1
	for(int i = 0; i < 7; ++i){
		pieces[1][i] = new Pawn(this, false, Position(i, 1));
	}
	// set the white side at row #6
    for(int j = 0; i < 7; ++i){
		pieces[6][j] = new Pawn(this, true, Position(j, 6));
	}
	// set the white side at row #7
	pieces[7][0] = new Rook(this, true, Position(0, 7));
	pieces[7][1] = new Knight(this, true, Position(1, 7));
	pieces[7][2] = new Bishop(this, true, Position(2, 7));
	pieces[7][3] = new Queen(this, true, Position(3, 7));
	pieces[7][4] = new King(this, true, Position(4, 7));
	pieces[7][5] = new Bishop(this, true, Position(5, 7));
	pieces[7][6] = new Knight(this, true, Position(6, 7));
	pieces[7][7] = new Rook(this, true, Position(7, 7));
}

// makeMove method needs to consider other cases
void Board::makeMove(Position start, Position end, string pieceType){
	// if there is already a piece at Position end, throw an error
	if(!atLocation(start)){
		throw("There is no piece at Position start!");
	}

	// move the piece pointer at Position start to Position end
	pieces[end.getY][end.getX] = move(pieces[start.getY][start.getX];)

	// free the owner piece at Position start
	delete pieces[start.getY][start.getX];

    bool isWhite;
	// check if the piece is white or blackß
	if (pieceType[0] <= 'Z'){
		isWhite = true;
	} else {
		isWhite = false;
	}

	// When the piece is a pawn, upgrade the pawn to another piece except King
}
