//============================================================================
// Name        : booos.cc
// Author      : Arliones Hoeller
// Version     :
// Copyright   : Santa Catarina Federal Institute of Technology - 2014
// Description : BOOOS Application
//============================================================================

#include <iostream>
#include <BOOOS.h>

using namespace std;

int main() {
	cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << endl;

	BOOOS::init();

	while(true);

	return 0;
}
