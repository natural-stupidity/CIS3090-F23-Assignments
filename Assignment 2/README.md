Note:
MPI uses all arguments up until the program name.
Because of that, argc and argv do not include MPI arguments, and I can't change the default number in the code (at least to how the instructions want it; [mpirun -n <number of processes> ./a2 -s <size of grid>])
If <-n #> is not included, the default number of processes is 4.