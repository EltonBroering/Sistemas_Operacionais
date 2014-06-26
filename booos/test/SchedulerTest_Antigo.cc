/*
 * Queue_Test.cc
 *
 *  Created on: Feb 21, 2014
 *      Author: arliones
 */

#include <iostream>
#include <queue>
#include <sstream>
#include <BOOOS.h>
#include <Scheduler.h>

using namespace std;
using namespace BOOOS;

namespace Scheduler_Test_Functions {

	void philosopher(void * arg) {
		int i;

		for(i=0; i<4; i++) {
			cout << (char*)arg << " " << i << endl;
			Task::self()->yield();
		}
		cout << (char*)arg << " End" << endl;
		Task::self()->exit(0);
	}

	int test_philosophers_dinner() {

		cout << "Main Start" << endl;

		Task pang(philosopher, 1, (char*)"\tPang");
		Task peng(philosopher, 1, (char*)"\t\tPeng");
		Task ping(philosopher, 1, (char*)"\t\t\tPing");
		Task pong(philosopher, 1, (char*)"\t\t\t\tPong");
		Task pung(philosopher, 1, (char*)"\t\t\t\t\tPung");
		while(Task::count() > 2)
			Task::self()->yield();

		cout << "Main End" << endl;

		return 0;
	}
}

int main() {
	cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << endl;
	cout << "This program will test the class: Scheduler" << endl;

	BOOOS::init();
	Scheduler_Test_Functions::test_philosophers_dinner();

	return 0;
}
