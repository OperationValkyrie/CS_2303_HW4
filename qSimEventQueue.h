/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimEventQueue.h
 */

#ifndef QSIMEVENTQUEUE_H
#define QSIMEVENTQUEUE_H

#include "qSimEvent.h"

class EventQueue {
public:
	EventQueue();
	EventQueue(Event *cust);
	~EventQueue();

	Event* getEventFirst();
	int getEventFirstTime();
	bool isNextEventCustomer();

	void addEvent(Event *event);

	int getLength();
	int countLength();

	void printQueue();

	bool hasCustomerEvent();
	bool hasServingTeller();
private:
	Event *eventFirst; // The first Customer in line
	Event *eventLast; // The last Customer in line
	int length; // Length of the queue

};
#endif
