#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "controller.h"

int main (int argc, char *argv[]) {
	Controller c;
	if (argv.length() > 1){
		if (argv[1] == "-text"){
			c.textMode();
		}
		else if	(argv[1] == "-seed"){
			c.setSeed(argv[++i]);
		}
	    else if (argv[1] == "-scriptfile"){
			c.scriptfile(argv[++i]);
		}
	    else if (argv[1] == "-startlevel"){
			c.startLevel(argv[++i]);
		}
		else if{
			cerr << "Invalid Command" << endl;
			break;		
		}
	}
	c.play();
}
