/*
 * Queue.cc
 *
 *  Created on: Feb 21, 2014
 *      Author: arliones
 */

#include "Queue.h"
#include <iostream>
#include "BOOOS.h"
#include "Scheduler.h"
using namespace std;

namespace BOOOS {

// Queue constructor: must initialize queue's attributes
Queue::Queue() {
	_length = 0;
}

// Queue destructor: must finalize queue's attributes
Queue::~Queue() {
//delete elementos e head

	/*
	 //Deletando todos os elementos ****
	 while(this->length()){
	 this->remove();
	 }
	 //libera o espaço de memoria da cabeca da fila.
	 //delete this->head();*/
	return;
}

// insert method: must insert the Element at the end of the queue
// Error messages:
//   01: invalid Element (if elem == 0)
//   02: duplicated Element (if elem already is on the queue)
void Queue::insert(Queue::Element * elem) {
	Queue::Element * aux;

	//caso de erro 01.
	if (elem == 0) {
		cerr << "01: invalid Element" << endl;
		return;
	}

	//quando adicionar um elemento com a lista vazia.
	if (this->length() == 0) {
		this->head()->prev(0);
		this->head()->next(elem);
		this->head()->next()->next(this->head()->next());
		this->head()->next()->prev(this->head()->next());
		this->head()->prev(this->head()->next()->prev());
		this->_length++;
		return;
	}

	//caso de erro 02.

	for (aux = this->head()->next(); aux->next() != this->head()->next(); aux =
			aux->next()) {

		if (aux == elem) {
			cerr << "02: duplicated Element" << endl;
			return;
		}
	}

	aux = this->_head.prev();
	//Adicionando o elemento no final da fila
	aux->next(elem);
	elem->next(this->head()->next());
	elem->prev(aux);
	this->head()->next()->prev(elem);
	this->head()->prev(this->head()->next()->prev());
	this->_length++;
	return;

}

// remove: must search and remove the element from the queue
// Error messages:
//   01: queue is empty
Queue::Element * Queue::remove() {

	//caso de erro 01
	if (this->length() == 0) {
		cerr << "01: queue is empty" << endl;
		return 0;
	}

	/*ajusta quais o proximo e o anterio do primeiro elemento da lista
	 e define qual o novo primeiro elemento da lista,o posterior ao antigo
	 primeiro elemento*/
	Element * aux;
	aux = this->head()->next();
	aux->next()->prev(aux->prev());
	aux->prev()->next(aux->next());
	this->head()->next(aux->next());
	this->head()->prev(this->head()->next()->prev());

	this->_length--;
	if (this->_length == 0) {
		this->head()->next(0);
		this->head()->prev(0);
	}
	aux->next(0);
	aux->prev(0);

	return aux;
}

// insert method: must insert the Element ordered
// Error messages:
//   01: invalid Element (if elem == 0)
//   02: duplicated Element (if elem already is on the queue)

void Queue::insert_ordered(Element* elem) {
	Queue::Element * ant;
	Queue::Element * prox;

	//caso de erro 01.
	if (elem == 0) {
		cerr << "01: invalid Element" << endl;
		return;
	}

	//quando adicionar um elemento com a lista vazia.
	if (this->length() == 0) {
		return insert(elem);
	}

	//caso de erro 02.

	for (ant = this->head()->next(); ant->next() != this->head()->next(); ant =
			ant->next()) {

		if (ant == elem) {
			cerr << "02: duplicated Element" << endl;
			return;
		}
	}

	if (this->length() == 1) {
		if (elem->rank() < this->_head.next()->rank()) {
			elem->next(this->_head.next());
			elem->prev(this->_head.next());
			this->head()->next()->next(elem);
			this->head()->next()->prev(elem);
			this->head()->next(elem);
			this->head()->prev(this->head()->next()->prev());
			this->_length++;
			return;
		} else {
			return insert(elem);
		}
	}
	int c;
	for (prox = this->_head.next(), c = 0; prox != this->_head.next() || c == 0;
			prox = prox->next(), c++) {
		if (elem->rank() < prox->rank()) {
			if (c == 0) {
				this->_head.next(elem);
			}
			elem->next(prox);
			prox->prev()->next(elem);
			elem->prev(prox->prev());
			prox->prev(elem);
			this->_length++;
			return;
		}

	}
	return insert(elem);
}

// insert method: must insert the Element ordered for time
// Error messages:
//   01: invalid Element (if elem == 0)
//   02: duplicated Element (if elem already is on the queue)

void Queue::insert_ordered_time(Element* elem) {
	Queue::Element * ant;
	Queue::Element * prox;
	Queue::Element * aux;

	//caso de erro 01.
	if (elem == 0) {
		cerr << "01: invalid Element" << endl;
		return;
	}

	//quando adicionar um elemento com a lista vazia.
	if (this->length() == 0) {
		this->head()->prev(0);
		this->head()->next(elem);
		this->head()->next()->next(this->head()->next());
		this->head()->next()->prev(this->head()->next());
		this->head()->prev(this->head()->next()->prev());
		this->_length++;
		return;
	}

	//caso de erro 02.

	for (ant = this->head()->next(); ant->next() != this->head()->next(); ant =
			ant->next()) {

		if (ant == elem) {
			cerr << "02: duplicated Element" << endl;
			return;
		}
	}

	if (this->length() == 1) {
		if (elem->time_sleep() < this->_head.next()->time_sleep()) {
			elem->next(this->_head.next());
			elem->prev(this->_head.next());
			this->head()->next()->next(elem);
			this->head()->next()->prev(elem);
			this->head()->next(elem);
			this->head()->prev(this->head()->next()->prev());
			this->_length++;
			return;

		} else {
			aux = this->_head.prev();
			//Adicionando o elemento no final da fila
			aux->next(elem);
			elem->next(this->head()->next());
			elem->prev(aux);
			this->head()->next()->prev(elem);
			this->head()->prev(this->head()->next()->prev());
			this->_length++;
			return;
		}
	}
	int c;
	for (prox = this->_head.next(), c = 0; prox != this->_head.next() || c == 0;
			prox = prox->next(), c++) {
		if (elem->time_sleep() < prox->time_sleep()) {
			if (c == 0) {
				this->_head.next(elem);
			}
			elem->next(prox);
			prox->prev()->next(elem);
			elem->prev(prox->prev());
			prox->prev(elem);
			this->_length++;
			return;
		}

	}
	aux = this->_head.prev();
	//Adicionando o elemento no final da fila
	aux->next(elem);
	elem->next(this->head()->next());
	elem->prev(aux);
	this->head()->next()->prev(elem);
	this->head()->prev(this->head()->next()->prev());
	this->_length++;
	return;
}



}

