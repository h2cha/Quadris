#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "controller.h"

int main (int argc, char *argv[]) {
	Controller c;
	if (argc > 1){
		if (string(argv[1]) == "-text"){
			c.textMode();
		}
		else if	(string(argv[1]) == "-seed"){
			c.setSeed(string(argv[2]));
		}
	    else if (string(argv[1]) == "-scriptfile"){
			c.scriptfile(string(argv[2]));
		}
	    else if (string(argv[1]) == "-startlevel"){
			c.startlevel(string(argv[2]));
		}
		else{
			cerr << "Invalid Command" << endl;
		}
	}
	c.play();
}
