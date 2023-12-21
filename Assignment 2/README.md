# CIS 3090 Assignment 2

## How to run:

1. Open the folder / files in an IDE and run:
```
make
```

2. To run the program, use the following command:
```
mpirun[optional: -n < number of processes>] ./a2 [optional: -s <size of board>]
```
Note: If -n is not specified, the default number of processes will be used, which depends on your machine.

## Assignment Description:
Write an MPI program that implements Conways' game of life.

Your program should run between one and four processes which will be defined by the user on the command line. The user can also define the board size.

The program will print each generation of the game to the screen. The initial generation is 

Each process will be responsible for calculating an equal part of the game board. The program will run with between 1 and 4 processes.

You do not need to run any timing tests for this assignment. Run the program for ten generations of the game. Print the ten boards to stdout.

### Conway's Game of Life
It is a cellular automata that runs on a two dimensional board. It follows a simple set of rules to create complex patterns. You can read about it here:
    https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life    
and you can see a demo of it running here:
    https://copy.sh/life/

The board is randomly initialized. Each square will have a probability of being occupied when the game starts. Pick a probability that tends to work well when you test it. 

The default board size will be 24 by 24 cells.

The rules for the game are based on how many neighbours are adjacent to
each cell (square) on the board.  There are potentially eight neighbours
for each cell (up, down, left, right, and four diagonals). There are fewer
neighbours along the edges of the board. The edges are counted as empty
squares.

In each generation a new pattern is created on the board. The new generation
is based on the pattern of the old generation.

The rules can be summarized as:
- a cell with two or three neighbours is copied to the next generation
- an empty cell with three neighbours is occupied in the next generation
- all other cells are emptied on the next generation

You will need two boards to play the game. These will be arrays. The current board and the board used to store the next generation. Do not calculate the next generation by overwriting the current board.

Mark the occupied cells on the board with the number of the  process that calculated that cell. This should demonstrate how much of the board is calculated by each process. An occupied cell will have a number from 1 to 4 stored in it.

### Command Line Arguments
The command line arguments are:
```
  -n #   -indicates the number of processes to use, the # should be 1 to 4
  -s #   -size of the board, the number will be used for both the width and height
```
Both arguments are optional.  The default number of processes is 1. The default board size is 24x24.
