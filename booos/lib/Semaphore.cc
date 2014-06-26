#include "Semaphore.h"
#include "BOOOS.h"

using namespace std;

namespace BOOOS {

Semaphore::Semaphore(int i) {
	this->sem = i;
}

Semaphore::~Semaphore() {
	while (this->_waiting.length() > 0) {
		Task::self()->insert_ready((Task*) this->_waiting.remove());
	}
}

void Semaphore::p() {
	Timer::set_controle();
	this->sem--;
	if (sem < 0) {
		this->_waiting.insert(Task::self());
		Timer::free_controle();
		Task::self()->pass_to(Scheduler::self(),Task::WAITING);
		//arrumar status
	}
	Timer::free_controle();

}

void Semaphore::v() {
	Timer::set_controle();
	this->sem++;
	if (this->_waiting.length()>0) {
		Timer::free_controle();
		Task::self()->insert_ready((Task*)this->_waiting.remove());
	}
	Timer::free_controle();
}

}
