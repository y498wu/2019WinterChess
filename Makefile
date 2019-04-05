CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror=vla -g
EXEC = chess
OBJECTS = main.o position.o pieces.o bishop.o king.o knight.o pawn.o queen.o rook.o textDisplay.o computerPlayer.o humanPlayer.o board.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
