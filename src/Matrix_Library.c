#include <stdio.h>
#include <stdlib.h>
#include "../include/Matrix_Library.h"


//stores the size, capacity, and memory address of a dynamic array of unions
struct dynamic_array
{
    int size;
    int capacity;
    union data_val* values;
};

//used to store values in a matrix depending on data type
union data_val;

//determines the way a matrix is searched through 
enum orientation;

struct matrix {

    int rows;
    int columns;
    enum orientation orient;
    enum data_type data_type;
    struct dynamic_array* matrix_data;  

};

/**
 * @brief Initialize a Matrix with the number of rows and columns taken as arguments.
 * 
 * @param Rows - number of rows.
 * @param Cols - number of cols.
 * @param orient  - whether the matrix will be traversable in row or column major format.
 * @param data_type - what type of data the matrix can store. Integers, Floats, and Doubles are accepted.
 * 
 * @return returns a matrix with the input dimensions and orientation.
 * 
*/
void* matrix_init (int rows, int cols, enum orientation orient, enum data_type data_type) {

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
        
        //instantiate new matrix object, with a pointer to it
        struct matrix* new_matrix = (struct matrix*)malloc(sizeof(struct matrix)*1);
        new_matrix->rows = rows;
        new_matrix->columns = cols;
        new_matrix->orient = orient;
        new_matrix->data_type = data_type;

        //allocate memory for block of dynamic arrays and for the union arrays inside them
        new_matrix->matrix_data = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*rows);
        new_matrix->matrix_data->capacity = rows;
        for(int x = 0; x < new_matrix->matrix_data->capacity; x++) {

            new_matrix->matrix_data[x].values = (union data_val*)malloc(sizeof(union data_val)*cols);
            new_matrix->matrix_data[x].capacity = cols;
            new_matrix->matrix_data[x].size = 0;

            new_matrix->matrix_data->size += 1;
        }

        return new_matrix;

    }
    else {

        //instantiate new matrix object, with a pointer to it
        struct matrix* new_matrix = (struct matrix*)malloc(sizeof(struct matrix)*1);
        new_matrix->rows = rows;
        new_matrix->columns = cols;
        new_matrix->orient = orient;
        new_matrix->data_type = data_type;

        //allocate memory for block of dynamic arrays and for the union arrays inside them
        new_matrix->matrix_data = (struct dynamic_array*)malloc(sizeof(struct dynamic_array)*cols);
        new_matrix->matrix_data->capacity = cols;
        for(int x = 0; x < new_matrix->matrix_data->capacity; x++) {

            new_matrix->matrix_data[x].values = (union data_val*)malloc(sizeof(union data_val)*rows);
            new_matrix->matrix_data[x].capacity = rows;
            new_matrix->matrix_data[x].size = 0;

            new_matrix->matrix_data->size += 1;
        }

        return new_matrix;

    }

    
}


/**
 * 
 * @brief this function will free any memory allocated for a given matrix.
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * 
 * @return returns 1 upon success, or -1 upon failure.
 * 
*/
int free_matrix (struct matrix* matrix_in) {
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    else {
        //freeing the union arrays stored in each dynamic array struct
        for(int x = 0; x < matrix_in->matrix_data->capacity; x++) {
            free(matrix_in->matrix_data[x].values);
        }

        //freeing the memory block of dynamic arrays
        free(matrix_in->matrix_data);

        //freeing the memory allocated for the matrix struct
        free(matrix_in);

        return 1;
    }
}


/**
 * 
 * @brief checks if a matrix exists, then returns the number of rows in a given matrix if it does.
 * 
 * @param matrix_in the pointer to the matrix struct.
 * 
 * @return returns an integer with the number of rows in the given matrix. returns -1 if unsuccessful.
 * 
*/
int get_rows(struct matrix* matrix_in) {
    if(matrix_in == NULL){
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    else {
        return matrix_in->rows;
    }
}


/**
 * 
 * @brief checks if a matrix exists, then returns the number of columns in a given matrix if it does.
 * 
 * @param matrix_in the pointer to the matrix struct.
 * 
 * @return returns an integer with the number of columns in the given matrix. returns -1 if unsuccessful.
 * 
*/
int get_columns(struct matrix* matrix_in) {

    if(matrix_in == NULL){
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    else {
        return matrix_in->columns;
    }

}


/**
 * 
 * @brief this function will set an element to a given matrix at a given set of coordinates
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * @param row - the row the new element is to be set to. 
 * @param column - the column the new element is to be set to.
 * @param elem_to_set - the element that is to be set to the matrix.
 * 
 * @return returns 1 if successful, or -1 if unsuccessful
 * 
*/
int set_element(struct matrix* matrix_in, int row, int column, union data_val elem_to_set) {
    //error handling: checking to make sure the matrix exists.
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    //error handling: checking that the user-given coordinates are within the bounds of the matrix.
    else if(row < 0 || row > matrix_in->rows || row < 0 || column < 0 || column > matrix_in->columns) {
        printf("Error: coordinates provided do not exist within the matrix.\n");
        return -1;
    }
    //if error handling is passed, then function runs as expected.
    else {

        if(matrix_in->orient == ROW) {

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    matrix_in->matrix_data[row].values[column] = elem_to_set;
                    break;

                case FLOAT:

                    matrix_in->matrix_data[row].values[column] = elem_to_set;
                    break;

                case DOUBLE:
                
                    matrix_in->matrix_data[row].values[column] = elem_to_set;
                    break;
            }

            return 1;
            
        }
        else {

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    matrix_in->matrix_data[column].values[row] = elem_to_set;
                    break;

                case FLOAT:

                    matrix_in->matrix_data[column].values[row] = elem_to_set;
                    break;

                case DOUBLE:
                
                    matrix_in->matrix_data[column].values[row] = elem_to_set;
                    break;
            }

            return 1;

        }
    }
}


