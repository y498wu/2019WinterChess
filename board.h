#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include <iostream>
#include <stack>
#include <utility>

#include "Position.h"
#include "Pieces.h"
#include "DisplaySuper.h"
#include "Player.h"

const int WIDTH = 8;
const int HEIGHT = 8;

class Board {
  vector<vector<Piece*>> pieces;
  //so the reason we need triple pointers is because Piece is an abstract class so we can't make any 
  //piece objects however we can create piece pointers so basically the board is a a board of piece pointers.
  //and these piece pointers can point to any of the possible pieces, which is why the board dosen't need to
  //know what types of pieces they are, that is all handeled by the piece class and its virtual methods

  public:
  ~Board();
  Board();

  bool hasSetup = false;
  bool hasPlay = false;

  int whiteScore = 0;
  int blackScore = 0;

  bool textOrGraphic = true;

  // setup stage: add a piece to the pos at the board
  // The board will automatically remove the piece on pos when it's adding a new piece there
  void addPiece(std::string pieceType, Position pos);

  // Get the piece pointer at pos
  Piece* atLocation(Position pos);

  // makeMove method
  void makeMove(Position start, Position end, std::string pieceType);
  
  // When a colour resigns
  void resign(bool isWhite);
  // set the level
  void setLevel(int level);
  // if a colour is undercheck
  bool isCheck(bool isWhite);
  // print TextBoard when textOrGarphic is true by default
  void printTextBoard(bool textOrGraphic);
  // void printGraphicBoard();
  void printScores();
   
};

std::ostream &operator<<(std::ostream &out, const Board &brd);


#endif
