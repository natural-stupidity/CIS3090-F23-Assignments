// Michael Sirna
// 1094947
// 2023-11-24
// CIS3090 Assignment 4

__kernel void vectorMult(__global float * m1, __global float * m2, __global float * res, unsigned long int size) {
    int i = get_group_id(0);
    int col = get_local_id(0);
    float sum = 0;
    
    // For each element in the vector, multiply it with each element in a row of the matrix
    for (int element = 0; element < size; element++){
        sum += (m1[i * size + element] * m2[element * size + col]);
    }

    res[i * size + col] = sum;

    // scale the points for curses screen resolution
    if (col < 3){
        res[i * size + col + 0] *= 20;
        res[i * size + col + 0] += 50;
    }
    if (col < 2){
        res[i * size + col + 1] *= 20;
        res[i * size + col + 1] += 50;
    }
    if (col < 1){
        res[i * size + col + 2] *= 20;
        res[i * size + col + 2] += 50;
    }
}