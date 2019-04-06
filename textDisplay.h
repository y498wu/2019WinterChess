#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"

class TextDisplay{
	// 2D vector of char
	std::vector<std::vector<char>> td;

public:

	int WIDTH;
    int HEIGHT;

	// constructor
	TextDisplay();

	// add and remove pieces
	void print(Board *b);
};

#endif