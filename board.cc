#include <string>
#include <vector>
#include <stack>
#include <utility>

#include "board.h"

using namespace std;

Board::Board() : pieces{8, vector<Pieces*>(8, nullptr)}, whiteKing{nullptr}, blackKing{nullptr}, isWhiteTurn{true}{}

Board::~Board(){
	// deallocate all Piece* at the 2D board
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			delete pieces[i][j];
		}
	}
}

Board::Board(const Board &n) : pieces{8, vector<Pieces*>(8, nullptr)}, whiteKing{n.whiteKing}, blackKing{n.blackKing}, isWhiteTurn{n.isWhiteTurn} {
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			pieces[i][j] = n.pieces[i][j];
		}
	}
}

Board::Board(Board &&n) : pieces{n.pieces}, whiteKing{n.whiteKing}, blackKing{n.blackKing}, isWhiteTurn{n.isWhiteTurn}{}

Board &Board::operator=(const Board &n){
	Board copy = n;

    using std::swap;

    swap(pieces, copy.pieces);
    swap(whiteKing, copy.whiteKing);
    swap(blackKing, copy.blackKing);
	swap(isWhiteTurn, copy.isWhiteTurn);

    return *this;
}

Board &Board::operator=(Board &&n){
	using std::swap;

    swap(pieces, n.pieces);
    swap(whiteKing, n.whiteKing);
    swap(blackKing, n.blackKing);
	swap(isWhiteTurn, n.isWhiteTurn);

    return *this;	
}

// get the Piece* at pos
Pieces* Board::atLocation(Position pos){
	return pieces[pos.getY()][pos.getX()];
}

// add a piece during setup stage
void Board::addPieceSetup(string pieceType, Position pos){
	
	bool pieceIsWhite;
	// check if the piece is white or black
	if (pieceType[0] <= 'Z'){
		pieceIsWhite = true;
	} else {
		pieceIsWhite = false;
	}

    // if there is already a piece at pos, free this owner
	if(atLocation(pos)){
		delete pieces[pos.getY()][pos.getX()];
		pieces[pos.getY()][pos.getX()] = nullptr;
	}

	// contruct a new piece pointer to the position on board
	if (pieceType == "K"){
		pieces[pos.getY()][pos.getX()] = new King(this, pieceIsWhite, pos);
		whiteKing = dynamic_cast<King*>(atLocation(pos));
	} else if (pieceType == "k"){
		pieces[pos.getY()][pos.getX()] = new King(this, pieceIsWhite, pos);
		blackKing = dynamic_cast<King*>(atLocation(pos));
	} else if (pieceType == "Q" || pieceType == "q"){
		pieces[pos.getY()][pos.getX()] = new Queen(this, pieceIsWhite, pos);
	} else if (pieceType == "R" || pieceType == "r"){
		pieces[pos.getY()][pos.getX()] = new Rook(this, pieceIsWhite, pos);
	} else if (pieceType == "H" || pieceType == "h"){
		pieces[pos.getY()][pos.getX()] = new Knight(this, pieceIsWhite, pos);
	} else if (pieceType == "B" || pieceType == "b"){
		pieces[pos.getY()][pos.getX()] = new Bishop(this, pieceIsWhite, pos);
	} else if (pieceType == "P" || pieceType == "p"){
		pieces[pos.getY()][pos.getX()] = new Pawn(this, pieceIsWhite, pos);
	}
}

// remove a piece during the setup stage
void Board::removePieceSetup(Position pos){
	if(atLocation(pos)){
		delete pieces[pos.getY()][pos.getX()];
		pieces[pos.getY()][pos.getX()] = nullptr;
	}
}

bool Board::validSetup(){//verifies if the setup is valid before exiting setup mode
	int whiteKingNum = 0;
	int blackKingNum = 0;
	this->updateBoard();
	
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 8; ++j){
			if (pieces[i][j]->checkType() == "K"){
				++whiteKingNum;
			} else if (pieces[i][j]->checkType() == "k"){
				++blackKingNum;
			} else if ((pieces[i][j]->checkType() == "P" || pieces[i][j]->checkType() == "p")
				&& (i == 0 || i == 7)){
				cout << "There is a pawn on the first or lat row! Can't leave setup mode!" << endl;
				return false;
			}
		}
	}
	if(whiteKingNum != 1){
		cout << "The board doesn't contain exactly one white king! Can't leave setup mode!" << endl;
		return false;
	} else if (blackKingNum != 1){
		cout << "The board doesn't contain exactly one black king! Can't leave setup mode!" << endl;
		return false;
	} else if (whiteKing->isInCheck()){
		cout << "The white king is in check! Can't leave setup mode!" << endl;
		return false;
	} else if (blackKing->isInCheck()){
		cout << "The black king is in check! Can't leave setup mode!" << endl;
		return false;
	} else {
		return true;
	}
}


// setter to set the current turn
void Board::setTurn(bool isWhite){
	this->isWhiteTurn = isWhite;
}

King* Board::WhiteKing() const{
	return this->whiteKing;
}
 
King* Board::BlackKing() const{
	return this->blackKing;
}

