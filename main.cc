#include "cell.h"
#include "block.h"
#include "board.h"
#include "level.h"
#include "view.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

int main() {
//	Xwindow x;
	//auto gd = make_shared<GraphicsDisplay>(x);
	auto td = make_shared<TextDisplay>();
	Board b{};
	b.attachView(td);
	b.setLevel(2);
	b.createBlock();
	cout << *td;

	string cmd;
	while (cin >> cmd) {
		if (cmd == "moveR") b.moveRight();
		if (cmd == "moveL") b.moveLeft();
		if (cmd == "rotateCW") b.rotateCW();
		if (cmd == "rotateCC") b.rotateCC();
		if (cmd == "moveD") b.moveDown();
		if (cmd == "drop") {
			b.drop();
			b.createBlock();
		}
		cout << *td;
	}
}
