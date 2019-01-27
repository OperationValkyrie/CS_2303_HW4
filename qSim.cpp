/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSim.cpp
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>

#include "qSim.h"
#include "qSimEvent.h"
#include "qSimCustomerEvent.h"
#include "qSimTellerEvent.h"
#include "qSimEventQueue.h"
#include "qSimCustomerQueue.h"

using namespace std;

#define SINGLEQUEUE false // Whether there is only one line
#define TELLERINITIALWAITTIME 600 // Initial wait time for tellers
#define TELLERWAITTIME 150 // Wait time for tellers if no customers

static int totalCustomers; // Holds the total number of served customers
static float* customerTotalTimes; // Holds all of the wait times;
static float maximumWaitTime; // Holds the maximum wait time
static float tellerServiceTime; // Holds the total time of teller service
static float tellerIdleTime; // Holds the total time of teller wait time

int main(int argc, char **argv) {

	int numCustomers; // Holds the number of customers
	int numTellers; // Holds the number of tellers
	float simTime; // Holds the total simulation time
	float averageServiceTime; // Holds the average service time
	int seed; // Holds the seed

	// Test if incorrect number of arguments
	if(argc < 4 || argc > 5) {
		// Uf incorrect number of arguments
		cout << "Incorrect number of arguments" << endl;
		cout << "Required Arguments: " << endl;
		cout << "  (int) The number of customers to simulate" << endl;
		cout << "  (int) The number of tellers to simulate" << endl;
		cout << "  (float) The total simulation time in minutes" << endl;
		cout << "  (float) The average service time in minutes" << endl;
		cout << "Optional Arguments: " << endl;
		cout << "  (int) The seed to use in random number generation" << endl;
		return EXIT_FAILURE;
	}

	// Assign variables to given arguments
	numCustomers = atoi(argv[1]);
	numTellers = atoi(argv[2]);
	simTime = atof(argv[3]);
	averageServiceTime = atof(argv[4]);
	seed = time(0);

	// Test if optional variable given
	if(argc == 6) {
		// If optional variable given
		seed = atoi(argv[5]);
	}
	srand(seed); // Set the random seed

	cout << "C: " << numCustomers << " ,T: " << numTellers << " ,MT:" << simTime
			<< " ,AST: " << averageServiceTime << " ,S: " << seed << endl << endl;

	// Add randomly generated customers
	EventQueue *eventQueue = generateCustomers(numCustomers, simTime);

	// Holds tellers in array
	TellerEvent* tellers[numTellers];

	// Test if using single queue
	if(SINGLEQUEUE) {
		// If using single queue
		// Generate Tellers with random waiting time
		eventQueue = generateTellersSingleQueue(eventQueue, numTellers, tellers,
				averageServiceTime);
	} else {
		// If using separate queues
		// Generate Tellers with random waiting time
		eventQueue = generateTellerSeparateQueues(eventQueue, numTellers, tellers,
				averageServiceTime);
	}

	// Prints initial event queue
	cout << "Initial Event Queue:" << endl;
	eventQueue->printQueue();
	cout << endl << "Running Events:" << endl;

	// Initialize statistic variables
	float currentTime = 0;
	float nextTime = 0;
	totalCustomers = 0;
	customerTotalTimes = new float[numCustomers];
	maximumWaitTime = 0;
	tellerServiceTime = 0;
	tellerIdleTime = 0;

	// Pre-conditions: No events run yet
	while(nextTime < simTime &&
			(eventQueue->hasCustomerEvent() || eventQueue->hasServingTeller()
					|| customerInQueue(tellers, numTellers))) {
		// Loop Invariant: simulation time has not been reached and customer are being
		// 					served or will be served
		Event *currentEvent = eventQueue->getEventFirst();
		currentTime = currentEvent->getEventTime();

		cout << "  " << currentTime << " ";

		currentEvent->doAction(eventQueue, tellers, numTellers, currentTime);

		nextTime = eventQueue->getEventFirstTime();
		cout << endl;
	}
	// Post-conditions: All events run or all customers served
	printLogs(currentTime, numTellers);
	return 0;
}

