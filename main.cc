#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "controller.h"

int main (int argc, char *argv[]) {
	Controller c;
	for (int i = 1; i < argc; i++){
		if (string(argv[i]) == "-text"){
			c.textMode();
		}
		else if	(string(argv[i]) == "-seed"){
			c.setSeed(string(argv[++i]));
		}
	    else if (string(argv[i]) == "-scriptfile"){
			c.scriptfile(string(argv[++i]));
		}
	    else if (string(argv[i]) == "-startlevel"){
			c.startlevel(string(argv[++i]));
		}
		else{
			cerr << "Invalid Command" << endl;
		}
	}
	c.play();
}
