/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimCustomerQ.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "qSimEvent.h"
#include "qSimEventQueue.h"
#include "qSimCustomerQueue.h"
#include "qSimCustomerEvent.h"
using namespace std;

/**
 * Constructor for CustomerQueue
 * @return The CustomerQueue Object
 */
CustomerQueue::CustomerQueue() {
	customerFirst = 0;
	length = 0;
	customerLast = customerFirst;
}

/**
 * Constructor for CustomerQueue
 * @param cust The first Customer in the queue
 * @return The CustomerQueue Object
 */
CustomerQueue::CustomerQueue(CustomerEvent *cust) {
	customerFirst = cust;
	customerLast = customerFirst;
	length = 1;
}

/**
 * Deconstructor for CustomerQueue
 * @return void
 *
 * Will deconstruct all customers in the queue as well
 */
CustomerQueue::~CustomerQueue() {
	Event *cust = customerFirst; // Holds the next customer

	// Pre-conditions: no customers deleted
	while(cust != 0) {
		// Loop Invariant: cust is not null
		Event *cust2 = cust->getEventNext();
		cust->~Event();
		cust = cust2;
	}
	// Post-conditions: all customers deleted
}

/**
 * Gets the total length of the queue
 * @return The total number of Customers in the queue
 */
int CustomerQueue::getLength() {
	return length;
}

/**
 * Gets the first customer in the queue
 * @return The first customer
 *
 * The customer is delinked from the queue
 */
CustomerEvent* CustomerQueue::getCustomerFirst() {
	CustomerEvent *event = static_cast<CustomerEvent*>(customerFirst);
	customerFirst = static_cast<CustomerEvent*>(event->getEventNext());
	event->removeEventNext();
	length--;
	return event;
}

/**
 * Adds a customer to the end of the queue
 * @param cust The customer to add
 * @return void
 */
void CustomerQueue::addCustomerLast(CustomerEvent *cust) {
	if(length == 0) {
		customerFirst = cust;
		customerLast = cust;
	} else  {
		customerLast->setEventNext(cust);
		customerLast = cust;
	}
	length++;
}

/**
 * Prints out a Customer Queue
 * @return void
 */
void CustomerQueue::printCustomerQueue() {
	Event* event = customerFirst;
	// Pre-conditions: No events printed
	while(event != 0) {
		// Loop Invariants: event points at an event in the queue
		cout << "  ";
		event->printEvent();
		event = event->getEventNext();
	}
	// Post-conditions: All events printed
}

