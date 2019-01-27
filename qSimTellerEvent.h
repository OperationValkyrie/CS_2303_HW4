/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimTeller.h
 */

#ifndef QSIMTELLEREVENT_H
#define QSIMTELLEREVENT_H

#include "qSimEvent.h"
#include "qSimCustomerEvent.h"
#include "qSimCustomerQueue.h"

class TellerEvent: public Event {
public:
	TellerEvent();
	TellerEvent(CustomerQueue *q);
	~TellerEvent();

	void doAction(EventQueue *eventQueue, TellerEvent** tellers, int numTellers,
			float currentTime);
	void setCustomerQueue(CustomerQueue *q);
	CustomerQueue* getCustomerQueue();
	void setCustomer(CustomerEvent* cust);
	CustomerEvent* getCustomer();

	bool currentlyInService();
	void setInService(bool inS);

	void setEventTime(float time);

	void setAverageServiceTime(float time);
private:
	bool inService; // Holds if currently serving a customer
	CustomerQueue* queue; // Holds the main queue to service
	CustomerEvent* customer; // Holds the current customer

	float averageServiceTime; // Holds the average service time
};
#endif
