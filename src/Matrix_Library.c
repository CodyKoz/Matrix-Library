#include <stdio.h>
#include <stdlib.h>
#include <Matrix_Library.h>



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

    //orient stores the orientation of the matrix. will determine how the matrix is iterated through in other functions
    enum orientation orient;

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
 *          orient  - whether the matrix will be traversable in row or column major format.
 * 
 * outputs: returns a matrix with the input dimensions and orientation
 * 
*/
void* matrix_init (int rows, int cols, enum orientation orient) {

    //error handling: check for negative matrix dimensions. will set temp to 0 if either dimension is negative, or set temp to 1 if dimensions are in-bounds.
    if(rows < 0 || cols < 0) {
        printf("Error: negative numbers are not valid matrix dimensions. please try again.\n");
        void* neg_dim = NULL;
        return neg_dim;
    }
    
    //error handling: check for non-integer dimensions. will set temp to 0 if either dimension is a whole number, or set temp to 1 if dimensions are in-bounds.
    //'rows' and 'cols' are casted implicitly to an integer by the function parameters, and will use the whole number part of the input value.
    //this block of code exists to handle any potiential non-integer value errors caused by the implicit cast. 
    else if(rows % 1 != 0 || cols % 1 != 0) {
        printf("Error: non-integer numbers are not valid matrix dimensions. please try again.\n");
        void* neg_dim = NULL;
        return neg_dim;
        
    }

    //initialize a header array
    if(orient == ROW) {
        struct header_array* head_ptr = (struct header_array*)malloc(sizeof(void*)*rows);
        head_ptr->capacity = rows;
        head_ptr->orient = orient;
        
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
    else if(orient == COL) {

        struct header_array* head_ptr = (struct header_array*)malloc(sizeof(void*)*cols);
        head_ptr->capacity = cols;
        head_ptr->orient = orient;
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
 * this method will be called when user is done using the matrix. it will free any memory allocated for the input matrix.
 * 
 * Inputs:  head_ptr - the pointer to the header array of the matrix.
 *          orient   - the orientation of the matrix. this matters for determining the order in which memory is freed.
 * 
 * Outputs: returns 1 upon success, or 0 upon failure.
 * 
*/
int free_matrix (struct header_array* head_ptr, enum orientation orient) {

}


/**
 * 
 * checks if a matrix exists, then returns the number of rows in a given matrix if it does.
 * 
 * inputs:  head_ptr - the pointer to the header array of the matrix.
 *          orient   - whether the matrix is oriented row or column major.
 * 
 * outputs: returns an integer with the number of rows in the given matrix.
 *          returns NULL if unsuccessful.
 * 
*/
int get_rows(struct header_array* head_ptr) {
    if(head_ptr == NULL){
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return NULL;
    }
    else {
        if(head_ptr->orient == ROW) {
            int num_of_rows = head_ptr->capacity;
            printf("number of rows: %d\n", num_of_rows);
            return num_of_rows;
        }
        else {
            int num_of_rows = head_ptr->data[0]->capacity;
            printf("number of rows: %d\n", num_of_rows);
            return num_of_rows;
        }
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
 *          returns NULL if unsuccessful.
 * 
*/
int get_columns(struct header_array* head_ptr) {

    if(head_ptr == NULL){
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return NULL;
    }
    else {
        if(head_ptr->orient == ROW) {
            int num_of_cols = head_ptr->data[0]->capacity;
            printf("number of columns: %d\n", num_of_cols);
            return num_of_cols;
        }
        else {
            int num_of_cols = head_ptr->capacity;
            printf("number of columns: %d\n", num_of_cols);
            return num_of_cols; 
        }
        
    }
}


/**
 * 
 * print element will take in coordinates for a location in the matrix, and will print the element at those coordinates to the console.
 * 
 * Inputs:  head_ptr - the pointer to the header array of the matrix.
 *          row      - the row of the desired element.
 *          column   - the column of the desired element.
 * 
 * outputs: - prints the element at the desired location to the console.
 *          - returns element at desired location upon success, and NULL for failure.
 * 
*/
int print_element(struct header_array* head_ptr, int row, int column) {
    
    //outtermost if-else handles differences between row/column major matrices.
    //rows and columns need to be switched in final print statement due to the different orientations.
    if (head_ptr->orient == ROW) {
        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return NULL;
        }
        //error handling: checking that the user-given coordinates are within the bounds of the matrix
        else if(row < 0 || row > head_ptr->capacity || row < 0 || column < 0 || column > head_ptr->data[0]->capacity){
            printf("Error: coordinates provided do not exist within the matrix.\n");
            return NULL;
        }

        
        //if matrix exists and coordinates are in-bounds, then function will print desired element to console and return 1.
        else {
            int elem_to_print = head_ptr->data[row]->data[column];
            printf("element at (%d,%d): %d", row, column, elem_to_print);
            return elem_to_print;
        }

    }
    else {
        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return NULL;
        }
        //error handling: checking that the user-given coordinates are within the bounds of the matrix
        else if(row < 0 || row > head_ptr->capacity || row < 0 || column < 0 || column > head_ptr->data[0]->capacity){
            printf("Error: coordinates provided do not exist within the matrix.\n");
            return NULL;
        }


        //if matrix exists and coordinates are in-bounds, then function will print desired element to console and return 1.
        else {
            int elem_to_print = head_ptr->data[column]->data[row];
            printf("element at (%d,%d): %d", row, column, elem_to_print);
            return elem_to_print;
        }
    }

    

}


/**
 * 
 * Print row will take in a row index from the user and print the elements to the console.
 * 
 * Inputs:  head_ptr - pointer to the header array of the desired matrix.
 *          row      - the index of the desired row to print elements from.
 * 
 * Outputs: - prints elements of desired row to console.
 *          - will return a 1 upon success or NULL if failed
 *
*/
int print_row(struct header_array* head_ptr, int row) {

    if (head_ptr->orient == ROW) {

        //error handling: check if matrix exists. will continue function if it does, or return 0 if it does not.
        if(head_ptr == NULL){
            printf("Error: matrix does not exist. please create a matrix and try again.\n");
            return NULL;
        }
        //checks to make sure the desired row exists within the matrix / is in bounds. will continue function if it does, or will return 0. 
        else if(row > head_ptr->capacity || row < 0) {
            printf("Error: desired row is out of bounds. please try again.\n");
            return NULL;
        }
        //if error handling is passed, then funcion continues as expected here.
        else {
            for(int j = 0; j < head_ptr->data[row]->capacity; j++) {
                printf("[%d]", head_ptr->data[row]->data[j]);
            }
            printf("\n");
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
 * Print column will take in a row index from the user and print the elements to the console.
 * 
 * Inputs:  head_ptr - pointer to the header array of the desired matrix.
 *          column      - the index of the desired column to print elements from.
 * 
 * Outputs: - prints elements of desired column to console
 *          - will return a 1 upon success or 0 if failed
 *
*/
int print_column(struct header_array* head_ptr, int column) {

}


int main() {
    
    enum orientation orient_row = ROW;
    enum orientation orient_col = COL;
    struct header_array* head_ptr_row = Matrix_Init(5,5.8,orient_row);
    get_rows(head_ptr_row);
    get_columns(head_ptr_row);
    

}
