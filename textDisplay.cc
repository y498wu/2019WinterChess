#include <vector>
#include <iostream>

#include "textDisplay.h"

using namespace std;

// constructor
TextDisplay::TextDisplay() : td{8, vector<char>(8)}, WIDTH{8}, HEIGHT{8}{
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

void TextDisplay::print(Board *b){
	for(int i = 0; i < HEIGHT; i++){
		cout << 8-i << ' ';
		for(int j = 0; j < WIDTH; j++){
			if (b->atLocation(Position(j, i))){				
				cout << b->atLocation(Position(j, i))->checkType();
			} else if ((i - j) % 2 == 0){
				cout << ' ';
			} else {
				cout << '_';
			}
		}
		cout << endl;
	}
	cout << endl << "  abcdefgh" << endl;
}
