#include "Message_Queue.h"
#include "BOOOS.h"
#include "Semaphore.h"
#include "Queue.h"

using namespace std;

namespace BOOOS {

//construtor da fila de mensagens.Recebe como parametro o tamanho maximo da mensagem.
Message_Queue::Message_Queue(int max_size) {
	this->_max_size = max_size;
	this->empty = new Semaphore(0);
	this->full = new Semaphore(this->_max_size);
}

Message_Queue::~Message_Queue() {
	while (this->_queue.length()) {
		delete this->_queue.remove();
	}
//	delete &this->empty;
//	delete &this->full;
}

void Message_Queue::send(Message & msg) {
	this->full->p();
	Message *aux = new Message(msg);
	this->_queue.insert(aux);
	this->empty->v();
}

Message_Queue::Message Message_Queue::receive() {
	this->empty->p();
	Message* aux =(Message *) this->_queue.remove();
	this->full->v();
	return *aux;
}

}
