# CIS 3090 Assignment 4

## How to run:

1. Open the folder / files in an IDE and run:
```
make
```
The makefile will create 2 programs: graphics and ng
  - **graphics**: The non-graphical version program.
  - **ng**: The non-graphical version of the program.

2. To run the program, use one of the following commands:
  - To run the GRAPHICAL version: 
    ```
    oclgrind ./graphics [optional: <-i iterations>] <-cube | -points #>
    ```
  - To run the NON GRAPHICAL version: 
    ```
    oclgrind ./ng [optional: <-i iterations>] <-cube | -points #>
    ```
**Note: For the graphical versions, type "q" or "Ctrl-C" to exit the program.**

## Assignment Description:

Modify the starting code so it uses OpenCL to perform the matrix multiplication 
operations for a 3D graphics transformation. 

The starting code displays a rotating cube made of individual points.
It calculates the position of each point as it rotates and draws
them using character graphics. This is done using transformation
matrices for three dimensional graphics. 

The main data structures that you will need to access
are defined at the start of graphics.c. They are:
```
// number of points
int pointCount;
// array of points before transformation
float **pointArray;
// array of points after transformation
float **drawArray;
```
The two arrays contain are the locations of the points in three dimensions.
The first (pointArray) is their starting positions. The second array (drawArray)
contains the points in their position when they are displayed on the screen.
The starting set of points is not changed. It is used to create the set
of display points. The displayed points are calculated each
time the screen is updated.

There are other data structures in the program which you can modify if
you wish.

The starting code creates an executable named graphics and it shows the algorithm running with a
text based display. You should see the points rotating when running
this program.

The main loop that does most of the work when the program runs with
the graphical display is:
```
   while(1) {
      if (drawPoints() == 1) break;
      movePoints();
   }
```
The drawPoints() function updates the screen each time through the loop.
The movePoints() function calculates the new positions for the points.

There is a non-graphical version of the program which is not used in
this assignment. It uses the same main loop but without
calling the drawPoints() function. This performs all of the same matrix
operations but doesn't display the results. This main loop looks like this: 
```
   for(i=0; i<count; i++) {
      movePoints();
   }
```
You don't need to do anything with the non-graphical code. It will not be
tested.

Replace the loop that calculates the drawArray[][] in the movePoints()
function. This loops through the number of points (pointCount) and multiplies
each point by the transformation matrix to produce the coordinates where
the point will be drawn. The for loop should be replaced with a call
to a kernel. The point vectors and the transformation matrix
are passed into the kernel where they are multiplied. The results of
this are returned and drawn using the drawArray[][]. 


### Running the graphics.c Program
Once the code is compiled it is run using command line arguments.
```
These are:
    -i <count>         -this causes the program to run for <count> iterations
                       -for example ./graphics -i 1000 will run for 1000 iterations
                       -used for timing tests
    -cube              -draws the eight corners of the cube and rotates them
    -points <number>   -draw <number> points inside the cube
                       -this is useful to see the cube made of more points
                       -it's also useful for timing tests with larger numbers of points
                       for example, ./graphics -points 100000 creates a cube containing 100000 points 
```

To see the results of the program use the graphics program. For example:
```
    ./graphics -cube
```
will draw the cube with eight points (one at each corner). To see more
points use:
```
    ./graphics -points 10000
```
to see 10000 points rotating.

Points which are near the viewer are displayed using the character 'X'.
Points that are far from the viewer are displayed using the character '.'.
Points between these two are displayed using 'o'.

The -i flag that sets the number of iterations is only used in the
non-graphical version of the code so it will not be used in this assignment.

You will need to have the ncurses libraries installed.
