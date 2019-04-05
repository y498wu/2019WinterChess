CXX=g++
CXXFLAGS=-std=c++14 -g -Wall -Werror=vla
OBJECTS=bishop.o board.o computerPlayer.o humanPlayer.o king.o knight.o main.o pawn.o pieces.o position.o queen.o rook.o textDisplay.o 
EXEC=chess
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: bishop.o board.o computerPlayer.o humanPlayer.o king.o knight.o main.o pawn.o pieces.o position.o queen.o rook.o textDisplay.o 
 g++-5 -std=c++14 *.o -o chess -lX11

-include:${DEPENDS}

.PHONY: clean

clean:
 rm *.o chess