/**
 * 
 * @brief returns the element at a specified location within a given matrix.
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * @param row - the row the the desired element is in.
 * @param column - the column the the desired element is in.
 * 
 * @return
 * 
*/
union data_val get_element(struct matrix* matrix_in, int row, int column) {
    
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        union data_val result;
        result.itgr = -1;
        return result;

    }
    //error handling: checking that the user-given coordinates are within the bounds of the matrix.
    else if(row < 0 || row > matrix_in->rows || row < 0 || column < 0 || column > matrix_in->columns) {
        printf("Error: coordinates provided do not exist within the matrix.\n");
        union data_val result;
        result.itgr = -1;
        return result;

    }
    //if error handling is passed, then function runs as expected.
    else {

        if(matrix_in->orient == ROW) {

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    return matrix_in->matrix_data[row].values[column];
                    break;

                case FLOAT:

                    return matrix_in->matrix_data[row].values[column];
                    break;

                case DOUBLE:
                
                    return matrix_in->matrix_data[row].values[column];
                    break;
            }

        }
        else {

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    return matrix_in->matrix_data[column].values[row];
                    break;

                case FLOAT:

                    return matrix_in->matrix_data[column].values[row];
                    break;

                case DOUBLE:
                
                    return matrix_in->matrix_data[column].values[row];
                    break;
            }

        }

    }

}


/**
 * 
 * @brief will set an array of elements to a specified row in a specified matrix.
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * @param row - the row to insert elements at.
 * @param nums_to_set - an array of the numbers to set.
 * @param arr_size - the size of the array being passed in.
 * 
 * @return returns 1 for success, or -1 for failure.
 * 
*/
int set_row(struct matrix* matrix_in, int row, union data_val nums_to_set[], int arr_size) {
    
    //error handling: checking to make sure the matrix exists.
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    //error handling: checking that the user-given coordinates are within the bounds of the matrix.
    else if(row < 0 || row > matrix_in->rows) {
        printf("Error: coordinates provided do not exist within the matrix.\n");
        return -1;
    }
    //error handling: checking if nums_to_set is not the same size as the number of columns
    else if(matrix_in->columns != arr_size) {
        if (arr_size < matrix_in->columns) {
            printf("Error: array does not have enough elements to fill the row. please add more elements and try again.");
            return -1;
        }
        else {
            printf("Error: array has too many elements to fill the row. please remove some elements and try again.");
            return -1;
        }
    }
    //if error handling is passed, then function runs as expected.
    else {

        if(matrix_in->orient == ROW){

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[row].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[row].size+1;
                    }

                    return 1;
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[row].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[row].size+1;
                    }

                    return 1;
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[row].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[row].size+1;
                    }

                    return 1;
                    break;

            }

        }
        else{

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[row] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[x].size+1;
                    }

                    return 1;
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[row] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[x].size+1;
                    }

                    return 1;
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[row] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[x].size+1;
                    }

                    return 1;
                    break;

            }

        }

    }

}


/**
 * 
 * @brief will set an array of elements to a specified row in a specified matrix.
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * @param column - the column to insert elements at.
 * @param nums_to_set - an array of the numbers to set.
 * 
 * @return returns 1 for success, or -1 for failure.
 * 
*/

