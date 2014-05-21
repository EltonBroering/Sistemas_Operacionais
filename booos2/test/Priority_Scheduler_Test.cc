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
#include <Task.h>

#define ASSERT(x,y) if(!(x)) return y;

using namespace std;
using namespace BOOOS;

namespace Priority_Scheduler_Test_Functions {

	Task *pang, *peng, *ping, *pong, *pung;



	void function(void * arg) {
		int i;

		for(i=0; i<10; i++) {
			cout << (char*)arg << " " << i << endl;
			Task::self()->nice(2*Task::self()->tid());
			Task::self()->yield();
		}
		cout << (char*)arg << " End" << endl;
		Task::self()->exit(0);
	}

	int test_scheduling_with_aging() {

		BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_PRIORITY;
		BOOOS_Configuration::SCHEDULER_PREEMPT = false;
		BOOOS_Configuration::SCHEDULER_AGING = true;
		BOOOS::init();

		cout << "Main Start" << endl;

		pang = new Task(function, 1, (char*)"\tPang");
		peng = new Task(function, 1, (char*)"\t\tPeng");
		ping = new Task(function, 1, (char*)"\t\t\tPing");
		pong = new Task(function, 1, (char*)"\t\t\t\tPong");
		pung = new Task(function, 1, (char*)"\t\t\t\t\tPung");

		while(Task::count() > 2) {
			Task::self()->nice(20);
			Task::self()->yield();
		}

		cout << "Main End" << endl;

		return 0;
	}

	int test_scheduling_without_aging() {

		BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_PRIORITY;
		BOOOS_Configuration::SCHEDULER_PREEMPT = false;
		BOOOS_Configuration::SCHEDULER_AGING = false;
		BOOOS::init();

		cout << "Main Start" << endl;

		pang = new Task(function, 1, (char*)"\tPang");
		peng = new Task(function, 1, (char*)"\t\tPeng");
		ping = new Task(function, 1, (char*)"\t\t\tPing");
		pong = new Task(function, 1, (char*)"\t\t\t\tPong");
		pung = new Task(function, 1, (char*)"\t\t\t\t\tPung");

		while(Task::count() > 2) {
			Task::self()->nice(20);
			Task::self()->yield();
		}

		cout << "Main End" << endl;

		return 0;
	}
}

int main() {
	cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << endl;
	cout << "This program will test the class: Priority_Scheduler" << endl;

	cout << Priority_Scheduler_Test_Functions::test_scheduling_without_aging() << endl;

//	cout << Priority_Scheduler_Test_Functions::test_scheduling_with_aging() << endl;

	return 0;
}
