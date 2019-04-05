#include <vector>
#include <iostream>

#include "pieces.h"
#include "position.h"
#include "board.h"
#include "textDisplay.h"

using namespace std;

// constructor
textDisplay::textDisplay() : WIDTH{8}, HEIGHT{8} 
{
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			td[i][j] = ' ';
		}
	}
}

void textDisplay::print(Board *b){
	for(int i = 0; i < HEIGHT; i++){
		for(int j = 0; j < WIDTH; j++){
			cout << b[i][j]->checkType();
		}
		cout << endl;
	}
}
