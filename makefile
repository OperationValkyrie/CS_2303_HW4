# Jonathan Chang
# CS 2303 C02 18
# Assignment 4
# makefile

all: qSim

CFLAGS = -c -g -Wall

qSim: qSim.o qSimCustomerEvent.o qSimCustomerQueue.o qSimTellerEvent.o qSimEvent.o qSimEventQueue.o
	g++ *.o -lm
	
qSim.o: qSim.cpp *.h
	gcc $(CFLAGS) qSim.cpp
	
qSimCustomerQueue.o: qSimCustomerQueue.cpp *.h
	gcc $(CFLAGS) qSimCustomerQueue.cpp 
	
qSimEventQueue.o: qSimEventQueue.cpp *.h
	gcc $(CFLAGS) qSimEventQueue.cpp
	
qSimTellerEvent.o: qSimTellerEvent.cpp *.h
	gcc $(CFLAGS) qSimTellerEvent.cpp
	
qSimCustomerEvent.o: qSimCustomerEvent.cpp *.h
	gcc $(CFLAGS) qSimCustomerEvent.cpp

qSimEvent.o: qSimEvent.cpp *.h
	gcc $(CFLAGS) qSimEvent.cpp
	
clean:
	rm -f *.o qSim
	rm -f -r html latex

docs:
	doxygen
	# Following lines are only needed if we want to access doc pages
	#   using a Web server.
	#chmod go+r html/*
	#cp html/* ~/public_html/cs2303assig3