/**
 * Generates the given number of customers over the given simulation time
 * @param numCustomers The number of customers to generate
 * @param simTime The overall simulation time to generate for
 * @return The customers as a event Queue in correct arrival time order
 */
EventQueue* generateCustomers(int numCustomers, float simTime) {
	CustomerEvent *custFirst = new CustomerEvent(generateArrivalTime(simTime));
	EventQueue *queue = new EventQueue(custFirst);
	// Pre-conditions: No customers added yet
	for(int i = 1; i < numCustomers; i++) {
		// Loop Invariant: 0 i < numCustomers
		queue->addEvent(new CustomerEvent(generateArrivalTime(simTime)));
	}
	// Post-conditions: All customers added
	return queue;
}

/**
 * Generates the given number of tellers and adds them to the event queue
 * @param queue The event queue to add the tellers to
 * @param numTellers The number of tellers to add
 * @return The event queue with the added tellers
 */
EventQueue* generateTellersSingleQueue(EventQueue *queue, int numTellers,
		TellerEvent** tellers, float averageServiceTime) {
	CustomerQueue * customerQueue = new CustomerQueue();
	// Pre-conditions: No tellers added yet
	for(int i = 0; i < numTellers; i++) {
		// Loop Invariant: 0 < i < numTellers
		TellerEvent *teller = new TellerEvent(customerQueue);
		teller->setEventTime(generateInitialWaitTime());
		tellers[i] = teller;
		teller->setAverageServiceTime(averageServiceTime);
		queue->addEvent(teller);
	}
	// Post-conditions: All tellers added
	return queue;
}

/**
 * Generates the given number of teller and adds them to the event queue
 * @param queue The event queue to add to
 * @param numTellers The number of tellers to add
 * @param tellers The teller array to add to
 * @return The event queue with the tellers added
 */
EventQueue* generateTellerSeparateQueues(EventQueue *queue, int numTellers,
		TellerEvent** tellers, float averageServiceTime) {
	// Pre-conditions: No tellers added yet
	for(int i = 0; i < numTellers; i++) {
		// Loop Invariant: 0 < i < numTellers
		TellerEvent *teller = new TellerEvent();
		teller->setEventTime(generateInitialWaitTime());
		teller->setAverageServiceTime(averageServiceTime);
		tellers[i] = teller;
		queue->addEvent(teller);
	}
	// Post-conditions: All tellers added
	return queue;
}

/**
 * Gets a random queue from the tellers with customers in it
 * @param tellers The array of tellers
 * @param numTellers The number of tellers
 * @return A Random queue that has customers in it
 *
 * If none of the tellers has a queue with customers a empty
 * queue will be returned
 */
CustomerQueue* getRandomQueueWithCustomers(TellerEvent** tellers, int numTellers) {
	CustomerQueue* queues[numTellers];
	int added = 0;
	// Pre-conditions: No tellers checked
	for(int i = 0; i < numTellers; i++) {
		// Test if teller queue has customers in it
		if(tellers[i]->getCustomerQueue()->getLength() != 0) {
			// If teller queue has customers in it
			queues[added] = tellers[i]->getCustomerQueue();
			added++;
		}
	}
	// Post-conditions: All tellers checked
	// Test if no queues were added
	if(added == 0) {
		// If no queues were added
		return new CustomerQueue();
	} else {
		// If at least one queue was added
		return queues[rand() % added];
	}
}

/**
 * Tests if a customer is in a teller's customer queue
 * @param teller The array of tellers
 * @param numTellers The number of tellers
 * @return Whether any teller queue has a customer
 */
bool customerInQueue(TellerEvent** tellers, int numTellers) {
	// Pre-conditions: No queues checked
	for(int i = 0; i < numTellers; i++) {
		// Loop Invariant: 0 < i < numTellers
		// Test if the queue has at least one customer in it
		if(tellers[i]->getCustomerQueue()->getLength() != 0) {
			// If the queue has customers
			return true;
		}
	}
	// Post-conditions: All queues checked
	return false;
}

