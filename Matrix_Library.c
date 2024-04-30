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
void* Matrix_Init (int rows, int cols, enum orientation orient) {

    //error handling: check for negative matrix dimensions. will set temp to 0 if either dimension is negative, or set temp to 1 if dimensions are in-bounds.
    int temp;
    if(rows < 0 || cols < 0) {
        printf("Error: negative numbers are not valid matrix dimensions. please try again.\n");
        temp = 0;
        void* neg_dim = NULL;
        return neg_dim;
        
    }
    
    //error handling: check for non-integer dimensions. will set temp to 0 if either dimension is a whole number, or set temp to 1 if dimensions are in-bounds.
    else if(rows % 1 == 0 || cols % 1 == 0) {
        printf("Error: non-integer numbers are not valid matrix dimensions. please try again.\n");
        temp = 0;
        void* neg_dim = NULL;
        return neg_dim;
        
    }
    else {
        temp = 1;
    }

    //initialize a header array
    if(orient == ROW && temp == 1) {
        struct header_array* head_ptr = (struct header_array*)malloc(sizeof(void*)*rows);
        head_ptr->capacity = rows;
        //printf("headptr address: %p \n", &head_ptr);

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
    else if(orient == COL && temp == 1) {

        struct header_array* head_ptr = (struct header_array*)malloc(sizeof(void*)*cols);
        head_ptr->capacity = cols;
        //printf("headptr address: %p \n", &head_ptr);

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
 * checks if a matrix exists, then returns the number of rows in a given matrix if it does.
 * 
 * inputs:  head_ptr - the pointer to the header array of the matrix.
 *          orient   - whether the matrix is oriented row or column major.
 * 
 * outputs: returns an integer with the number of rows in the given matrix.
 * 
*/
int get_rows(struct header_array* head_ptr, enum orientation orient) {
    if(head_ptr == NULL){
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return 0;
    }
    else {
        if(orient == ROW) {
            printf("number of rows: %d\n", head_ptr->capacity);
        }
        else {
            printf("number of rows: %d\n", head_ptr->data[0]->capacity);
        }
        return 1;
    }
}

/**
 * 
 * Checks if a matrix exists, then returns the number of columns in a given matrix if it does.
 * 
 * inputs:  head_ptr - the pointer to the header array of the matrix.
 *          orient   - whether the matrix is oriented row or column major.
 * 
 * outputs: returns an integer with the number of columns in the given matrix.
 * 
*/
int get_columns(struct header_array* head_ptr, enum orientation orient) {

    if(head_ptr == NULL){
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return 0;
    }
    else {
        if(orient == ROW) {
        printf("number of columns: %d\n", head_ptr->data[0]->capacity);
    }
    else {
        printf("number of columns: %d\n", head_ptr->capacity);
    }
    return 1;
    }
}


/**
 * 
 * print element will take in coordinates for a location in the matrix, and will print the element at those coordinates to the console.
 * 
 * Inputs:  head_ptr - the pointer to the header array of the matrix.
 *          row      - the row of the desired element.
 *          column   - the column of the desired element.
 *          orient   - the orientation of the matrix.
 * 
 * outputs: - prints the element at the desired location to the console.
 *          - returns 1 for success, and 0 for failure.
 * 
*/
int print_element(struct header_array* head_ptr, int row, int column, enum orientation orient) {
    
    //outtermost if-else handles differences between row/column major matrices.
    //rows and columns need to be switched in final print statement due to the different orientations.
    if (orient == ROW) {
        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return 0;
        }

        //error handling: checking that the user-given coordinates are within the bounds of the matrix
        else if(row < 0 || row > head_ptr->capacity || row < 0 || column < 0 || column > head_ptr->data[0]->capacity){
            printf("Error: coordinates provided do not exist within the matrix.\n");
            return 0;
        }
        //if matrix exists and coordinates are in-bounds, then function will print desired element to console and return 1.
        else {
            printf("element at (%d,%d): %d", row, column, head_ptr->data[row]->data[column]);
            return 1;
        }

    }
    else {
        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return 0;
        }

        //error handling: checking that the user-given coordinates are within the bounds of the matrix
        else if(row < 0 || row > head_ptr->capacity || row < 0 || column < 0 || column > head_ptr->data[0]->capacity){
            printf("Error: coordinates provided do not exist within the matrix.\n");
            return 0;
        }
        //if matrix exists and coordinates are in-bounds, then function will print desired element to console and return 1.
        else {
            printf("element at (%d,%d): %d", row, column, head_ptr->data[column]->data[row]);
            return 1;
        }
    }

    

}


/**
 * 
 * Print row will take in a row index from the user and print the elements to the console
 * 
 * Inputs:  head_ptr - pointer to the header array of the desired matrix
 *          row      - the index of the desired row to print elements from
 *          orient   - the orientation of the matrix, either row major or column major
 * 
 * Outputs: - prints elements of desired row to console
 *          - will return a 1 upon success or 0 if failed
 *
*/
int print_row(struct header_array* head_ptr, int row, enum orientation orient) {

    if (orient == ROW) {

        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return 0;
        }
        //checks to make sure the desired row exists within the matrix / is in bounds. will continue function if it does, or will return 0. 
        else if(row > head_ptr->capacity || row < 0) {
            printf("Error: desired row is out of bounds. please try again.\n");
            return 0;
        }
        //if error handling is passed, then funcion continues as expected here.
        else {
            for(int j = 0; j < head_ptr->data[row]->capacity; j++) {
                printf("[%d]", head_ptr->data[row]->data[j]);
            }
            return 1;
        }

    }
    else {

        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return 0;
        }
        //checks to make sure the desired row exists within the matrix / is in bounds. will continue function if it does, or will return 0. 
        else if(row > head_ptr->capacity || row < 0) {
            printf("Error: desired row is out of bounds. please try again.\n");
            return 0;
        }
        //if error handling is passed, then funcion continues as expected here.
        else {
            for(int j = 0; j < head_ptr->capacity; j++) {
                printf("[%d]", head_ptr->data[j]->data[row]);
            }
            return 1;
        }

    }
}


/**
 * 
 * Print column will take in a row index from the user and print the elements to the console
 * 
 * Inputs:  head_ptr - pointer to the header array of the desired matrix
 *          column      - the index of the desired column to print elements from
 *          orient   - the orientation of the matrix, either row major or column major
 * 
 * Outputs: - prints elements of desired column to console
 *          - will return a 1 upon success or 0 if failed
 *
*/
int print_column(struct header_array* head_ptr, int column, enum orientation orient) {

}


int main() {
    //test data will go here
    enum orientation orient_row = ROW;
    enum orientation orient_col = COL;
    struct header_array* head_ptr_row = Matrix_Init(5,3,orient_row);
    get_rows(head_ptr_row, orient_row);
    get_columns(head_ptr_row, orient_row);

}
