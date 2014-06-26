/*
 * Task.h
 *
 *  Created on: Feb 27, 2014
 *      Author: arliones
 */

#ifndef TASK_H_
#define TASK_H_

#include <Queue.h>
#include <ucontext.h>

namespace BOOOS {

class Task : public Queue::Element {
public:
	enum State {
		READY,
		WAITING,
		RUNNING,
		FINISHING,
		SCHEDULER,
		SLEEPING
	};

	Task(void (*entry_point)(void *), int nargs, void * arg);
	virtual ~Task();

	int tid() { return _tid; }
	State state() { return _state; }

	void pass_to(Task * t, State s = READY);
	void yield();

	void nice(int p);

	void exit(int code);

	void print_queue(Queue & q);

	static int _tid_counter;
	static Task * self() { return (Task*)__running; }
	static void init();
	static int count() {return Task::_Task_Count;}
	int join(Task * t);
	void wait_you(Task * t);
	int cod_end;
	void sleep(int t);
	void insert_ready(Task * task);


protected: // These are used by friend class Scheduler
	static Queue __ready;
	static Queue __sleeping;
	State _state;
	static int _Task_Count;


private:
	//construtor especifico para uso do main
	Task();
	static volatile Task * __running;
	Queue __pending;
	int _tid; // task ID
	ucontext _cTask;
	static Task * _tMain;
	int __time_init;
	int __actn;
	int __time_exec;
	int t1;

	// ...
};

} /* namespace BOOOS */

#endif /* TASK_H_ */
