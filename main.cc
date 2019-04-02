#include <string>
#include <iostream>

int main(){
	
	while(true){
		
		string command;
		cin >> command;
		
		if(command == "game"){
			Board b = new Board();
			
			string white_player;
			string black_player;
			
			cin >> white_player;
			cin >> black_player;
			
			if(white_player == human){
				Human white_p = new Human(true, b);
			}
			else if(white_player == computer[1]){
				Computer white_p = new Human(true, b, 1);
			}
			//ETC ADD ALL THE DIFFICULTIES
			
			if(black_player == human){
				Human black_p = new Human(false, b);
			}
			else if(black_player == computer[1]){
				Computer black_p = new Human(false, b, 1);
			}
			//ETC ADD ALL THE DIFFICULTIES
			
			//start the game
			
			while(true){
			
				string setup_type;
				cin >> setup_type;
			
				if(setup_type == "default"){
					b.originalSetup();
				}
				else if(setup_type == "setup"){//ENTER SETUP MODE
					while(){// CODE FOR SETUP MODE HERE, READ COMMANDS AND PASS THEM TO THE BOARD
					
					
					
					}
				}
			
			
			
				while(true){ //MOVES START TO HAPPEN
					
					b.textDisplay(); //Or graphics display based off a parameter or whatever
					
					string read_move;
					cin >> read_move;
						
					// white players move, if game ends then break and increment white player's score
					
					
					// END OF WHITE PLAYERS MOVE
					b.textDisplay(); //Or graphics display based off a parameter or whatever
					
					string read_move;
					cin >> read_move;
						
					// black player makes the move	
		
				} // THIS IS WHERE THE GAME ENDS
			
				
				
				// THIS IS WHERE YOU DISPLAY THE SCORE
			
			
				// ASK THE INPUT IF HE WANTS TO PLAY ANOTHER ROUND
				
			}
		}
		else{
			cout << "invalid command" << endl;
		}		
	}
	
	
	
}  