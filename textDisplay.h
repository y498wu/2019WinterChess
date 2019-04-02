#ifdef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>
#include "pieces.h"
#include "position.h"

class TextDisplay{
	// 2D vector of char
	std::vector<std::vector<char>> textBoard;

public:
	// constructor and destructor
	textDisplay(int WIDTH = 8; int HEIGHT = 8);
	~textDisplay;
	// add and remove pieces
	void addPiece(Position pos, char pieceType);
	void removePiece(Position pos);
};

std::ostream &operator<<(std::ostream &out, const TextDisplay &td);

#endif