#include <string>
#include <iostream>

#include "board.h"
#include "textDisplay.h"
#include "humanPlayer.h"
#include "computerPlayer.h"
#include "position.h"

using namespace std;

int main(){
	
	while(true){
		
		string command;
		cin >> command;
				
		if(command == "game"){
			
			Board *b = new Board();
						
			TextDisplay display;
			
			HumanPlayer* white_player_h = nullptr;	
			HumanPlayer* black_player_h = nullptr;
			ComputerPlayer* white_player_c = nullptr;	
			ComputerPlayer* black_player_c = nullptr;
			
			string white_p;
			string black_p;
			
			cin >> white_p;
			cin >> black_p;
						
			if(white_p == "human"){
				white_player_h = new HumanPlayer(true, b);
			}
			else if(white_p == "computer[1]"){
				white_p == "computer";
				white_player_c = new ComputerPlayer(true, b, 1);
			}
					
			if(black_p == "human"){
				black_player_h = new HumanPlayer(false, b);
			}
			else if(black_p == "computer[1]"){
				black_p == "computer";
				black_player_c = new ComputerPlayer(false, b, 1);
			}
		
			//start the game
			cout << "game started enter setup type" << endl;
			while(true){
			
				string setup_type;
				cin >> setup_type;
			
				if(setup_type == "default"){
					b->originalSetup();
				}
				else if(setup_type == "setup"){//ENTER SETUP MODE
					display.print(b);
					while(true){// CODE FOR SETUP MODE HERE, READ COMMANDS AND PASS THEM TO THE BOARD
						
						string setup_type;
						cin >> setup_type;
						
						if(setup_type == "+"){
							string piece_type;	
							string position;
							cin >> piece_type;
							cin >> position;
							
							int y = 8 - (position[1] - '0');
							int x = position[0] - 'a';
							
							Position pos(x, y);							
							
							b->addPieceSetup(piece_type, pos);							
							display.print(b);
						}
						else if(setup_type == "-"){
							string position;
							cin >> position;
							
							int y = 8 - (position[1] - '0');
							int x = position[0] - 'a';
							
							Position pos(x, y);							
							
							b->removePieceSetup(pos);
							display.print(b);							
						}
						else if(setup_type == "="){
							string color;
							cin >> color;
							
							if(color == "white"){
								b->setTurn(true);
							}else if(color == "black"){
								b->setTurn(false);						
							}							
						}
						else if(setup_type == "done"){
							if(b->validSetup()){
								break;
							}else{
								cout << "This is an invalid board" << endl;
							}
						}
					}
				}
							
				while(true){// first to move is white
		
					display.print(b);
					b->setTurn(true);
					
					if(white_p == "human"){//if the white player is a human
						string result;
						
						while(true){
							
							string read_move;
							cin.ignore();
							getline(cin, read_move);//read the desired input for the user
							
							//parse the input
							string delimiter = " ";
							size_t pos = read_move.find(delimiter);
							string command = read_move.substr(0, pos);
							read_move.erase(0, pos + delimiter.length());
							
							if(command == "resign" && black_p == "human"){
								black_player_h->setScore(black_player_h->getScore() + 1);
								cout << "Black wins!" << endl;
								break;//end the game			
							}else if(command == "resign" && black_p == "computer"){
								black_player_c->setScore(black_player_c->getScore() + 1);
								cout << "Black wins!" << endl;
								break;//end the game									
							}
							
							pos = read_move.find(delimiter);
							string position = read_move.substr(0, pos);
							read_move.erase(0, pos + delimiter.length());
							
							int y = 8 - (position[1] - '0');
							int x = position[0] - 'a';
							
							Position start(x, y);		
							string promote = "";
							Position end(0, 0);
							if((pos = read_move.find(delimiter)) != std::string::npos){//there is a pawn promotion
								position = read_move.substr(0, pos);
								read_move.erase(0, pos + delimiter.length());
								
								end.setY(8 - (position[1] - '0'));
								end.setX(position[0] - 'a');
								promote = read_move;								
							}else{
								end.setY(8 - (read_move[1] - '0'));
								end.setX(read_move[0] - 'a');
							}
							
							//try to make the move, see what the makeMove function returns
							result = white_player_h->makeMove(start, end, promote);
							
							cout << "start:" << start.getX() << ", " << start.getY() << endl;
							cout << "end:" << end.getX() << ", " << end.getY() << endl;
							
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
							white_player_h->setScore(white_player_h->getScore() + 1);
							cout << "White wins!" << endl;
							break;//end the game
						} 
						else if(result == "stalemate" && black_p == "human"){
							white_player_h->setScore(white_player_h->getScore() + 0.5);
							black_player_h->setScore(black_player_h->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game			
						}else if(result == "stalemate" && black_p == "computer"){
							white_player_h->setScore(white_player_h->getScore() + 0.5);
							black_player_c->setScore(black_player_c->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game			
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! Black turn next:" << endl;
						}
												
					}else if(white_p == "computer"){
						
						string result = white_player_c->move();	
						
						if(result == "black checkmate"){
							white_player_c->setScore(white_player_c->getScore() + 1);
							cout << "White wins!" << endl;
							break;//end the game	
						} 
						else if(result == "stalemate" && black_p == "human"){
							white_player_c->setScore(white_player_c->getScore() + 0.5);
							black_player_h->setScore(black_player_h->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game					
						}else if(result == "stalemate" && black_p == "computer"){
							white_player_c->setScore(white_player_c->getScore() + 0.5);
							black_player_c->setScore(black_player_c->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game					
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! Black turn next:" << endl;
						}
					}//THIS CONCLUDES WHITES TURN
									
					display.print(b);
					b->setTurn(false);
					
					if(black_p == "human"){//if the black player is a human
						string result;
						
						while(true){
						
							string read_move;
							cin.ignore();
							getline(cin, read_move);//read the desired input for the user
						
							//parse the input
							string delimiter = " ";
							size_t pos = read_move.find(delimiter);
							string command = read_move.substr(0, pos);
							read_move.erase(0, pos + delimiter.length());
							
							if(command == "resign" && white_p == "human"){
								white_player_h->setScore(white_player_h->getScore() + 1);
								cout << "White wins!" << endl;
								break;//end the game			
							}else if(command == "resign" && white_p == "computer"){
								white_player_c->setScore(white_player_c->getScore() + 1);
								cout << "White wins!" << endl;
								break;//end the game									
							}
							
							pos = read_move.find(delimiter);
							string position = read_move.substr(0, pos);
							read_move.erase(0, pos + delimiter.length());
							
							int y = 8 - (int)position[1];
							int x = position[0] - 'a';
							
							Position start(x, y);		
							string promote = "";
							Position end(0, 0);
							
							if((pos = read_move.find(delimiter)) != std::string::npos){//there is a pawn promotion
								position = read_move.substr(0, pos);
								read_move.erase(0, pos + delimiter.length());
								
								end.setY(8 - (int)position[1]);
								end.setY(position[0] - 'a');
								promote = read_move;								
							}else{//no pawn promotion
								end.setY(8 - (int)read_move[1]);
								end.setY(read_move[0] - 'a');
							}
							
							result = black_player_h->makeMove(start, end, promote);
						
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
							black_player_h->setScore(black_player_h->getScore() + 1);
							cout << "Black wins!" << endl;
							break;//end the game	
						} 
						else if(result == "stalemate" && white_p == "human"){
							black_player_h->setScore(black_player_h->getScore() + 0.5);
							white_player_h->setScore(white_player_h->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game			
						}else if(result == "stalemate" && white_p == "computer"){
							black_player_h->setScore(black_player_h->getScore() + 0.5);
							white_player_c->setScore(white_player_c->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game			
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! White turn next:" << endl;
						}
						
					}else if(black_p == "computer"){
						
						string result = black_player_c->move();	
						
						if(result == "white checkmate"){
							black_player_c->setScore(black_player_c->getScore() + 1);
							cout << "Black wins!" << endl;
							break;//end the game	
						} 
						else if(result == "stalemate" && white_p == "human"){
							black_player_c->setScore(black_player_c->getScore() + 0.5);
							white_player_h->setScore(white_player_h->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game					
						}
						else if(result == "stalemate" && white_p == "computer"){
							black_player_c->setScore(black_player_c->getScore() + 0.5);
							white_player_c->setScore(white_player_c->getScore() + 0.5);
							cout << "Stalemate!" << endl;
							break;//end the game					
						}
						else if(result == "sucessful move"){
							cout << "Sucessful move! White turn next:" << endl;
						}						
					}		
				} // EXITING THIS LOOP MEANS THE GAME ENDED
				
				float white_score;
				float black_score;
				
				if(white_p == "human"){
					white_score = white_player_h->getScore();
				}else{
					white_score = white_player_c->getScore();
				}
				
				if(black_p == "human"){
					black_score = black_player_h->getScore();
				}else{
					black_score = black_player_c->getScore();
				}
				
				cout << "Current Score:" << endl;
				cout << "White:" << white_score << endl;
				cout << "Black:" << black_score << endl;
		
				string play_again;
				
				cout << "Play another round?" << endl;
				cin >> play_again;
				
				if(play_again == "no" || play_again == "n"){
					break;
				}
			}
			
			delete b;
		}
		else{
			cout << "invalid command" << endl;
		}		
	}
	
	
	
}  