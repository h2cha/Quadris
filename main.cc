#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "controller.h"

int main (int argc, char *argv[]) {
	Controller c;
	if (argv.length() > 1){
		if (str(argv[1]) == "-text"){
			c.textMode();
		}
		else if	(str(argv[1]) == "-seed"){
			c.setSeed(str(argv[2]));
		}
	    else if (str(argv[1]) == "-scriptfile"){
			c.scriptfile(str(argv[2]));
		}
	    else if (str(argv[1]) == "-startlevel"){
			c.startLevel(str(argv[2]));
		}
		else{
			cerr << "Invalid Command" << endl;
			break;		
		}
	}
	c.play();
}
