# CIS 3090 Assignment 1

## How to run:

1. Open the folder / files in an IDE and run:
```
make
```
This command will create three programs: ray, data, and task.
  - **ray:** The serial version.
  - **data:** The data parallelism version.
  - **task:** The task parallelism version.
2. To run the program, use one of the following commands:
  - To run the SERIAL version, run:
    ```
    ./ray <-i iterations> <-cube | -points #>
    ```
  - To run the DATA PARALLELISM version, run:
    ```
    ./data <-i iterations> <-cube | -points #>
    ```
  - To run the TASK PARALLELISM version, run:
    ```
    ./task <-i iterations> <-cube | -points #>
    ```

## Assignment Description:
Add Pthreads to a ray tracing program to implement two common forms of parallel algorithms.

### 1. Data Parallelism
Add Pthreads to the ray.c program to implement data parallelism. Name
this program data.c.

This algorithm will require the threads to calculate separate areas of the
the output image. The image is stored in an array which is named img
and is allocated in the main routine. 

The program is run on the command line and uses parameters to set
the scale of the image and the number of threads.

The usage for the program is described in the readme.txt.

Each thread should be used to calculate a proportional amount
of the image. For example, if there are two threads then each one
should calculate half of the image. If there are three threads then each
one should calculate one third of the image.

The area of the program where you need to add the Pthreads is marked
with the comments:
```
        /*** start timing here ****/
        /*** end timing here ****/
```
Execute the Pthreads between these comments. You will need to add other code
to manage the threads before and after these comments.

The ray traced image is calculated using two for loops which correspond to
the height and width of the final image. Each pass through the loops calculates
one pixel of the final image. You will need to divide these operations over
multiple threads so each thread calculates approximately the same number of
pixels. Each thread will actually be performing the same operations but it
will do so for a different section of the image (which is really a different
section of the img data structure). 

Name your C program data.c and the executable data. 


### 2. Task Parallelism
This program also starts with the ray.c program but instead of having
all threads perform the same actions on a different part of the image,
each thread should perform a part of a calculation. The most likely place
where this can be applied is to the smaller loops used to render the
image (lines 254-340). You can also consider if any of the functions
will benefit from the use of threads.

To be clear, you should not divide the image into sections and use threads
to calculate parts of the image as you did for Part 1 of this assignment.
If you are trying to parallelize the following two lines of code then you
are making a mistake.
```
   for(y=0;y<HEIGHT;y++){
      for(x=0;x<WIDTH;x++){
```
The above two lines are the focus of Part 1 - Data Parallelism. 

This is a more difficult task than applying data parallelism to the ray.c
program. Your program may not run faster once Pthreads have been added.
This is expected because ray tracing is an application which is better
suited to data parallelism then task parallelism. 

Name your C program task.c and the executable task. 


### 3. Timing Tests
Add code to the data.c and task.c programs to time the performance of the
systems. Once this is done run several tests to show the performance increase
or decrease of the two approaches to parallelism. 

Submit a file named results.txt which contains timing results for the data.c and
task.c programs when run using a variety of scaling factors and numbers of
threads. Present these results in two tables with number of threads on the
horizontal axis and scale on the vertical axis. For example:

```
data.c Results
    Threads        1    2    3    4 ...
Scale
   1
   2
   3
   ...
```
Choose a reasonable number of threads and scale values to test your program.
Provide a description in the results.txt file of what the the timing tests
suggest. Is there a point when number of threads or the scale of the image
benefits from the use of Pthreads? Is there an image size that is too small
to benefit from the use of threads? Is task parallelism beneficial for this
problem?

Don't leave large image.ppm output files in your directory. That can take up
a lot of space and serve no purpose. When running timing tests do not use the
-o flag. 

Note that if a lot of people are using the server simultaneously then the
program's performance will likely be poorer and possibly more variable than
if fewer people are simultaneously running programs. This means that testing
on the server may be difficult the night the assignment is due. You can run the
timing tests on another system as long as you provide information about
the testing platform in your results.txt file. This would include the
type or processor, number of cores it supports, clock speed, and amount of
memory in the testing platform.
 
The ray.c program contains the following comments indicating where to place
timing code.
```
        /*** start timing here ****/

        /*** end timing here ****/
```
After the end comment your program should print out the time it spent
running the code between these comments. You will be calculating the
time spent in rendering the image. 

The code to create the output file is not within the timed section of
the program. Do not move the code which writes the output file into the
timing tests.  It will not benefit from the use of threads and may mask
the performance improvements achieved through their use.
