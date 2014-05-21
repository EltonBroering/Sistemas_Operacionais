/*
 * Queue_Test.cc
 *
 *  Created on: Feb 21, 2014
 *      Author: arliones
 */

#include <iostream>
#include <Queue.h>

#define ASSERT(x,y) if(!(x)) return y;

using namespace std;
using namespace BOOOS;

class MyElement : public Queue::Element {
public:
	MyElement(string str) : _name(str) {}

	virtual ~MyElement() {}

	string & name() { return _name; }

private:
	string _name;
};

void print_queue(Queue & q) {
	cout << "Queue length: " << q.length() << endl;

	if(q.length()) {
		MyElement * elem = dynamic_cast<MyElement *>(q.head()->next());
		do {
			cout << elem->name() << endl;
			elem = dynamic_cast<MyElement *>(elem->next());
		} while (elem != q.head()->next());
	}

	cout << "==============================" << endl;
}

int test_creation_destruction() {
	Queue *q = new Queue();

	ASSERT(q->length() == 0, 1);
	ASSERT(q->head()->next() == 0, 2);
	ASSERT(q->head()->prev() == 0, 3);

	delete q;

	return 	0;
}

int test_insertion() {
	Queue q;

	MyElement * person1 = new MyElement("João");
	MyElement * person2 = new MyElement("Pedro");
	MyElement * person3 = new MyElement("Augusto");
	MyElement * person4 = new MyElement("Fábio");

	q.insert(person1);
	q.insert(person2);
	q.insert(person3);
	q.insert(person4);

	ASSERT(q.head()->next() == person1, 1); // head
	ASSERT(q.head()->prev() == person4, 2); // tail

	MyElement * tmp = dynamic_cast<MyElement*>(q.head()->next());
	ASSERT(tmp == person1, 3);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person2, 4);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person3, 5);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person4, 6);

	return 0;
}

int test_remotion() {
	Queue q;

	MyElement * person1 = new MyElement("João");
	MyElement * person2 = new MyElement("Pedro");
	MyElement * person3 = new MyElement("Augusto");
	MyElement * person4 = new MyElement("Fábio");

	q.insert(person1);
	q.insert(person2);
	q.insert(person3);
	q.insert(person4);

	MyElement * removed_person = dynamic_cast<MyElement *>(q.remove());
	ASSERT(person1 == removed_person, 1);
	delete removed_person;

	ASSERT(q.head()->next() == person2, 2);
	ASSERT(person2->prev() == q.head()->prev(), 3);
	ASSERT(q.head()->prev()->next() == person2, 4);

	return 0;
}

int test_ordered_insertion() {
	Queue q;

	MyElement * person1 = new MyElement("João");
	MyElement * person2 = new MyElement("Pedro");
	MyElement * person3 = new MyElement("Augusto");
	MyElement * person4 = new MyElement("Fábio");

	person1->rank(3);
	person2->rank(1);
	person3->rank(6);
	person4->rank(2);

	q.insert_ordered(person1);
	q.insert_ordered(person2);
	q.insert_ordered(person3);
	q.insert_ordered(person4);

	ASSERT(q.head()->next() == person2, 1); // head
	ASSERT(q.head()->prev() == person3, 2); // tail

	MyElement * tmp = dynamic_cast<MyElement*>(q.head()->next());
	ASSERT(tmp == person2, 3);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person4, 4);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person1, 5);
	tmp = dynamic_cast<MyElement*>(tmp->next());
	ASSERT(tmp == person3, 6);

	return 0;
}

int main() {
	cout << "Welcome to BOOOS - Basic Object Oriented Operating System!" << endl;
	cout << "This program will test the class: Queue" << endl;

	cout << "Creation and Destruction: " << test_creation_destruction() << endl;
	cout << "Insertion: " << test_insertion() << endl;
	cout << "Remotion: " << test_remotion() << endl;
	cout << "Ordered Insertion: " << test_ordered_insertion() << endl;

	return 0;
}
