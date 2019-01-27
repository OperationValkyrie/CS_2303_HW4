Jonathan Chang
CS 2303 C01 18
Assignment 4 qSim
README.txt

The program runs a simulation of a bank using customer and teller objects to calculate average times in the bank, effectiveness of tellers, and the maximum waiting time in order to compare a queueing system with a single queue or a separate queue for each teller. Customers and Tellers are stored as subclasses of the Event Object - each event object points to the next event in the event queue with a pointer of 0 meaning null or no event. The Event object also holds whether the event is a CustomerEvent or a TellerEvent each which hold boolean values to store the tellers or customers current state.

This program can be complied with the following command:
make qSim

This program can be run with the following command:
./qSim numCustomers numTellers simTime averageServiceTime (seed)
numCustomer:        (int) number of customers to simulate
numTellers:         (int) number of tellers to simulate
simTime:            (float) the total simulation time in minutes
averageServiceTime: (float) the average service time in minutes
seed:               (int) (optional) a seed to use

This program can be complied in Eclipse by right-clicking on the project name and clicking Build Project.

This program can be run in Eclipse by using a Run Configuration with at least 4 arguements specificed above.

There were two major complications in the development of this program. Firstly, these were some odd errors occuring because of subclasses and virtual functions so some functions had to be moved or copied over to their subclass. The qSimCustomerQueue had to have its own getLength() function since the program was returning the qSimEventQueue's length member instead which was separate from qSimCustomerQueue's desipte that qSimCustomerQueue was a subclass of qSimEventQueue. Anther odd problem occured with a single teller - since the event queue was empty eventLast was not being set property. There was a special if statement that had to account for that by setting both eventFirst and eventLast to 0.

All algorithms were taken from the assignment document.

Results were as follows:
For:
Total number of Customer: 200
Customer to Teller Ratio: 40:1 (5 tellers)
Simulation Time:          50
Average Service Time:     1.1 min

                        Common Queue  Seperate Queues
  Average Time in Bank:   2.30 min      4.13 min
  Standard Deviation:     0.74 min      2.03 min
  Total Service Time:   210.22 min    208.84 min
  Total Idle Time:       19.58 min      9.90 min

For:
Total number of Customer: 50
Customer to Teller Ratio: 10:1 (5 tellers)
Simulation Time:          50
Average Service Time:     2.7 min

                        Common Queue  Seperate Queues
  Average Time in Bank:   3.12 min      3.39 min
  Standard Deviation:     1.26 min      1.22 min
  Total Service Time:   124.85 min    139.80 min
  Total Idle Time:      106.33 min     93.52 min
 
It appears that for a low average service time, a higher number of customers, and ratio of customers to tellers the common queue is far more effective. The common queue has a far lower average time in bank of 2.30 min compared to 4.13 for the seperate queues; Furthermore, there is far less standard deviation 32 percent vs 49 percent. Oddly however, there is a greater total idle time of the tellers (19.58 min vs 9.90 min).

It appears that for a higher service time, a lower number of customers, and a lower ratio of customers ot tellers, both queues work very similarly. Both queues have equivalent average times in bank as well as standard deviations (3.12 min vs 3.39 min) (40 percent vs 36 percent). Tere was a difference in the total service time with the separte queues serving more and idling less.

Based on these results, it appears that a common queue is more effective in most circumstances ith better or equvalient average time in bank compared to serparate queues. It is likely that separate queues tend to have a higher standard deviation because while some customers might get stuck in the back of a line, others shoot straight to the front.
