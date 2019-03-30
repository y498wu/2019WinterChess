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

  public:
  void makeMove(Position start, Position end, bool isWhite);
  void setLevel(int level);
  void endGame(Player *player);
  Piece* atLocation(Position pos);
  void updateBoard();
  bool isCheck();
  bool checkMate();
  bool staleMate();
  bool textOrGraphic();
  bool printTextBoard();
  void printGraphicBoard();
  void printScores();
  void placePieces(string piece, Position pos, bool isWhite);

  ~Board();
   Board();
   
};

	std::ostream &operator<<(std::ostream &out, const Board &brd);

#endif