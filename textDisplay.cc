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
			if ((i - j) % 2 == 0){
				td[i][j] = ' ';
			} else {
				td[i][j] = '_';
			}
			td[i][j] = ' ';
		}
	}
}

void textDisplay::print(Board *b){
	for(int i = 0; i < HEIGHT; i++){
		cout << 8-i << ' ';
		for(int j = 0; j < WIDTH; j++){
			if (b[i][j]){
				cout << b[i][j]->checkType();
			} else if ((i - j) % 2 == 0){
				cout << ' ';
			} else {
				cout << '_';
			}
		}
		cout << endl;
	}
	cout << endl << "abcdefgh" << endl;
}
