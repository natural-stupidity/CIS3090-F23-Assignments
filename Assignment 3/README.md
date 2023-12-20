Student Name:   Michael Sirna
Student Number: 1094947


--------------- Notes ---------------

- The makefile compiles 4 executables:
  - boids: The non-graphical version of the serial boids program.
  - boidsomp: The non-graphical version of the parallel (OMP) boids program.
  - boidsG: The graphical version of the serial boids program.
  - boidsompG: The graphical version of the parallel (OMP) boids program.


----------- Usages / Syntax -----------

Usage 1: ./boids <number of iterations>
  - Will run the non-graphical version of the serial boids program

Usage 2: ./boidsomp <number of iterations>
  - Will run the non-graphical version of the parallel (OMP) boids program

Usage 3: ./boidsG
  - Will run the graphical version of the serial boids program
  - Press q or use Ctrl-C to quit.

Usage 4: ./boidsompG
  - Will run the graphical version of the parallel (OMP) boids program
  - Press q or use Ctrl-C to quit.


--------------- Results ---------------

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





