/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSimTeller.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

#include "qSim.h"
#include "qSimEvent.h"
#include "qSimTellerEvent.h"
#include "qSimCustomerQueue.h"

/**
 * Constructor for Teller Object
 * @return The Teller object
 */
TellerEvent::TellerEvent() {
	queue = new CustomerQueue();
	customer = 0;
	eventNext = 0;
	isCustomer = false;
	inService = false;
	averageServiceTime = 0;
}

/**
 * Constructor for the Teller Object
 * @param q The queue that the Teller services
 * @return The Teller object
 */
TellerEvent::TellerEvent(CustomerQueue *q) {
	queue = q;
	customer = 0;
	eventNext = 0;
	isCustomer = false;
	inService = false;
	averageServiceTime = 0;
}

/**
 * Decontructor for the Teller Object
 * @return void
 *
 * Will deconstrut the appointed queue as well
 */
TellerEvent::~TellerEvent(){
	queue->~CustomerQueue();
	delete queue;
}

/**
 * Does the required action
 * @param eventQueue The event queue
 * @param tellers The array of tellers
 * @param numTelelrs The number of tellers
 * @param currentTime The current Time
 * @return void
 */
void TellerEvent::doAction(EventQueue *eventQueue, TellerEvent** tellers,
		int numTellers, float currentTime) {
	// Test if teller event is serving a customer
	if(this->currentlyInService()) {
		// If teller event is serving a customer
		logCustomer(this->getCustomer(), currentTime);
		cout << "Customer Served ";
	}

	CustomerQueue *tellerQueue = this->getCustomerQueue();
	// Test if current customer queue is empty
	if(this->getCustomerQueue()->getLength() == 0) {
		// If customer queue is empty
		tellerQueue = getRandomQueueWithCustomers(tellers, numTellers);
	}
	// Test if the customer queue is empty
	if(tellerQueue->getLength() == 0) {
		// If customer queue is empty
		this->setInService(false);
		this->setEventTime(currentTime + generateIdleTime());
		cout << "Teller Idle";
	} else {
		// If customer queue has customers
		this->setInService(true);
		CustomerEvent *customer = static_cast<CustomerEvent*>
			(tellerQueue->getCustomerFirst());
		this->setCustomer(customer);
		checkWaitTime(customer, currentTime);
		this->setEventTime(currentTime +
				generateServiceTime(averageServiceTime));
		cout << "Teller Serving";
	}
	eventQueue->addEvent(this);
}

/**
 * Sets the customer queue for the teller
 * @param The customer queue to set to
 */
void TellerEvent::setCustomerQueue(CustomerQueue *q) {
	queue = q;
}

/**
 * Gets the teller customer queue
 * @return The customer queue for this teller
 */
CustomerQueue* TellerEvent::getCustomerQueue() {
	return queue;
}

/**
 * Sets the event time
 * @param time The new event time
 * @return void
 */
void TellerEvent::setEventTime(float time) {
	eventTime = time;
}

/**
 * Sets the current customer of this teller
 * @param cust The customer to set to
 */
void TellerEvent::setCustomer(CustomerEvent* cust) {
	customer = cust;
}

/**
 * Gets the current customer of this teller
 * @return The current customer
 *
 * Delinks the customer from the Teller
 */
CustomerEvent* TellerEvent::getCustomer() {
	CustomerEvent* cust = customer;
	customer = 0;
	return cust;
}

/**
 * Gets if the teller is currently serving a customer
 * @return Whether the teller is currently serving a customer
 */
bool TellerEvent::currentlyInService() {
	return inService;
}

/**
 * Sets whether the teller is in service
 * @return void
 */
void TellerEvent::setInService(bool inS) {
	inService = inS;
}

/**
 * Sets the average service time of the teller
 * @param time The average service time
 * @return void
 */
void TellerEvent::setAverageServiceTime(float time) {
	averageServiceTime = time;
}