void Board::originalSetup(){
	// set the black side at row #0
	pieces[0][0] = new Rook(this, false, Position(0, 0));
	pieces[0][1] = new Knight(this, false, Position(1, 0));
	pieces[0][2] = new Bishop(this, false, Position(2, 0));
	pieces[0][3] = new Queen(this, false, Position(3, 0));
	pieces[0][4] = new King(this, false, Position(4, 0));
	blackKing = dynamic_cast<King*>(pieces[0][4]);
	pieces[0][5] = new Bishop(this, false, Position(5, 0));
	pieces[0][6] = new Knight(this, false, Position(6, 0));
	pieces[0][7] = new Rook(this, false, Position(7, 0));
	// set the black side at row #1
	for(int i = 0; i <= 7; ++i){
		pieces[1][i] = new Pawn(this, false, Position(i, 1));
	}
	// set the white side at row #6
    for(int i = 0; i <= 7; ++i){
		pieces[6][i] = new Pawn(this, true, Position(i, 6));
	}
	// set the white side at row #7
	pieces[7][0] = new Rook(this, true, Position(0, 7));
	pieces[7][1] = new Knight(this, true, Position(1, 7));
	pieces[7][2] = new Bishop(this, true, Position(2, 7));
	pieces[7][3] = new Queen(this, true, Position(3, 7));
	pieces[7][4] = new King(this, true, Position(4, 7));
	whiteKing = dynamic_cast<King*>(pieces[7][4]);
	pieces[7][5] = new Bishop(this, true, Position(5, 7));
	pieces[7][6] = new Knight(this, true, Position(6, 7));
	pieces[7][7] = new Rook(this, true, Position(7, 7));
}

void Board::updateBoard(){
	// go through all the Piece* to reset the protected&pinned status
	for(int y = 0; y <= 7; y++){
		for(int x = 0; x <= 7; x++){
			Pieces* temp = pieces[y][x];
			temp->resetProtectedPinned();
		}	
	}
	// go through all the Piece* to update their legalMoves
	for(int y = 0; y <= 7; y++){
		for(int x = 0; x <= 7; x++){
			Pieces* temp = pieces[y][x];
			temp->updateMoves();
		}	
	}
	whiteKing->updateMoves();
	blackKing->updateMoves();
}

// makeMove method needs to consider other cases
std::string Board::makeMove(Position start, Position end, string pieceType){
	// if there is no piece at Position start, throw an error
	if (!atLocation(start)){
		return "no piece";
	}
	// check the piece at Position start's colour
	bool pieceIsWhite;
	if (atLocation(start)->isWhite()){
		pieceIsWhite = true;
	} else {
		pieceIsWhite = false;
	}
	// check if it's the piece at Position start's colour's turn
	if (pieceIsWhite != isWhiteTurn){
		return "wrong color";
	}
	// check if the move is valid
	if(!atLocation(start)->canMove(end)){
		return "not legal";
	}
	// check if this colour's king is in check
	King* currentKing;
	if (isWhiteTurn){
		currentKing = whiteKing;
	} else {
		currentKing = blackKing;
	}
	// if currentKing is in check, make the move first
	// and then check if this move enable the currentKing to escape from check
	Pieces* temp = nullptr;
	if (currentKing->isInCheck()){
		// move atLocation(end) to temp piece pointer
	    temp = atLocation(end);
		// move atLocation(start) to atLocation(end)
		// move will automatically free atLocation(start)
		pieces[end.getY()][end.getX()] = atLocation(start);
		pieces[start.getY()][start.getX()] = nullptr;
		// update the board after this move
		updateBoard();
		// check if the current king is still in check
		if (currentKing->isInCheck()){
			// if still in check, reverse the move back and throw an error
			pieces[start.getY()][start.getX()] = atLocation(end);
			pieces[end.getY()][end.getX()] = nullptr;
			pieces[end.getY()][end.getX()] = temp;
			temp = nullptr;
			return "still in check";
		} else {
			delete temp;
		}
	} else {
		// if currentKing isn't in check, just update the board
		delete pieces[end.getY()][end.getX()];
		pieces[end.getY()][end.getX()] = nullptr;
		pieces[end.getY()][end.getX()] = pieces[start.getY()][start.getX()];
		pieces[start.getY()][start.getX()] = nullptr;
		updateBoard();
	}
	// After the move, we check if the pawn needs promotion
	// if atLocation(end) is a white pawn and it's white's turn and the pieceType is white
	// or if atLocation(end) is a black pawn and it's black's turn
	if ((atLocation(end)->checkType() == "P" && isWhiteTurn && end.getY() == 7 && pieceType[0] <= 'Z') 
		|| (atLocation(end)->checkType() == "p" && !isWhiteTurn && end.getY() == 0)){
		delete pieces[end.getY()][end.getX()];
		if (pieceType == "Q" || pieceType == "q"){
			pieces[end.getY()][end.getX()] = new Queen(this, pieceIsWhite, end);
		} else if (pieceType == "R" || pieceType == "r"){
			pieces[end.getY()][end.getX()] = new Rook(this, pieceIsWhite, end);
		} else if (pieceType == "H" || pieceType == "h"){
			pieces[end.getY()][end.getX()] = new Knight(this, pieceIsWhite, end);
		} else if (pieceType == "B" || pieceType == "b"){
			pieces[end.getY()][end.getX()] = new Bishop(this, pieceIsWhite, end);
		}
	}
	// check if the enemy colour's king is in checkmate
	// This one need more implementations......
	// such as draw state, restart te setup, display the board
	if (isWhiteTurn && blackKing->isInCheckMate()){
		return "black checkmate";
	} else if (!isWhiteTurn && whiteKing->isInCheckMate()){
		return "white checkmate";
	}else if (blackKing->isInStaleMate() || whiteKing->isInStaleMate()){
		return "stalemate";
	} 	
	
	return "sucessful move";
}
