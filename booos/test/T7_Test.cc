#include <iostream>
#include <queue>
#include <sstream>
#include <BOOOS.h>
#include <Scheduler.h>

#define ASSERT(x,y) if(!(x)) return y;

using namespace std;
using namespace BOOOS;

Task *pang, *peng, *ping, *pong, *pung;

void function(void * arg) {
	int i;

	Task::self()->nice(2*Task::self()->tid());

	for(i=0; i<10; i++) {
		cout << (char*)arg << " " << i << endl;
		Timer::delay_ticks(25);
	}
	cout << (char*)arg << " End" << endl;
	Task::self()->exit(0);
}

int main() {

	BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_FCFS;
	BOOOS_Configuration::SCHEDULER_PREEMPT = true;
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

	Task::self()->exit(0);

	return 0;
}
