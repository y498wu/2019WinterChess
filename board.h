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
  ~Board();
  Board(int WIDTH = 8; int HEIGHT = 8);

  int WIDTH;
  int HEIGHT;

  bool hasSetup;
  bool hasPlay;

  int whiteScore;
  int blackScore;

  bool isTextDisplay;
  bool isWhiteTurn;

  int level;

  Board(int WIDTH = 8, int HEIGHT = 8);

  // Get the piece pointer at pos
  Piece* atLocation(Position pos);

  // start setup mode
  void startSetup();

  // setup stage: add a piece at pos 
  // The board will automatically remove the piece on pos when it's adding a new piece there
  void addPieceSetup(std::string pieceType, Position pos);

  // setup stage: remove a piece at pos
  void removePieceSetup(Position pos);

  // setup stage: which colour's turn to go next
  void colourSetup(bool isWhite);

  // setup stage: user can choose the original setup
  void originalSetup();

  // play stage: setup is done and start to play
  void startPlay();

  // set the level
  void setLevel(int levelInput);

  // go through all the Piece* to update the board
  void updateBoard();

  // makeMove method
  void makeMove(Position start, Position end, std::string pieceType);
  
  // When a colour resigns
  void resign(bool isWhite);

  // print TextBoard when isTextDisplay is true by default
  // print GraphicBoard when isTextDisplay is false
  void printBoard(bool isTextDisplay);

  // void printGraphicBoard();
  void printScores();
   
};

std::ostream &operator<<(std::ostream &out, const Board &brd);


#endif