int set_column(struct matrix* matrix_in, int column, union data_val nums_to_set[]) {
    //arr_size will be used in error handling later 
    size_t arr_size = sizeof(nums_to_set) / sizeof(nums_to_set[0]);

    //error handling: checking to make sure the matrix exists.
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    //error handling: checking that the user-given coordinates are within the bounds of the matrix.
    else if(column < 0 || column > matrix_in->columns) {
        printf("Error: coordinates provided do not exist within the matrix.\n");
        return -1;
    }
    //error handling: checking if nums_to_set is not the same size as the number of rows
    else if(matrix_in->rows != arr_size) {
        if (arr_size < matrix_in->rows) {
            printf("Error: array does not have enough elements to fill the row. please add more elements and try again.");
            return -1;
        }
        else {
            printf("Error: array has too many elements to fill the row. please remove some elements and try again.");
            return -1;
        }
    }
    //if error handling is passed, then function runs as expected.
    else {

        if(matrix_in->orient == ROW){

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[column] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[x].size+1;
                    }

                    return 1;
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[column] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[x].size+1;
                    }

                    return 1;
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[column] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[x].size+1;
                    }

                    return 1;
                    break;

            }

        }
        else{

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[column].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[column].size+1;
                    }

                    return 1;
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[column].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[column].size+1;
                    }

                    return 1;
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[column].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        matrix_in->matrix_data[column].size+1;
                    }

                    return 1;
                    break;

            }

        }

    }

}


/**
 * 
 * @brief will return an array of the elements in a desired row in a given matrix.
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * @param row - the row from which the elements will be returned.
 * 
 * @return returns a pointer to an array containing the elements in the desired row; or returns a null pointer if unsuccessful.
 * 
*/
void* print_row(struct matrix* matrix_in, int row) {
    //error handling: checking to make sure the matrix exists.
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        void* error_ptr = NULL;
        return error_ptr;
    }
    //error handling: checking that the user-given coordinates are within the bounds of the matrix.
    else if(row < 0 || row > matrix_in->rows) {
        printf("Error: coordinates provided do not exist within the matrix.\n");
        void* error_ptr = NULL;
        return error_ptr;
    }
    else {

        //initializing an empty array to add row elements to
        union data_val nums_to_return[matrix_in->columns];
        union data_val* return_ptr = &nums_to_return;

        if(matrix_in->orient == ROW) {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[row].values[x];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[row].values[x];
                    }
                    return return_ptr;
                    break;

                case DOUBLE:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[row].values[x];
                    }
                    return return_ptr;
                    break;
            }
        }
        else {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[row];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[row];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;

                case DOUBLE:
                //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[row];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;
            }
        }
    }
}


/**
 * 
 * @brief will return an array of the elements in a desired row in a given matrix.
 * 
 * @param matrix_in - the pointer to the matrix struct.
 * @param column - the column from which the elements will be returned.
 * 
 * @return returns a pointer to an array containing the elements in the desired row; or returns a null pointer if unsuccessful.
 * 
*/
void* print_column(struct matrix* matrix_in, int column) {
    //error handling: checking to make sure the matrix exists.
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        void* error_ptr = NULL;
        return error_ptr;
    }
    //error handling: checking that the user-given coordinates are within the bounds of the matrix.
    else if(column < 0 || column > matrix_in->columns) {
        printf("Error: coordinates provided do not exist within the matrix.\n");
        void* error_ptr = NULL;
        return error_ptr;
    }
    else {

        //initializing an empty array to add row elements to
        union data_val nums_to_return[matrix_in->rows];
        union data_val* return_ptr = nums_to_return;
        
        if(matrix_in->orient == ROW) {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[column];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[column];
                    }
                    return return_ptr;
                    break;

                case DOUBLE:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[column];
                    }
                    return return_ptr;
                    break;
            }
        }
        else {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[column].values[x];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[column].values[x];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;

                case DOUBLE:
                //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[column].values[x];
                    }
                    //returns a pointer to the array
                    return return_ptr;
                    break;
            }
        }
    }
}


int main() {

    enum orientation orient_row = ROW;
    enum orientation orient_col = COL;
    enum data_type dt_int = INT;
    enum data_type dt_flt = FLOAT;
    enum data_type dt_dbl = DOUBLE;

    union data_val int1, int2, int3, int4, int5;
    int1.itgr = 397;
    int2.itgr = 82;
    int3.itgr = 3;
    int4.itgr = 8000;
    int5.itgr = 0;

    union data_val flt1, flt2, flt3, flt4, flt5;
    flt1.flt = 10.7;
    flt2.flt = 3.7;
    flt3.flt = 5.4;
    flt4.flt = 8.0;
    flt5.flt = 100.3;

    union data_val dbl_test;
    dbl_test.dbl = 3.1415926;
    

    struct matrix* row_matrix = matrix_init(3, 3, orient_row , dt_int);
    struct matrix* col_matrix = matrix_init(3, 3, orient_col , dt_int);

    set_element(row_matrix, 0, 0, int3);
    union data_val ret_val = get_element(row_matrix, 0, 0);
    printf("value at (0,0): %d\n", ret_val);

    union data_val nums_to_set[] = {int1, int2, int3};

    set_row(row_matrix, 1, nums_to_set, 3);

    free_matrix(row_matrix);
    free_matrix(col_matrix);

}