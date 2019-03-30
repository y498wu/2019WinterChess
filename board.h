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

  bool hasSetup = false;
  bool hasPlay = false;

  int whiteScore = 0;
  int blackScore = 0;

  bool textOrGraphic = true;

  public:
  ~Board();
  Board();

  // setup stage: add/remove a piece to the pos at the board
  void addPiece(std::string pieceType, Position pos);
  void removePiece(Position pos);

  // makeMove method
  void makeMove(Position start, Position end, Position pos);
  // Not sure I understand what atLocation is doing
  Piece* atLocation(Position pos);
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
