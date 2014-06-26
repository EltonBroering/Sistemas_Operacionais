#include <iostream>
#include <Task.h>
#include <BOOOS.h>
#include <Semaphore.h>


using namespace std;
using namespace BOOOS;

const int DELAY = 100000;
const int REP = 5;

Semaphore * empty = new Semaphore(1);
Semaphore * full = new Semaphore(0);

void producer(void * n) {
	cout << "Producer was born!\n";

	// Faltam, no laço abaixo:
	//  - uma chamada para empty.p()
	//  - uma chamada para full.v()
	empty->p();
	int i;
	for (i = 0; i < REP; i++) {
		cout << "Producing ...\n";
		Task::self()->sleep(DELAY);
		cout << "Storing ...\n";
		Task::self()->sleep(DELAY);
	}
	full->v();
	Task::self()->exit(i);

}

void consumer(void * n) {
	cout << "Consumer was born!\n";

	// Faltam, no laço abaixo:
	//  - uma chamada para full.p()
	//  - uma chamada para empty.v()
	full->p();
	int i;
	for (i = 0; i < REP; i++) {
		cout << "Retrieving ...\n";
		Task::self()->sleep(DELAY);
		cout << "Consuming ...\n";
		Task::self()->sleep(DELAY);
	}
	empty->v();
	Task::self()->exit(i);

}

int main() {

	BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_PRIORITY;
	BOOOS_Configuration::SCHEDULER_PREEMPT = true;
	BOOOS_Configuration::SCHEDULER_AGING = true;
	BOOOS::init();

	cout << "Main Start" << endl;

	cout << "The Producer x Consumer Problem\n";

	Task* prod = new Task(producer,1,(char*)"produtor");
	Task* cons = new Task(consumer, 1,(char*)"consumidor");

	Task * Main = Task::self();

	int status;
	status=Main->join(prod);
	if (status == REP)
		cout << "Producer went to heaven!\n";
	else
		cout << "Producer went to hell!\n";

	status=Main->join(cons);
	if (status == REP)
		cout << "Consumer went to heaven!\n";
	else
		cout << "Consumer went to hell!\n";

	cout << "Main End" << endl;
	Main->exit(0);

	return 0;

}
