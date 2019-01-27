/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimCustomer.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "qSimEvent.h"
#include "qSimEventQueue.h"
#include "qSimCustomerQueue.h"
#include "qSimCustomerEvent.h"
#include "qSimTellerEvent.h"

/**
 * Contructor for a Customer Event object
 * @return The Customer object
 */
CustomerEvent::CustomerEvent() {
	startTime = 0;
	served = false;
	eventNext = 0;
	isCustomer = true;
	eventTime = 0;
}

/**
 * Contructor for a Customer Event object
 * @return The Customer Object
 */
CustomerEvent::CustomerEvent(float stTime) {
	startTime = stTime;
	served = false;
	eventNext = 0;
	isCustomer = true;
	eventTime = stTime;
}

/**
 * Decontructor for a Customer Event object
 * @return void
 */
CustomerEvent::~CustomerEvent(void) {
}

/**
 * Does the action for the customer event
 * @param eventQueue The event queue
 * @param tellers The array of tellers
 * @param numTelelrs The number of tellers
 * @param currentTime The current Time
 * @return void
 */
void CustomerEvent::doAction(EventQueue *eventQueue, TellerEvent** tellers,
		int numTellers, float currentTime) {
	CustomerQueue *customerQueue = getShortestQueue(tellers, numTellers);
	customerQueue->addCustomerLast(this);
	std::cout << "Added Customer";
}

/**
 * Sets this customer's start time
 * @param time The start time in seconds
 * @return void
 */
void CustomerEvent::setStartTime(float time) {
	startTime = time;
}

/**
 * Gets the start time of this customer
 * @return The start time
 */
float CustomerEvent::getStartTime() {
	return startTime;
}

/**
 * Gets if the customer has been served
 * @return Whether this customer is being or has been served
 */
bool CustomerEvent::beenServed() {
	return served;
}

/**
 * Sets whether the customer is being or has been served
 * @return void
 */
void CustomerEvent::setServed(bool s) {
	served = s;
}

/**
 * Sets the next Event
 * @param event The next event in the event queue
 * @return void
 */
void CustomerEvent::setEventNext(Event *event) {
	eventNext = event;
}

/**
 * Gets the next Event
 * @return The next Event
 */
Event* CustomerEvent::getEventNext() {
	return eventNext;
}

/**
 * Gets the shortest queue from the tellers and returns it
 * @param tellers The array of tellers
 * @param numTellers The number of tellers
 * @return The shortest Customer Queue
 */
CustomerQueue* CustomerEvent::getShortestQueue(TellerEvent** tellers, int numTellers) {
	CustomerQueue* shortQueue = tellers[0]->getCustomerQueue();
	int shortLength = tellers[0]->getCustomerQueue()->getLength();
	// Pre-conditions: No queues checked
	for(int i = 1; i < numTellers; i++) {
		// Loop Invariant: 0 < i < numTellers
		// Test if this queue is shorter than shortQueue
		if(tellers[i]->getCustomerQueue()->getLength() < shortLength) {
			// If this queue is shorter
			shortLength = tellers[i]->getCustomerQueue()->getLength();
			shortQueue = tellers[i]->getCustomerQueue();
		}
	}
	// Post-Conditions: All cusotmer queues checked
	return shortQueue;
}
