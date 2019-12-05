# Breadth First Seearch (BFS)

This program consists of code that implements the breadth first search (BFS)
algorithm. Additionally, a random input generator is included for robust 
testing. 

The already compiled program can be executed by by simply running ./driver in
the command line. This runs the BFS and random input testing code. Command line
arguments can be added to alter the testing parameters:

-s k — where k is an integer ≥ 2. The number of streets should be a random integer 
in [2, k]. If this option is not specified, you should use a default of k = 10; that 
is, the number of streets should be a random integer in [2, 10].

-n k — where k is an integer ≥ 1. The number of line-segments in each street should 
be a random integer in [1, k]. Default: k = 5.

-l k — where k is an integer ≥ 5. Your process should wait a random number w seconds, 
where w is in [5, k] before generating the next (random) input. Default: k = 5.

-c k — where k is an integer ≥ 1. Your process should generate (x, y) coordinates such 
that every x and y value is in the range [−k, k]. For example, if k = 15, all of your 
coordinate values should be integers between −15 and 15. Default: k = 20.

In order to execute only the BFS alogirth the driver.cpp files should be altered by
simply disconnecting the pipe to rgen.

To compile the code: Compile bfs.cpp and rgen.cpp initially, then run the makefile
by executing "make" in the command line, which will run the driver program. 