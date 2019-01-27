/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimCustomerQueue.h
 */

#ifndef QSIMCUSTOMERQUEUE_H
#define QSIMCUSTOMERQUEUE_H

#include "qSimEvent.h"
#include "qSimCustomerEvent.h"
#include "qSimEventQueue.h"

class CustomerQueue: public EventQueue {
public:
	CustomerQueue();
	CustomerQueue(CustomerEvent *cust);
	~CustomerQueue();

	CustomerEvent* getCustomerFirst();
	void addCustomerLast(CustomerEvent* cust);

	int getLength();

	void printCustomerQueue();
private:
	CustomerEvent *customerFirst; // The first Customer in line
	CustomerEvent *customerLast; // The last Customer in line
	int length; // Length of the queue

	int countLength();
};
#endif
