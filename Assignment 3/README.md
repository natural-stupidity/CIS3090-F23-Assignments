# CIS 3090 Assignment 3

## How to run:

1. Open the folder / files in an IDE and run:
```
make
```
The makefile compiles 4 executables:
  - boids: The non-graphical version of the serial boids program.
  - boidsomp: The non-graphical version of the parallel (OMP) boids program.
  - boidsG: The graphical version of the serial boids program.
  - boidsompG: The graphical version of the parallel (OMP) boids program.

2. To run the program, use one of the following commands:
  - To run the NON GRAPHICAL SERIAL program
    ```
    ./boids <number of iterations>
    ```
  - To run the NON GRAPHICAL PARALLEL version, run:
    ```
    ./boidsomp <number of iterations>
    ```
  - To run the GRAPHICAL SERIAL version, run:
    ```
    ./boidsG
    ```
  - To run the GRAPHICAL PARALLEL version, run:
    ```
    ./boidsompG
    ```
**Note: For the graphical versions, type "q" or "Ctrl-C" to exit the program.**

## Assignment Description:
Complete the sample code provided and implement the three rules for a Boids system.
Once the program is working in serial, add the OpenMP directives to allow it to
run in parallel. 

The sample code will compile and run but it is not work correctly.  Add the code and
the OpenMP directives in the locations that are commented in the boids.c file. Also add code
to time the execution of the parallel code in the main routine. 

There are instructions in the boids.c file on how to develop the assignment. Follow these
instructions. In particular, there are restrictions on which data structures to use and
how to organize the code which you must follow when writing your code.

A tutorial describing the three rules for Boids is available at:
    http://www.kfish.org/boids/pseudocode.html
Implement the three main rules described on this page. Most of the suggested parameters
for the algorithm described on this page are reasonable. The world size is 100x100. 
It is possible for the boids to temporarily move outside this space. They will not be
drawn but this wont create any problems.  A reasonable distance between boids for rule 2 is 5.0
but other small values will work. 

A fourth rule is implemented in the sample code. Leave this code in the program. This is called
the "Tendency towards a particular place" on the boids tutorial web page. It causes the
flock to move between two points on the screen. It is also an example for how the other rules
can be implemented. 

Test the boidsomp program with different numbers of iterations. Determine if there
is a size when the parallel version is faster than the serial version. 
The boidsomp program will take a single command line argument which is the 
number of iterations. There are no other command line arguments. 

## Results
```
All times below are in seconds.

Iterations      Serial      Parallel (OMP)
50              0.008       0.001
100             0.015       0.003
500             0.069       0.018
1000            0.119       0.037
5000            0.596       0.134
10000           1.204       0.248
50000           5.654       1.372
100000          11.321      2.768
500000          57.483      14.105
1000000         116.793     25.968
```





