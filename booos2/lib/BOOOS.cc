/*
 * BOOOS.cc
 *
 *  Created on: Mar 24, 2014
 *      Author: arliones
 */

#include <BOOOS.h>
#include <Task.h>
#include <Scheduler.h>
#include <Timer.h>

namespace BOOOS {

//Scheduler::SchedulerType BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_FCFS;
Scheduler::SchedulerType BOOOS_Configuration::SCHEDULER_TYPE = Scheduler::SCHED_PRIORITY;
bool BOOOS_Configuration::SCHEDULER_PREEMPT = true;
bool BOOOS_Configuration::SCHEDULER_AGING = false;
Timer::Timestamp BOOOS_Configuration::TIMER_RESOLUTION = 1000; // in microseconds / tick
Timer::Timestamp BOOOS_Configuration::SCHEDULER_RESOLUTION = 1; // in ticks / queue check
Timer::Timestamp BOOOS_Configuration::SCHEDULER_QUANTUM = 20; // in ticks / task

void init() {
	Task::init();
	Scheduler::init();
	Timer::init(Scheduler::self(), BOOOS_Configuration::SCHEDULER_QUANTUM);
	if(BOOOS_Configuration::SCHEDULER_PREEMPT)
		Timer::start();
}

} /* namespace BOOOS */
