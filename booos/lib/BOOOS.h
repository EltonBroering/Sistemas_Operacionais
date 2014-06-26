/*
 * BOOOS.h
 *
 *  Created on: Mar 24, 2014
 *      Author: arliones
 */

#ifndef BOOOS_H_
#define BOOOS_H_

#include <Scheduler.h>
#include <Timer.h>
#include <Semaphore.h>

namespace BOOOS {

/* Configuration Space */
class BOOOS_Configuration {
public:
	static Scheduler::SchedulerType SCHEDULER_TYPE;  //mode of scheduler
	static bool SCHEDULER_PREEMPT;  //scheduler preempt mode
	static bool SCHEDULER_AGING;
	static Timer::Timestamp TIMER_RESOLUTION; // in microseconds / tick
	static Timer::Timestamp SCHEDULER_RESOLUTION; // in ticks / queue check
	static Timer::Timestamp SCHEDULER_QUANTUM; // in ticks / task
	static const int MESSAGE_SIZE=100;
};

void init();

} /* namespace BOOOS */

#endif /* BOOOS_H_ */
