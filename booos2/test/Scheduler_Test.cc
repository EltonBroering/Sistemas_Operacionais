/*
 * Queue_Test.cc
 *
 *  Created on: Feb 21, 2014
 *      Author: arliones
 */

#include <iostream>
#include <queue>
#include <sstream>
#include "BOOOS.h"
#include <Scheduler.h>

#define ASSERT(x,y) if(!(x)) return y;

using namespace std;
using namespace BOOOS;

int test_init() {
	BOOOS::init();

	ASSERT(Scheduler::self()->tid() == 1, 1);
	ASSERT(Scheduler::self()->state() == Task::SCHEDULER, 2);

	//Scheduler::init(); // should execute only once!
	ASSERT(Scheduler::self()->tid() == 1, 3);
	ASSERT(Scheduler::self()->state() == Task::SCHEDULER, 4);

	return 0;
}

void f1(void* a) {}
void f2(void* a) {}
void f3(void* a) {}
void f4(void* a) {}

int test_creation_destruction() { // will add to Scheduler

	BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_FCFS;
	BOOOS_Configuration::SCHEDULER_PREEMPT = false;
	BOOOS_Configuration::SCHEDULER_AGING = false;
	BOOOS::init();

	Task t1(f1, 1, (void*)"f1"), t2(f2, 1, (void*)"f2");
	Task * t3 = new Task(f3, 1, (void*)"f3");
	Task * t4 = new Task(f4, 1, (void*)"f4");

	ASSERT(t1.tid() == 2, 1);
	ASSERT(t1.state() == Task::READY, 2);
	ASSERT(t2.tid() == 3, 3);
	ASSERT(t2.state() == Task::READY, 4);
	ASSERT(t3->tid() == 4, 5);
	ASSERT(t3->state() == Task::READY, 6);
	ASSERT(t4->tid() == 5, 7);
	ASSERT(t4->state() == Task::READY, 8);

	delete t3,t4;

	return 0;
}

Task *pang, *peng, *ping, *pong, *pung;

void function(void * arg) {
	int i;

	for(i=0; i<4; i++) {
		cout << (char*)arg << " " << i << endl;
		Task::self()->yield();
	}
	cout << (char*)arg << " End" << endl;
	Task::self()->exit(0);
}

int test_scheduling() {

	BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_FCFS;
	BOOOS_Configuration::SCHEDULER_PREEMPT = false;
	BOOOS_Configuration::SCHEDULER_AGING = false;
	BOOOS::init();

	cout << "Main Start" << endl;

	pang = new Task(function, 1, (char*)"\tPang");
	peng = new Task(function, 1, (char*)"\t\tPeng");
	ping = new Task(function, 1, (char*)"\t\t\tPing");
	pong = new Task(function, 1, (char*)"\t\t\t\tPong");
	pung = new Task(function, 1, (char*)"\t\t\t\t\tPung");

	while(Task::count() > 2)
		Task::self()->yield();

	cout << "Main End" << endl;

	return 0;
}

int main() {
	cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << endl;
	cout << "This program will test the class: Scheduler" << endl;

    cout << "Init: " << test_init() << endl;
    cout << "Creation and Destruction: " << test_creation_destruction() << endl;
    cout << "FCFS: " << test_scheduling() << endl;

	return 0;
}
