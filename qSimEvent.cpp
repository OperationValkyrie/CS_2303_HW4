/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimEvent.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>

using namespace std;

#include "qSimEvent.h"
#include "qSimCustomerEvent.h"
#include "qSimTellerEvent.h"

/**
 * Constructor for an Event object
 * @return The Event Object
 */
Event::Event() {
	isCustomer = 0;
	eventTime = 0;
	eventNext = 0;
}

/**
 * Destructor for an Event object\
 * @return void
 */
Event::~Event() {
}

/**
 * Does the action for the event
 * @param eventQueue The event queue
 * @param tellers The array of tellers
 * @param numTelelrs The number of tellers
 * @param currentTime The current Time
 * @return void
 */
void Event::doAction(EventQueue* eventQueue, TellerEvent** tellers,
		int numTellers, float currentTime) {
}

/**
 * Sets the event time
 * @param time The new event time
 * @return void
 */
void Event::setEventTime(float time) {
	eventTime = time;
}

/**
 * Gets the event time
 * @return The event time
 */
float Event::getEventTime() {
	return eventTime;
}

/**
 * Sets the next Event
 * @param event The next event in the event queue
 * @return void
 */
void Event::setEventNext(Event *event) {
	eventNext = event;
}

/**
 * Gets the next Event
 * @return The next Event
 */
Event* Event::getEventNext() {
	return eventNext;
}

/**
 * Removes and delinks the next event from this event
 * @return void
 */
void Event::removeEventNext() {
	eventNext = 0;
}

/**
 * Tests if current event is a customer event
 * @return Whether this event is a customer event
 */
bool Event::isCustomerEvent() {
	return isCustomer;
}

/**
 * Prints out this event
 * @return void
 */
void Event::printEvent() {
	if(isCustomer) {
		CustomerEvent* event = static_cast<CustomerEvent*>(this);
		cout << "Time: " << std::setprecision(9) << eventTime <<
				", C: " << isCustomer << ", S:" << event->beenServed() << endl;
	} else {
		TellerEvent* event = static_cast<TellerEvent*>(this);
		cout << "Time: " << std::setprecision(9) << eventTime <<
				", C: " << isCustomer << ", S:" << event->currentlyInService() << endl;
	}
	// cout << "Time: " << std::setprecision(9) << eventTime << ", C: " << isCustomer << endl;
}
