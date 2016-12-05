CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g
OBJECTS = main.o cell.o block.o block_i.o block_j.o block_l.o block_o.o block_z.o block_s.o block_t.o block_x.o board.o level.o view.o textdisplay.o graphicsdisplay.o window.o controller.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11
-include ${DEPENDS}

.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}


