// Michael Sirna
// 1094947
// 2023-10-20
// CIS3090 Assignment 2

#include <mpi.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char * argv[]){
	int rank, numProcs, numRows = 24, numCols = 24, numGens = 10;

    // Init MPI stuff
    MPI_Init(&argc, &argv);
    MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &numProcs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Error checking for arguments
    if (argc != 1 && argc != 3) {
		if (rank == 0) 
            printf("\nERROR: Incorrect Syntax.\nUsage: mpirun[optional: -n < number of processes>] ./a2 [optional: -s <size of board>]\n\n");
        MPI_Finalize();
		return -1;
	}
    // Run srand so the generaltion isn't the same each time
    srand(time(NULL) + rank);

    // Set the number of rows and numCols if the argument is there.
    if (argc == 3){
        if (atoi(argv[2]) < 1) {
            if (rank == 0) 
                printf("\nInvalid size for the grid!\nExiting program....\n\n");
            MPI_Finalize();
            return -1;
        }
        numRows = atoi(argv[2]);
        numCols = atoi(argv[2]);
    }

    // Print some info
    if (rank == 0){
        printf("\nNumber of Processes: %d\n", numProcs);
        printf("Grid Size: %d x %d\n", numRows, numCols);
    }

    MPI_Bcast(&numRows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numCols, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&numGens, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Init the number of rows each process will take
    int numRowsLocal = numRows / numProcs;
    if (rank == numProcs - 1)
        numRowsLocal += numRows % numProcs;

    // We need an extra two rows - one for each side - so we can scan stuff properly
    int numRowsGhost = numRowsLocal + 2;
    int numColsGhost = numCols + 2;

    int currGrid[numRowsGhost][numColsGhost];
    int nextGrid[numRowsGhost][numColsGhost];

    // Init both grids to 0
    for (int i = 0; i < numRowsGhost; i++){
        for (int j = 0; j < numColsGhost; j++){
            currGrid[i][j] = 0;
            nextGrid[i][j] = 0;
        }
    }

    // Init the current grid
    for (int i = 1; i <= numRowsLocal; i++){
        for (int j = 1; j <= numCols; j++){
            currGrid[i][j] = (rand() % 2) ? rank + 1 : 0;
        }
    }

    // Get the neighbouring rows of the ranks (one above, one below)
    int upperNeighbour = (rank == 0) ? numProcs - 1 : rank - 1;
    int lowerNeighbour = (rank == numProcs - 1) ? 0 : rank + 1;

    // Go through all generations
    for (int gen = 1; gen <= numGens; gen++){
            
        // Send and receive the lower neighbour (lower to upper)
        MPI_Send(currGrid[numRowsLocal], numColsGhost, MPI_INT, lowerNeighbour, 0, MPI_COMM_WORLD);
        MPI_Recv(currGrid[0], numColsGhost, MPI_INT, upperNeighbour, 0, MPI_COMM_WORLD, &status);

        // Send and receive the upper neighbour (upper to lower)
        MPI_Send(currGrid[1], numColsGhost, MPI_INT,upperNeighbour, 0, MPI_COMM_WORLD);
        MPI_Recv(currGrid[numRowsLocal + 1], numColsGhost, MPI_INT, lowerNeighbour, 0, MPI_COMM_WORLD, &status);
    
        // Init ghost numCols
        for (int i = 0; i < numRowsGhost; i++){
            currGrid[i][0] = currGrid[i][numCols];
            currGrid[i][numCols + 1] = currGrid[i][1];
        }

        // If rank is not zero, send all the rows that this specific has.
        if (rank != 0){
            for (int i = 1; i <= numRowsLocal; i++){
                MPI_Send(&currGrid[i][1], numCols, MPI_INT, 0, 0, MPI_COMM_WORLD);
            }
        }

        // --- Displaying The Grid ---

        // Rank 0 takes care of printing the grid
        if (rank == 0){

            // Print the generation and then print all rows that rank 0 calculated.
            printf("\nGeneration %d\n", gen);
            for (int i = 1; i <= numRowsLocal; i++){
                for (int j = 1; j <= numCols; j++){
                    printf("%d ", currGrid[i][j]);
                }
                printf("\n");
            }

            // Print the rows that the other ranks took care of after receiving them.
            for (int sourceRank = 1; sourceRank < numProcs; sourceRank++){
                int numRecv = numRows / numProcs;
                if (sourceRank == numProcs - 1)
                    numRecv += numRows % numProcs;

                int buff[numCols];
                memset( buff, 0, numCols * sizeof(int) );
                
                for (int i = 0; i < numRecv; i++){
                    MPI_Recv(&buff[0], numCols, MPI_INT, sourceRank, 0, MPI_COMM_WORLD, &status);
                    for (int j = 0; j < numCols; j++){
                        printf("%d ", buff[j]);
                    }
                    printf("\n");
                }
            }
        }

        // --- Updating The Grids ---

        // Go through all the rows given to this rank
        for (int i = 1; i <= numRowsLocal; i++) {
            for (int j = 1; j <= numCols; j++) {
                int numActiveNeighbours = 0;

                // Go through all neighbouring cells
                for (int currentRow = i - 1; currentRow <= i + 1; currentRow++) {
                    
                    // Skip ghost rows on the top of bottom of the grid
                    if ((i == 1 && currentRow < 1 && rank == 0) || (i == numRowsLocal && currentRow > numRowsLocal && rank == numProcs - 1))
                        continue;

                    for (int currentCol = j - 1; currentCol <= j + 1; currentCol++) {
                        
                        // Skip the current cell and skip ghost columns on the sides
                        if ((currentRow == i && currentCol == j) || (j == 1 && currentCol < 1) || (j == numCols && currentCol > numCols))
                            continue;

                        // If this neighbour is active, increment the counter.
                        if (currGrid[currentRow][currentCol] > 0)
                            numActiveNeighbours++;
                    }
                }

                // If the current cell is "dead"
                if (currGrid[i][j] == 0){

                    // And has three neighbours, it becomes "alive"
                    if (numActiveNeighbours == 3)
                        nextGrid[i][j] =  rank + 1;

                    // Otherwise it remains "dead"
                    else
                        nextGrid[i][j] = 0; 
                }
                // If the current cell is "alive"
                else {

                    // And it has 2 or 3 active neighbours, it stays "alive"
                    if (numActiveNeighbours == 2 || numActiveNeighbours == 3)
                        nextGrid[i][j] = rank + 1;

                    // Otherwise, it "dies"
                    else
                        nextGrid[i][j] = 0;
                }
            }
        }

        // Copy next grid to current grid.
        for (int i = 1; i <= numRowsLocal; i++){
            for (int j = 1; j <= numCols; j++){
                currGrid[i][j] = nextGrid[i][j];
            }
        }
    }
    if (rank == 0) 
        printf("\n");
    MPI_Finalize();
    return 0;
}
