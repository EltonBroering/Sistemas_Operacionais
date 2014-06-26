#include <iostream>
//#include "thread.h"
#include "semaphore.h"
#include <BOOOS.h>

using namespace std;
using namespace BOOOS;


const int DELAY = 1000000;
const int REP = 5;

Semaphore empty(1);
Semaphore full(0);

Task * prod, *cons;

  void producer(void * n)
  {
	cout << "Producer was born!\n";
	int i;
      for(i = 0; i < REP; i++) { // 2

	    cout << "Tentando produzir ...\n";// verifica se pode produzir
	    empty.p(); // verifica se o buffer esta vazio para poder produzir
	    Task::self()->sleep(DELAY);
	    cout << "Produzido!!\n";
	    full.v(); // sinaliza que foi produzido(tem algo no buffer)
	    Task::self()->sleep(DELAY);

      }

	Task::self()->exit(i);
  }

  void consumer(void * n)
  {
	cout << "Consumer was born!\n";
	int i;
	for( i = 0; i < REP; i++) { // 1

	    cout << "Tentando consumir ...\n";
	    full.p(); // verifica se há elementos no buffer-> verifica p para ver se pode consumir(se p!=0)
	    Task::self()->sleep(DELAY);
	    cout << "Consumido!!\n";
	    empty.v();//esvazia o buffer (v)
	    Task::self()->sleep(DELAY);
	}

	Task::self()->exit(i);
   }

  int main()
  {

	BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_PRIORITY;
	BOOOS_Configuration::SCHEDULER_PREEMPT = true;
	BOOOS_Configuration::SCHEDULER_AGING = true;
	BOOOS::init();

	cout << "Main Start" << endl;

	cout << "The Producer x Consumer Problem\n";


	prod = new Task (producer,1, (int *)1);
	cons = new Task (consumer,1, (int*)1);

	int status = Task::self()->join(cons);

	if(status == REP)
      cout << "Producer went to heaven!\n";
	else
      cout << "Producer went to hell!\n";

	//Task::self()->join(prod);

	if(status == REP)
      cout << "Consumer went to heaven!\n";
	else
      cout << "Consumer went to hell!\n";

      //cout << Scheduler::cont_notify;

	return 0;
  }
