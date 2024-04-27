#include <stdio.h>
#include <stdlib.h>

struct dynamic_array
{
    int size;
    int capacity;
    int data[];
};

struct header_array
{
    int size;
    int capacity;

    //'data' will store a pointer to a dynamic array, which is defined above.
    struct dynamic_array* data[];
};

enum orientation {
    ROW,
    COL
};

/**
 * Initialize a Matrix with the number of rows and columns taken as arguments.
 * 
 * Inputs:  Rows - number of rows.
 *          Cols - number of cols.
 *          dir  - whether the matrix will be traversable in row or column major format.
 * 
 * outputs: returns a matrix with the input dimension.
 * 
*/
struct header_array* Matrix_Init (int rows, int cols, enum orientation orient) {
    
    if(rows < 0 || cols < 0) {
        printf("Error: negative numbers are not valid inputs. please try again");
    }
    
    
    //initialize a header array
    if(orient == ROW) {
        struct header_array* head_ptr = (struct header_array*)malloc(sizeof(void*)*rows);
        head_ptr->capacity = rows;
        printf("headptr address: %p \n", &head_ptr);

        //populate the header array with dynamic arrays (these will house the contents of the matrix)
        for(int x = 0; x < head_ptr->capacity; x++) {

            struct dynamic_array* matrix_row_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*cols);
            matrix_row_ptr->capacity = cols;
            head_ptr->data[x] = matrix_row_ptr;

            head_ptr->size = x + 1;
        };

        printf("Matrix created successfully!\n");
        return head_ptr;

    }
    else {

        struct header_array* head_ptr = (struct header_array*)malloc(sizeof(void*)*cols);
        head_ptr->capacity = cols;
        printf("headptr address: %p \n", &head_ptr);

        //populate the header array with dynamic arrays (these will house the contents of the matrix)
        for(int x = 0; x < head_ptr->capacity; x++) {

            struct dynamic_array* matrix_row_ptr = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*rows);
            matrix_row_ptr->capacity = rows;
            head_ptr->data[x] = matrix_row_ptr;

            head_ptr->size = x + 1;
        };

        printf("Matrix created successfully!\n");
        return head_ptr;

    }
}


/**
 * 
 * Will return the number of rows in a given matrix.
 * 
 * inputs:  head_ptr - the pointer to the header array of the matrix.
 *          orient   - whether the matrix is oriented row or column major.
 * 
 * outputs: returns an integer with the number of rows in the given matrix.
 * 
*/
int get_rows(struct header_array* head_ptr, enum orientation orient) {

    if(orient == ROW) {
        printf("number of rows: %d\n", head_ptr->capacity);
    }
    else {
        printf("number of rows: %d\n", head_ptr->data[0]->capacity);
    }
    return 0;
}

/**
 * 
 * Will return the number of columns in a given matrix.
 * 
 * inputs:  head_ptr - the pointer to the header array of the matrix.
 *          orient   - whether the matrix is oriented row or column major.
 * 
 * outputs: returns an integer with the number of columns in the given matrix.
 * 
*/
int get_columns(struct header_array* head_ptr, enum orientation orient) {

    if(orient == ROW) {
        printf("number of columns: %d\n", head_ptr->data[0]->capacity);
    }
    else {
        printf("number of columns: %d\n", head_ptr->capacity);
    }
    return 0;
}

int main() {
    //test data will go here
    enum orientation orient = ROW;
    struct header_array* head_ptr = Matrix_Init(5,-3,orient);
    get_rows(head_ptr, orient);
    get_columns(head_ptr, orient);

}
