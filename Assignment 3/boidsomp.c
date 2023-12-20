// Michael Sirna
// 1094947
// 2023-11-10
// CIS3090 Assignment 3

/* Boids using ASCII graphics
        -original NCurses code from "Game Programming in C with the Ncurses Library"
         https://www.viget.com/articles/game-programming-in-c-with-the-ncurses-library/
         and from "NCURSES Programming HOWTO"
         http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
        -Boids algorithms from "Boids Pseudocode:
         http://www.kfish.org/boids/pseudocode.html
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#ifndef NOGRAPHICS
#include <ncurses.h>
#include <unistd.h>
#endif

#define DELAY 50000

// population size, number of boids
#define POPSIZE 50
// maximum screen size, both height and width
#define SCREENSIZE 100

// boid location (x,y,z) and velocity (vx,vy,vz) in boidArray[][]
#define BX 0
#define BY 1
#define BZ 2
#define VX 3
#define VY 4
#define VZ 5

#ifndef NOGRAPHICS
// maximum screen dimensions
int max_y = 0, max_x = 0;
#endif

// location and velocity of boids
float boidArray[POPSIZE][6];

// change in velocity is stored for each boid (x,y,z)
// this is applied after all changes are calculated for each boid
float boidUpdate[POPSIZE][3];

// Create a separate array to store the coordinates for each boid in the population based on each rule
float boidRules[3][POPSIZE][3];

#define DEBUG_LOG 0
char debug[128];

void initBoids() {
    int i;
    // calculate initial random locations for each boid, scaled based on the screen size
    for (i = 0; i < POPSIZE; i++) {
        boidArray[i][BX] = (float)(random() % SCREENSIZE);
        boidArray[i][BY] = (float)(random() % SCREENSIZE);
        boidArray[i][BZ] = (float)(random() % SCREENSIZE);
        boidArray[i][VX] = 0.0;
        boidArray[i][VY] = 0.0;
        boidArray[i][VZ] = 0.0;
    }
}

#ifndef NOGRAPHICS
int drawBoids() {
    int c, i;
    float multx, multy;

    // update screen maximum size
    getmaxyx(stdscr, max_y, max_x);

    // used to scale position of boids based on screen size
    multx = (float)max_x / SCREENSIZE;
    multy = (float)max_y / SCREENSIZE;

    clear();

    // display boids
    for (i = 0; i < POPSIZE; i++) {
        mvprintw((int)(boidArray[i][BX] * multy), (int)(boidArray[i][BY] * multx), "o");
    }

    if (DEBUG_LOG)
        mvprintw(0, 0, debug);

    refresh();

    usleep(DELAY);

    // read keyboard and exit if 'q' pressed
    c = getch();
    if (c == 'q')
        return (1);
    else
        return (0);
}
#endif

/** A function that applies rule 1 (Move towards the centre of the flock) to the array
 * 
 *  @param boid - Which boid in the population we're applying this rule to.
*/
void rule1(int boid) {
    int i, j;
    float c[3];
    memset(c, 0, sizeof(int) * 3);

    // Scans all boids except for the one we're looking at.
    // We then take those boid's points and add them to the centre coords array.
    for (i = 0; i < POPSIZE; i++) {
        if (i != boid) {
            for (j = 0; j < 3; j++) {
                c[j] += boidArray[i][j];
            }
        }
    }

    // Add the calculate values to the boid's index in the boidsRule array.
    for (i = 0; i < 3; i++) {
        boidRules[0][boid][i] = ((c[i] / (POPSIZE - 1)) - boidArray[boid][i]) / 150.0;
    }
}

/** Calculates the distance between points - p1 and p2
 * 
 *  @param p1 - The first point
 *  @param p2 - The second point.
*/
float dist(float *p1, float *p2) {
    int i;
    float sum = 0;
    for (i = 0; i < 3; i++) {
        float x = p2[i] - p1[i];
        sum += x * x;
    }
    return sqrt(sum);
}

/** A function that applies rule 2 (Avoid the other boids) to the array
 * 
 *  @param boid - Which boid in the population we're applying this rule to.
*/
void rule2(int boid) {
    int i, j;
    float c[3];
    memset(c, 0, sizeof(int) * 3);

    // Scans all boids except for the one we're looking at.
    // If that boid is closeby (has a distance of < 5.0) then we make the current boid
    // "move away" by subtracting it's distance slightly
    for (i = 0; i < POPSIZE; i++) {
        if (i != boid && dist(boidArray[boid], boidArray[i]) < 5.0) {
            for (j = 0; j < 3; j++) {
                c[j] -= (boidArray[i][j] - boidArray[boid][j]) / 5.0;
            }
        }
    }

    // Add the calculate values to the boid's index in the boidsRule array.
    for (i = 0; i < 3; i++) {
        boidRules[1][boid][i] = c[i];
    }
}

