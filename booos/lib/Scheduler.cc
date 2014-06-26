/*
 * Scheduler.cpp
 *
 *  Created on: Mar 21, 2014
 *      Author: arliones
 */

#include "Scheduler.h"
#include <ucontext.h>
#include "Queue.h"


namespace BOOOS {


Scheduler * Scheduler::__dispatcher = 0;

/*
 *  The scheduler is an active task that schedules/manages other tasks
 */
Scheduler::Scheduler() : Task::Task(dispatcher,0,0){
	this->_state=SCHEDULER;
	Scheduler::__ready.remove();
}

Scheduler::~Scheduler() {}
/*
 * Initializes Scheduler's static attributes
 */
void Scheduler::init() {
	__dispatcher= new Scheduler();
}

/*
 * This function implements the scheduler behavior.
 */
void Scheduler::dispatcher(void*) {
Task * next;

	while(Scheduler::_Task_Count> 1)
	    {
	       next = self()->choose_next() ;  // escolher a próxima Task* a executar
	       if(next)
	       {
	          //... // ações antes de lancar a tarefa "next", se houverem
	          self()->pass_to(next); // transfere controle para a tarefa "next"
	          //... // ações apos retornar da tarefa "next", se houverem
	       }
	    }
	    self()->exit(0) ; // encerra a tarefa dispatcher

}


Task * Scheduler::choose_next() {

	if(Task::__ready.length()){
	return (Task *)Task::__ready.remove();
	}
	else{
		return 0;
	}
}

void Scheduler::notify_time(Timer::Timestamp ticks){
	if(Task::self()->state()==Task::SCHEDULER){
		return;
	}
	else{
		Task::self()->yield();
	}
}

void Scheduler::pass_to_ready(){
	Task::insert_ready((Task*)Task::__sleeping.remove());
}




} /* namespace BOOOS */
