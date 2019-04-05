#ifdef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"

class TextDisplay{
	// 2D vector of char
	std::vector<std::vector<char>> td;

public:

	int WIDTH;
    int HEIGHT;

	// constructor
	textDisplay();

	// add and remove pieces
	void print(Board *b)
};

#endif