CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
EXEC = straights
OBJECTS = main.o Deck.o DefaultComputer.o Game.o Human.o Player.o StandardGame.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${DEPENDS} ${OBJECTS} ${EXEC}