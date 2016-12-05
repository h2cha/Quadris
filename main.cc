#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "controller.h"

int main (int argc, char *argv[]) {
	Controller c;
	c.play(argc,argv);
}
