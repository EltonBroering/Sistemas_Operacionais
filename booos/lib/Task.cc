/*
 * Task.cc
 *
 *  Created on: Feb 27, 2014
 *      Author: arliones
 */

#include "Task.h"
#include "BOOOS.h"
#include <stdio.h>
#include <ucontext.h>
#include <stdlib.h>
#include <Scheduler.h>
#include <iostream>

using namespace std;

#define STACKSIZE 32768		/* tamanho de pilha das threads */

namespace BOOOS {

volatile Task * Task::__running;
Task * Task::_tMain;
Queue Task::__ready;
Queue Task::__sleeping;
int Task::_tid_counter;
int Task::_Task_Count;

// This method initializes Task's global attributes
void Task::init() {

	Task::_tMain = new Task();
	getcontext(&Task::_tMain->_cTask);
	Task::__running = Task::_tMain;
	//_state é private//
	Task::_tMain->_state = RUNNING;
	Task::_tid_counter = 0;
	Task::_tMain->_tid = _tid_counter;
	Task::_tid_counter++;
	Task::_Task_Count++;
	_tMain->__actn = 1;
	_tMain->__time_exec = 0;
	_tMain->__time_init = Timer::time();

}

// This constructor creates a task.
// - entry_point: pointer to a function that implements the behavior of the task
// - nargs: number of arguments sent to the entry_point function
// - arg: vector with the arguments for the entry_point function
Task::Task(void (*entry_point)(void *), int nargs, void * arg) {

	getcontext(&this->_cTask);
	_state = READY;
	char *stack = (char*) malloc(STACKSIZE);
	if (stack) {
		_cTask.uc_stack.ss_sp = stack;
		_cTask.uc_stack.ss_size = STACKSIZE;
		_cTask.uc_stack.ss_flags = 0;
		_cTask.uc_link = 0;
		this->__actn = 0;
		this->__time_exec = 0;
		this->__time_init = Timer::time();

	} else {
		perror("Erro na criação da pilha: ");
		exit(1);
	}
	makecontext(&_cTask, (void (*)()) entry_point, nargs,arg);
	this->_tid = _tid_counter;
	_tid_counter++;
	if (BOOOS_Configuration::SCHEDULER_TYPE == Scheduler::SCHED_FCFS) {
		Task::__ready.insert(this);

	} else {
		if (BOOOS_Configuration::SCHEDULER_TYPE == Scheduler::SCHED_PRIORITY) {
			Task::__ready.insert_ordered(this);
		}
	}
	Task::_Task_Count++;
	return;

}

//construtor específico para o main
Task::Task() {

}

// This destructor destroys/frees any resources allocated in the constructor
Task::~Task() {
	if (this->_state != Scheduler::FINISHING) {
		Task::exit(0);
	}

	free(this->_cTask.uc_stack.ss_sp);

}

// This method transfers the execution flow from the current task to the Task 't'.
// - t: pointer to the task that will assume the CPU.
// - s: state that the current task will assume
void Task::pass_to(Task * t, State s) {

	this->__time_exec += Timer::time() - this->t1;
	if (this->_state != Task::SCHEDULER) {
		this->_state = s;
	}
	Task::__running = t;
	if (t->_state != Task::SCHEDULER) {
		t->_state = RUNNING;
	}
	if (this->_state == READY) {

		this->insert_ready(this);
	}
	if (this->_state == SLEEPING) {
		Task::__sleeping.insert_ordered_time(this);
	}

	t->__actn++;
	t->t1 = Timer::time();

	if (this->state() == Scheduler::FINISHING) {
		Task::_Task_Count--;
		cout << "Task " << this->_tid << " exit: response time "
				<< (Timer::time() - this->__time_init) / 1000
				<< " ms, CPU time " << this->__time_exec / 1000 << " ms, "
				<< this->__actn << " activations" << endl;
	}
	swapcontext(&this->_cTask, &t->_cTask);

}

//finaliza a Task (this) e configura o valor de resultado da task com o valor de code.
//Por enquanto, se preocupem em fazer a Task retornar a execução para a main.
//Ignorem o parâmetro code agora - utilizaremos ele mais adiante.

// This method finalizes a task
// - code: exit/error code.
void Task::exit(int code) {
	this->cod_end = code;
	while (this->__pending.length()) {
		Task* aux = (Task*) this->__pending.remove();
		aux->_state = READY;
		this->insert_ready(aux);

	}
	pass_to(Scheduler::self(), FINISHING);
}

//transfere a execução da tarega corrente para o escalonador
void Task::yield() {
	this->pass_to(Scheduler::self());

}

void Task::nice(int p) {
	if (p > -21 and p < 21) {
		rank(p);
	} else {
		cerr << "Invalid Priority" << endl;
	}
}
void Task::print_queue(Queue & q) {
	cout << "Queue length: " << q.length() << endl;

	if (q.length()) {
		Task * elem = dynamic_cast<Task *>(q.head()->next());
		do {
			cout << elem->tid() << endl;
			elem = dynamic_cast<Task *>(elem->next());
		} while (elem != q.head()->next());
	}

	cout << "==============================" << endl;
}

int Task::join(Task * t) {
	if (t == 0) {
		return -1;
	}
	if (t->_state != FINISHING) {
		t->wait_you(this);
		this->pass_to(Scheduler::self(), WAITING);
	}
	return t->cod_end;

}

void Task::wait_you(Task * t) {
	this->__pending.insert(t);
	return;
}

//Metodo sleep, deixa a tarefa dormindo por um intervalo de tempo, o parametro é em microsegundos
void Task::sleep(int t) {

	if((t%BOOOS_Configuration::TIMER_RESOLUTION)==0){
		t=t/BOOOS_Configuration::TIMER_RESOLUTION;
	}else{
		t=(t/BOOOS_Configuration::TIMER_RESOLUTION)+1;
	}
	this->time_sleep(t+ Timer::time());
	this->pass_to(Scheduler::self(), SLEEPING);

}

//Função que insere Tasks na fila de ready
void Task::insert_ready(Task * task) {
	if (BOOOS_Configuration::SCHEDULER_TYPE == Scheduler::SCHED_FCFS) {
		Task::__ready.insert(task);
	} else if (BOOOS_Configuration::SCHEDULER_TYPE
			== Scheduler::SCHED_PRIORITY) {
		Task::__ready.insert_ordered(task);
	}
}

}

/* namespace BOOOS */
