# Michael Sirna
# 1094947
# 2023-11-10
# CIS3090 Assignment 3

all: boids boidsomp boidsG boidsompG

boids: boidsomp.c
	gcc boids.c -o boids -lm -DNOGRAPHICS

boidsomp: boidsomp.c
	gcc -fopenmp boidsomp.c -o boidsomp -lm -DNOGRAPHICS

boidsG: boids.c
	gcc boids.c -o boidsG -lncurses -lm 

boidsompG: boidsomp.c
	gcc boidsomp.c -o boidsompG -lncurses -lm 

clean:
	rm boids boidsomp boidsG boidsompG

