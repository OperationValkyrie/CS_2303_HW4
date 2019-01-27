/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimCustomer.h
 */

#ifndef QSIMCUSTOMEREVENT_H
#define QSIMCUSTOMEREVENT_H

#include "qSimEvent.h"
class CustomerQueue;

class CustomerEvent: public Event {
public:
	CustomerEvent(); // Constructor
	CustomerEvent(float stTime); // Constructor
	~CustomerEvent(); // Destructor

	void doAction(EventQueue* eventQueue, TellerEvent** tellers, int numTellers,
			float currentTime);
	void setStartTime(float time);
	float getStartTime();

	void setEventNext(Event* event);
	Event* getEventNext();

	bool beenServed();
	void setServed(bool s);

	void action();

	void setEventNExt(Event *event);
	Event* getEventNExt();
private:
	float startTime; // Holds the time the customer enters the bank
	bool served; // If the customer is being served or has been served
	Event* eventNext; // Holds the next Event

	CustomerQueue* getShortestQueue(TellerEvent** tellers, int numTellers);
};
#endif
