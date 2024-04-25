#include <stdio.h>
#include <stdlib.h>

struct dynamic_Array
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

enum Major {
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
int Matrix_Init (int rows, int cols, enum Major dir) {
    //initialize a header array
    
    //populate the header array with dynamic arrays (these will house the contents of the matrix)

    

}




int main() {
    //test data will go here
    enum Major Row_Maj = ROW;


}
