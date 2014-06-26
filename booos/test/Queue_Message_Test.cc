/*
 * Semaphore_Test.cc
 *
 *  Created on: Jun 01, 2014
 *      Author: arliones
 */

#include <BOOOS.h>
#include <Task.h>
#include <Message_Queue.h>

#include <iostream>

using namespace std;
using namespace BOOOS;

Message_Queue queue;

static const int repetitions = 10;

void producer(void *)
{
    cout << "Producer was born!" << endl;

    Task * myself = Task::self();

    char msg[26] = "This is message number 0.";

    for(int i = 0; i < repetitions; i++) {
        msg[23] = 0x30 + i;
        Message_Queue::Message qmsg(msg);
        queue.send(qmsg);
        myself->sleep(25000);
    }

    myself->exit(repetitions);
}

void consumer(void *)
{
    cout << "Consumer was born!" << endl;

    Task * myself = Task::self();

    for(int i = 0; i < repetitions; i++) {
        cout << queue.receive().get() << endl;
    }

    myself->exit(repetitions);
}

int main()
{
    cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << endl;
    cout << "This program will test the class: Semaphore" << endl;

    BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_FCFS;
    BOOOS_Configuration::SCHEDULER_PREEMPT = true;
    BOOOS_Configuration::SCHEDULER_AGING = true;
    BOOOS::init();

    Task * myself = Task::self();

    Task* prod = new Task(producer,1,(char*)"produtor");
   	Task* cons = new Task(consumer, 1,(char*)"consumidor");

    myself->join(prod);
    myself->join(cons);

    myself->exit(0);

    return 0;
}
