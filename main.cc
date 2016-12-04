#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

#include "controller.h"

int main (int argc, char *argv[]) {
	Controller c;
	if (argv.length > 1){
		if (argv[i] == "-text"){
			c.textMode();
		}
		else if	(argv[i] == "-seed"){
			c.seed(argv[++i]);
		}
	    else if (argv[i] == "-scriptfile"){
			c.scriptfile(argv[++i]);
		}
	    else if (argv[i] == "-startlevel"){
			c.setLevel(argv[++i]);
		}
		else if{
			cerr << "Invalid Command" << endl;
			break;		
		}
	}
	c.play();
}
