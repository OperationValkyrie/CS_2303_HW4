/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimEventQueue.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

#include "qSimEvent.h"
#include "qSimTellerEvent.h"
#include "qSimEventQueue.h"

/**
 * Constructor for an Event Queue
 * @return The Event Queue
 */
EventQueue::EventQueue() {
	eventFirst = 0;
	eventLast= 0;
	length = 0;
}

/**
 * Constructor for an Event Queue
 * @param event The first event to point at
 * @return The Event Queue
 */
EventQueue::EventQueue(Event* event) {
	eventFirst = event;
	eventLast= event;
	length = 1;
}

/**
 * Deconstructor for an Event Queue
 * @return void
 */
EventQueue::~EventQueue() {
	Event *event = eventFirst; // Holds the next event

	// Pre-conditions: No events deleted
	while(event != 0) {
		// Loop Invariant: event is not null
		Event *event2 = event->getEventNext();
		event->~Event();
		event = event2;
	}
	// Post-conditions: All events deleted
}

/**
 * Gets the first event from the queue and removes it from the queue
 * @return The first customer event from the queue
 */
Event* EventQueue::getEventFirst() {
	Event *cust = eventFirst;
	eventFirst = eventFirst->getEventNext();
	cust->removeEventNext();
	length--;
	if(length == 0) {
		eventLast = eventFirst;
	}
	return cust;
}

/**
 * Gets the event time of the first event
 * @return The event time of the first event
 */
int EventQueue::getEventFirstTime() {
	return eventFirst->getEventTime();
}

/**
 * Adds an event in sequential order based on the event time
 * @param event The event to add
 * @return void
 *
 * In the event of ties, the event is added afterward
 */
void EventQueue::addEvent(Event *event) {
	Event* eventCurrent = eventFirst; // Holds event to test
	Event* eventPrevious = eventFirst; // Holds previous event

	bool flag = false;
	// Pre-conditions: event has not been added
	while(!flag) {
		// Loop Invariant: eventCurrent is allows within the queue
		// Test if at first index and event is before eventFirst
		if(eventCurrent == eventFirst &&
				eventCurrent->getEventTime() > event->getEventTime()) {
			// If at first event and event is before eventFirst
			eventFirst = event;
			event->setEventNext(eventCurrent);
			// Test if length is one
			if(length == 1) {
				// If length is one
				eventCurrent->removeEventNext();
			}
			flag = true;
		}
		// Test if event is before eventCurrent and event not added
		if(!flag && eventCurrent->getEventTime() > event->getEventTime()) {
			// If event not added and event if before eventCurrent
			eventPrevious->setEventNext(event);
			event->setEventNext(eventCurrent);
			flag = true;
		}
		// Test if there is event after eventCurrent and event not added
		if(!flag && eventCurrent->getEventNext() != 0) {
			// If there is an event and event not added
			eventPrevious = eventCurrent;
			eventCurrent = eventCurrent->getEventNext();
		// Test if event has been added
		} else if(!flag) {
			// If event not added and not more events
			eventCurrent->setEventNext(event);
			event->removeEventNext();
			eventLast = event;
			flag = true;
		}
	}
	// Post-conditions: event added to queue
	length++;
}

/**
 * Gets the total length of the queue
 * @return The total number of Customers in the queue
 */
int EventQueue::getLength() {
	return length;
}

/**
 * Manually counts the length of the queue
 * @return The number of customers in the queue
 */
int EventQueue::countLength() {
	int count = 0; // Holds the count
	Event *eventNext = eventFirst; // Holds the next customer
	// Pre-conditions: last customer is linked to 0
	while(!eventNext) {
		// Loop Invariant: 0 < count < numberOfCustomers in Queue
		count++;
		eventNext = eventNext->getEventNext();
	}
	// Post-conditions: all customers counted
	return count;
}

/**
 * Prints out the queue in the proper order
 * @return void
 */
void EventQueue::printQueue() {
	Event* event = eventFirst;
	// Pre-conditions: No events printed
	while(event != 0) {
		// Loop Invariants: event points at an event in the queue
		cout << "  ";
		event->printEvent();
		event = event->getEventNext();
	}
	// Post-conditions: All events printed
}

/**
 * Tests if the queue still has any customer events
 * @return Whether the queue has any customer events
 */
bool EventQueue::hasCustomerEvent() {
	Event *event = eventFirst;
	// Pre-conditions: No events checked
	while(event != 0) {
		// Loop Invariant: event points to valid event
		// Test if event is CustomerEvent
		if(event->isCustomerEvent()) {
			// If the event is a CustomerEvent
			return true;
		}
		event = event->getEventNext();
	}
	// Post-conditions: All events checked
	return false;
}

/**
 * Tests if the queue has any tellers serving
 * @return Whether a teller is serving
 */
bool EventQueue::hasServingTeller() {
	Event *event = eventFirst;
	// Pre-conditions: No events checked
	while(event != 0) {
		// Loop Invariant: event points to valid event
		// Test if event is CustomerEvent
		if(!event->isCustomerEvent()) {
			// If the event is a TellerEvent
			TellerEvent* teller = static_cast<TellerEvent*>(event);
			// Test if teller is serving
			if(teller->currentlyInService()) {
				// If teller is serving
				return true;
			}
		}
		event = event->getEventNext();
	}
	// Post-conditions: All events checked
	return false;
}
