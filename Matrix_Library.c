#include <stdio.h>
#include <stdlib.h>

struct dynamic_array
{
    int size;
    int capacity;
    int data;
};

struct header_array
{
    int size;
    int capacity;

    //'data' will store a pointer to a dynamic array, which is defined above.
    struct dynamic_array* data;
};

enum orientation {
    ROW,
    COL
};

/**
 * Initialize a Matrix with the number of rows and columns taken as arguments
 * 
 * Inputs:  Rows - number of rows
 *          Cols - number of cols
 *          dir  - whether the matrix will be traversable in row or column major format
 * 
 * outputs: returns a matrix with the input dimension
 *   
 * 
*/
int Matrix_Init (int rows, int cols, enum orientation orient) {
    //initialize a header array
    struct header_array* headptr = malloc(sizeof(void*)*rows);
    headptr->capacity = rows;
    printf("headptr address: %p \n", &headptr);

    
    for(int x = 0; x < headptr->capacity; x++) {
        
    };

    //populate the header array with dynamic arrays (these will house the contents of the matrix)
    
    

}




int main() {
    //test data will go here
    enum orientation orient = ROW;
    Matrix_Init(4,4,orient);

}
