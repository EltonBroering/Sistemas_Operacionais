/*
 * Timer.cc
 *
 *  Created on: Mar 30, 2014
 *      Author: arliones
 */

#include <Timer.h>
#include <BOOOS.h>
#include <Scheduler.h>
#include <sys/time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

namespace BOOOS {

Timer::Timestamp Timer::__ticks = 0;
itimerval Timer::__timer;
struct sigaction Timer::__action;
Scheduler * Timer::__scheduler;
Timer::Timestamp Timer::__period;

/*
 * Initializes the timer
 */
void Timer::init(Scheduler * sched, Timestamp period) {

	__scheduler = sched;
	__period = period;
	__ticks = 0;

	cout << "Timer inicializado" << endl;
	__timer.it_interval.tv_usec=BOOOS_Configuration::TIMER_RESOLUTION;
	__timer.it_value.tv_usec=BOOOS_Configuration::TIMER_RESOLUTION;

	__action.sa_handler=sig_handler;
	sigemptyset (&__action.sa_mask);
	__action.sa_flags=0;

	if (sigaction (SIGALRM, &__action, 0) < 0)
	   {
	      cerr << ("Erro em sigaction: ") << endl;
	      exit (1) ;
	   }

}

// Start counting time...
void Timer::start() {


	// arma o temporizador ITIMER_REAL (vide man setitimer)
	if (setitimer (ITIMER_REAL, &__timer, 0) < 0){
		cerr << "01: invalid Element" << endl;
		exit (1);
	}
	;
}

// Count ticks. Notify Scheduler if period is reached
void Timer::sig_handler(int signum) {
	__ticks++;

	if((__ticks % __period) == 0)
		__scheduler->notify_time(__ticks);
}

Timer::Timestamp Timer::ticks() { return __ticks; }
Timer::Timestamp Timer::time() { return __ticks * BOOOS_Configuration::TIMER_RESOLUTION; }

void Timer::delay_ticks(Timer::Timestamp t) {
	Timestamp start = ticks();
	while(ticks() - start <= t);
}

void Timer::delay(Timer::Timestamp t) {
	Timestamp start = time();
	while(time() - start <= t);
}

}
