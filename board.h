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
#include "player.h"

class Board {
  std::vector<std::vector<Piece*>> pieces;
  //so the reason we need triple pointers is because Piece is an abstract class so we can't make any 
  //piece objects however we can create piece pointers so basically the board is a a board of piece pointers.
  //and these piece pointers can point to any of the possible pieces, which is why the board dosen't need to
  //know what types of pieces they are, that is all handeled by the piece class and its virtual methods

  King* whiteKing;
  King* blackKing;

  public:
  Board();
  ~Board();

  int WIDTH;
  int HEIGHT;

  bool hasPlay;

  int whiteScore;
  int blackScore;

  bool isTextDisplay;
  bool isWhiteTurn;

  int level;

  Board(int WIDTH = 8, int HEIGHT = 8);

  // Get the piece pointer at pos
  Piece* atLocation(Position pos);

  // setup stage: add a piece at pos 
  // The board will automatically remove the piece on pos when it's adding a new piece there
  void addPieceSetup(std::string pieceType, Position pos);

  // setup stage: remove a piece at pos
  void removePieceSetup(Position pos);

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