/** A function that applies rule 3 (Match velocity of other boids) to the array
 * 
 *  @param boid - Which boid in the population we're applying this rule to.
*/
void rule3(int boid) {
    int i, j;
    float v[3];

    // Scans all boids except for the one we're looking at.
    // From there, we get the next values for that boid and add it to the v array
    // This v is not the actual velocity, but more a "perceived velocity"
    for (i = 0; i < POPSIZE; i++) {
        if (i != boid) {
            for (j = 0; j < 3; j++) {
                v[j] += boidArray[i][j + 3];
            }
        }
    }

    // Add a small portion (about an 8th) to get the perceived velocity.
    for (i = 0; i < 3; i++) {
        v[i] = ((v[i] / (POPSIZE - 1)) - boidArray[boid][i + 3]) / 8.0;
    }

    // Add the calculate values to the boid's index in the boidsRule array.
    for (i = 0; i < 3; i++) {
        boidRules[2][boid][i] = v[i];
    }
}

// Assign a function that runs all of the functions since this is faster.
void (*rules[3])(int boid) = {rule1, rule2, rule3};

// move the flock between two points
// you can optimize this funciton if you wish, or you can replace it and move it's
//    functionality into another function
void moveFlock() {
    int i;
    static int count = 0;
    static int sign = 1;
    float px, py, pz;  // (x,y,z) point which the flock moves towards

    // pull flock towards two points as the program runs
    // every 200 iterations change point that flock is pulled towards
    if (count % 200 == 0) {
        sign = sign * -1;
    }
    if (sign == 1) {
        // move flock towards position (40,40,40)
        px = 40.0;
        py = 40.0;
        pz = 40.0;
    } else {
        // move flock towards position (60,60,60)
        px = 60.0;
        py = 60.0;
        pz = 60.0;
    }
    // add offset (px,py,pz) to each boid location (x,y,z) in order to pull it
    // towards the current target point
    for (i = 0; i < POPSIZE; i++) {
        boidUpdate[i][BX] = (px - boidArray[i][BX]) / 200.0;
        boidUpdate[i][BY] = (py - boidArray[i][BY]) / 200.0;
        boidUpdate[i][BZ] = (pz - boidArray[i][BZ]) / 200.0;
    }
    count++;
}

void moveBoids() {
    int i, j, k;

    /*** Your code goes here ***/
    /*** add the code to implement the three boids rules ***/
    /*** do not change any other code except to add timing to the main() routine ***/
    /*** do not replace the data structures defined in this program ***/
    /*** omp code should be used here ***/
    /*** you can call other functions from this location ***/

// OpenMP pragma for the for loop
// The for loops goes through all of the boids, and runs them through the rules.
#pragma omp parallel for num_threads(3)
    for (i = 0; i < 3; i++)
        for (j = 0; j < POPSIZE; j++)
            rules[i](j);

    moveFlock();

    // sprintf(debug, "vel == %.1lf %.1lf", boidUpdate[0][0], boidUpdate[0][1]);

    // move boids by calculating updated velocity and new position
    // you can optimize this code if you wish and you can add omp directives here
    // #pragma omp parallel for num_threads(4)
    for (i = 0; i < POPSIZE; i++) {
        // update velocity for each boid using value stored in boidUpdate[][]
        boidArray[i][VX] += boidUpdate[i][BX];
        boidArray[i][VY] += boidUpdate[i][BY];
        boidArray[i][VZ] += boidUpdate[i][BZ];
        
        // Update the position for each boid with the values calculated in each rule.
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                boidArray[i][3 + k] += boidRules[j][i][k];
            }
        }

        // update position for each boid using newly updated velocity
        boidArray[i][BX] += boidArray[i][VX];
        boidArray[i][BY] += boidArray[i][VY];
        boidArray[i][BZ] += boidArray[i][VZ];
    }
}

int main(int argc, char *argv[]) {
    int i, count;

#ifndef NOGRAPHICS
    // initialize curses
    initscr();
    noecho();
    cbreak();
    timeout(0);
    curs_set(FALSE);
    // Global var `stdscr` is created by the call to `initscr()`
    getmaxyx(stdscr, max_y, max_x);
#endif

    // place boids in initial position
    initBoids();

    // draw and move boids using ncurses
    // do not calculate timing in this loop, ncurses will reduce performance
#ifndef NOGRAPHICS
    while (1) {
        if (drawBoids() == 1)
            break;
        moveBoids();
    }
#endif

    // calculate movement of boids but do not use ncurses to draw
    // this is used for timing the parallel implementation of the program
#ifdef NOGRAPHICS
    count = 1000;
    // read number of iterations from the command line
    if (argc == 2)
        sscanf(argv[1], "%d", &count);
    printf("Number of iterations %d\n", count);

    /*** Start timing here ***/
    /*** omp code can be used here ***/
    struct timeval start, finish;
    double elapsed;

    gettimeofday(&start, NULL);

    for (i = 0; i < count; i++) {
        moveBoids();
    }
    /*** End timing here ***/
    /*** print timing results ***/
    gettimeofday(&finish, NULL);

    elapsed = (double)(finish.tv_sec - start.tv_sec);
    elapsed += (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
    // elapsed *= 1000;

    printf("time taken: %.3lfs\n", elapsed);

#endif

#ifndef NOGRAPHICS
    // shut down curses
    endwin();
#endif
}