/**
 * Generates a random arrival time for a customer
 * @param simTime The overall simulation time to generate for
 * @return A arrival time randomized to to the simulation time
 */
float generateArrivalTime(float simTime) {
	return simTime * rand()/float(RAND_MAX);
}

/**
 * Generates a random initial wait time for a teller
 * @return The initial wait time
 */
float generateInitialWaitTime() {
	float idleTime = (rand() % TELLERINITIALWAITTIME) / 60.0;
	tellerIdleTime += idleTime;
	return idleTime;
}

/**
 * Generates a random idle time for a teller
 * @return The random idle time
 */
float generateIdleTime() {
	float idleTime = (rand() % TELLERWAITTIME) / 60.0;
	tellerIdleTime += idleTime;
	return idleTime;
}

/**
 * Generates a service time for a teller
 * @return The random service time
 */
float generateServiceTime(float averageServiceTime) {\
	float serviceTime = 2 * averageServiceTime * rand()/float(RAND_MAX);
	tellerServiceTime += serviceTime;
	return serviceTime;
}

/**
 * Logs a customer statistics
 * @param customer The customer to log
 * @param currentTime The time that the customer exits
 * @return void
 */
void logCustomer(CustomerEvent *customer, float currentTime) {
	customerTotalTimes[totalCustomers] = currentTime - customer->getStartTime();
	totalCustomers++;
	delete customer;
}

/**
 * Checks the wait time of the customer
 * @param customer The customer to check
 * @param currentTime The current Time
 * @return void
 */
void checkWaitTime(CustomerEvent* customer, float currentTime) {
	float totalTime = currentTime - customer->getStartTime();
	// Test if current wait time is greater than held time
	if(maximumWaitTime < totalTime) {
		// If current wait time is greater
		maximumWaitTime = totalTime;
	}
}

/**
 * Prints out the final log and statistics of this simulation
 * @param endTime The end time of the simulation
 * @param numTellers The number of Tellers
 * @return void
 */
void printLogs(float endTime, int numTellers) {
	cout << endl;
	cout << "Final Simulation Statistics:" << endl;
	cout << "  Total Customers Served:             " << totalCustomers << endl;
	cout << "  Total Time:                         " << endTime << endl;
	cout << "  Total Number of Tellers:            " << numTellers << endl;
	cout << "  Type of Queuing:                    ";
	// Test if using single queue
	if(SINGLEQUEUE) {
		// If using a single queue
		cout << "Common Queue" << endl;
	} else {
		// If using seperate queues
		cout << "Separate Queues" << endl;
	}
	cout << "  Average Time in Bank:               " << calculateAverageTotalTime() << endl;
	cout << "  Standard Deviation of Time in Bank: " << calculateStandardDeviation() << endl;
	cout << "  Maximum Wait Time:                  " << maximumWaitTime << endl;
	cout << "  Total Teller Service Time:          " << tellerServiceTime << endl;
	cout << "  Total Teller Idle Time:             " << tellerIdleTime << endl;
}

/**
 * Calculates the average total time in bank
 * @return The average total time in the bank
 */
float calculateAverageTotalTime() {
	float totalTime = 0;
	// Pre-conditions: No times added yet
	for(int i = 0; i < totalCustomers; i++) {
		// Loop Invariant: 0 < i < totalCustomers
		totalTime += customerTotalTimes[i];
	}
	// Post-conditionsL All times added
	return totalTime / totalCustomers;
}

/**
 * Calculates the standard Deviation of the time in bank
 * @return The standard deviation
 */
float calculateStandardDeviation() {
	float averageTime = calculateAverageTotalTime();
	float totalDifferences = 0;
	// Pre-conditions: No differences added
	for(int i = 0; i < totalCustomers; i ++) {
		// Loop Invariant: 0 < i < totalCustomers
		totalDifferences += std::abs(averageTime - customerTotalTimes[i]);
	}
	// Post-conditions: All differences added
	return totalDifferences / totalCustomers;
}
