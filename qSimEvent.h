/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimEvent.h
 */

#ifndef QSIMEVENT_H
#define QSIMEVENT_H

class EventQueue;
class TellerEvent;

class Event {
friend class CustomerEvent;
friend class TellerEvent;
public:
	Event();
	virtual ~Event();

	virtual void doAction(EventQueue *eventQueue, TellerEvent** tellers,
			int numTellers, float currentTime);
	void setEventTime(float time);
	float getEventTime();

	void setEventNext(Event* event);
	Event* getEventNext();
	void removeEventNext();

	bool isCustomerEvent();

	void printEvent();
private:
	bool isCustomer; // Holds if event is customer event
	float eventTime; // Holds the event time
	Event* eventNext; // Holds the next event
};
#endif
