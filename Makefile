CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g
OBJECTS = main.o cell.o block.o board.o level.o view.o textdisplay.o graphicsdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}
-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


