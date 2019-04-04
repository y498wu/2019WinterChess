#include <string>
#include <iostream>

using namespace std;

int main(){
	
	while(true){
		
		string command;
		cin >> command;
		
		if(command == "game"){
			Board *b = new Board();
			
			string white_player;
			string black_player;
			
			cin >> white_player;
			cin >> black_player;
						
			if(white_player == "human"){
				Human white_p = new Human(true, b);
			}
			else if(white_player == "computer[1]"){
				white_player == "computer"
				Computer white_p = new Computer(true, b, 1);
			}
					
			if(black_player == human){
				Human black_p = new Human(false, b);
			}
			else if(black_player == "computer[1]"){
				black_player == "computer"
				Computer black_p = new Computer(false, b, 1);
			}
		
			//start the game
			
			while(true){
			
				string setup_type;
				cin >> setup_type;
			
				if(setup_type == "default"){
					b->originalSetup();
				}
				else if(setup_type == "setup"){//ENTER SETUP MODE
					while(){// CODE FOR SETUP MODE HERE, READ COMMANDS AND PASS THEM TO THE BOARD
					
					
					
					}
				}
							
				textDisplay display();	
				while(true){// first to move is white
								
					display.print(b);
					b->setTurn(true);
					
					if(white_player == "human"){//if the white player is a human
						string result;
						
						while(true){
						
							string read_move;
							cin >> read_move;//read the desired input for the user
						
							//parse the input
							Position start = 
							Position end =
							string promote =
							
							//try to make the move, see what the makeMove function returns
							result = white_player.makeMove(start, end, promote);
						
							if(result == "invalid input"){
								cout << "This position is out of bound, try again:" << endl;
							}else if(result == "no piece"){
								cout << "There is no piece at this position, try again:" << endl;
							}else if(result == "wrong color"){
								cout << "This is not your piece, try again:" << endl;
							}else if(result == "not legal"){
								cout << "That is not a legal move for this piece, try again:" << endl;
							}else if(result == "still in check"){
								cout << "Your king is still in check! Try again:" << endl;
							}else{//if the input is valid you can continue, otherwise keep looping
								break;
							}
						}
						
						if(result == "black checkmate"){
							white_player.setScore(white_player.getScore() + 1);
							cout << "White wins!" << endl;
							break;//end the game
						} 
						else if(result == "stalemate"){
							white_player.setScore(white_player.getScore() + 0.5);
							black_player.setScore(black_player.getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game			
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! Black turn next:" << endl;
						}
												
					}else if(white_player == "computer"){
						
						string result = white_player.move();	
						
						if(result == "black checkmate"){
							white_player.setScore(white_player.getScore() + 1);
							cout << "White wins!" << endl;
							break;//end the game	
						} 
						else if(result == "stalemate"){
							white_player.setScore(white_player.getScore() + 0.5);
							black_player.setScore(black_player.getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game					
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! Black turn next:" << endl;
						}
					}//THIS CONCLUDES WHITES TURN
									
					display.print(b);
					b->setTurn(false);
					
					if(black_player == "human"){//if the black player is a human
						string result;
						
						while(true){
						
							string read_move;
							cin >> read_move;
						
							//parse the input
							Position start = 
							Position end =
							string promote =
							
							result = black_player.makeMove(start, end, promote);
						
							if(result == "invalid input"){
								cout << "This position is out of bound, try again:" << endl;
							}else if(result == "no piece"){
								cout << "There is no piece at this position, try again:" << endl;
							}else if(result == "wrong color"){
								cout << "This is not your piece, try again:" << endl;
							}else if(result == "not legal"){
								cout << "That is not a legal move for this piece, try again:" << endl;
							}else if(result == "still in check"){
								cout << "Your king is still in check! Try again:" << endl;
							}else{
								break;
							}
						}
						
						if(result == "white checkmate"){
							black_player.setScore(black_player.getScore() + 1);
							cout << "Black wins!" << endl;
							break;//end the game	
						} 
						else if(result == "stalemate"){
							black_player.setScore(black_player.getScore() + 0.5);
							white_player.setScore(white_player.getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game						
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! White turn next:" << endl;
						}
						
					}else if(black_player == "computer"){
						
						string result = black_player.move();	
						
						if(result == "white checkmate"){
							black_player.setScore(black_player.getScore() + 1);
							cout << "Black wins!" << endl;
							break;//end the game	
						} 
						else if(result == "stalemate"){
							black_player.setScore(black_player.getScore() + 0.5);
							white_player.setScore(white_player.getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game						
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! White turn next:" << endl;
						}
					}		
				} // EXITING THIS LOOP MEANS THE GAME ENDED
			
				cout << Current Score: << endl;
				cout << White: << white_player.getScore() << end;
				cout << Black: << black_player.getScore() << end;
				
				string play_again;
				
				cout << "Play another round?" << endl;
				cin >> play_again;
				
				if(play_again == "no" || play_again == "n"){
					break;
				}				
			}
		}
		else{
			cout << "invalid command" << endl;
		}		
	}
	
	
	
}  