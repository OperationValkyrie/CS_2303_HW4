/*
 * Jonathan Chang
 * CS 2303 C02 18
 * Assignment 4
 * qSim.h
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "qSimEvent.h"
#include "qSimEventQueue.h"
#include "qSimCustomerEvent.h"
#include "qSimTellerEvent.h"
#include "qSimCustomerQueue.h"

#ifndef QSIM_H
#define QSIM_H

EventQueue* generateCustomers(int numCustomers, float simTime);
EventQueue* generateTellersSingleQueue(EventQueue* queue, int numTellers,
		TellerEvent** tellers, float averageServiceTime);
EventQueue* generateTellerSeparateQueues(EventQueue* queue, int numTellers,
		TellerEvent** tellers, float averageServiceTime);

CustomerQueue* getRandomQueueWithCustomers(TellerEvent** tellers, int numTellers);

bool customerInQueue(TellerEvent** tellers, int numTellers);

float generateArrivalTime(float simTime);
float generateInitialWaitTime();
float generateIdleTime();
float generateServiceTime(float averageServiceTime);

void logCustomer(CustomerEvent *customer, float currentTime);
void checkWaitTime(CustomerEvent *customer, float currentTime);
void printLogs(float endTime, int numTellers);

float calculateAverageTotalTime();
float calculateStandardDeviation();
#endif
