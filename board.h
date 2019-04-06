#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <utility>

#include "position.h"
#include "pieces.h"
#include "textDisplay.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "pawn.h"

class Board {
  std::vector<std::vector<Pieces*>> pieces;
  //so the reason we need triple pointers is because Piece is an abstract class so we can't make any 
  //piece objects however we can create piece pointers so basically the board is a a board of piece pointers.
  //and these piece pointers can point to any of the possible pieces, which is why the board dosen't need to
  //know what types of pieces they are, that is all handeled by the piece class and its virtual methods

  King* whiteKing;
  King* blackKing;

  bool isWhiteTurn;		

  public:
  Board();
  ~Board();
  Board(const Board &n);
  Board(Board &&n);
  Board &operator=(const Board &n);
  Board &operator=(Board &&n);	

  // Get the piece pointer at pos
  Pieces* atLocation(Position pos);

  // setup stage: add a piece at pos 
  // The board will automatically remove the piece on pos when it's adding a new piece there
  void addPieceSetup(std::string pieceType, Position pos);

  // setup stage: remove a piece at pos
  void removePieceSetup(Position pos);
  
  // verifies if the setup is valid
  bool validSetup();

  // setup stage: which colour's turn to go next
  void setTurn(bool isWhite);
  
  //getters for kings, returns white and black king pointers
  King* WhiteKing() const;
  King* BlackKing() const;

  // setup stage: user can choose the original setup
  void originalSetup();

  // go through all the Piece* to update the board
  void updateBoard();

  // makeMove method
  std::string makeMove(Position start, Position end, std::string pieceType); 
};

#endif
