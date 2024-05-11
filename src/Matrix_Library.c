#include <stdio.h>
#include <stdlib.h>
#include "../include/Matrix_Library.h"


//stores the size, capacity, and memory address of a dynamic array of unions
struct dynamic_array;

//used to store values in a matrix depending on data type
union data_val;

//determines the way a matrix is searched through 
enum orientation;

struct matrix;

/**
 * 
 * @brief this is a helper function that will assist in matrix math operations and error handling.
 * @brief ensures that all values in the given matrix are set to a specified "NO_VALUE" value.
 * 
 * @param matrix_in the pointer to the matrix. 
 * 
 * @return returns -1 for fail, or 1 for success.
 * 
*/
int devalue_matrix(struct matrix* matrix_in) {

    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    else {
        if(matrix_in->orient == ROW) {   
            for(int i = 0; i < matrix_in->rows; i++) {
                //helps keep track of how many values are in a given row/column
                matrix_in->matrix_data[i].size = 0;
                
                for(int j = 0; j < matrix_in->columns; j++) {

                    switch (matrix_in->data_type) {
                        case INT:
                            matrix_in->matrix_data[i].values[j].itgr = NO_VAL_INT;
                            break;
                        case FLOAT:
                            matrix_in->matrix_data[i].values[j].flt = NO_VAL_FLOAT;
                            break;
                        case DOUBLE:
                            matrix_in->matrix_data[i].values[j].dbl = NO_VAL_DOUBLE;
                            break;
                    }
                }
            }
            return 1;
        }
        else {
            for(int i = 0; i < matrix_in->columns; i++) {
                //helps keep track of how many values are in a given row/column
                matrix_in->matrix_data[i].size = 0;
                
                for(int j = 0; j < matrix_in->rows; j++) {

                    switch (matrix_in->data_type) {
                        case INT:
                            matrix_in->matrix_data[i].values[j].itgr = NO_VAL_INT;
                            break;
                        case FLOAT:
                            matrix_in->matrix_data[i].values[j].flt = NO_VAL_FLOAT;
                            break;
                        case DOUBLE:
                            matrix_in->matrix_data[i].values[j].dbl = NO_VAL_DOUBLE;
                            break;
                    }
                }
            }
            return 1;
        }
    }
}


/**
 * 
 * @brief this is a helper function that will determine if a matrix is entirely populated or not
 * @brief will be used to streamline matrix math function error checking.
 * 
 * @param
 * 
 * @return returns 1 if matrix is completely populated, or returns 0 if not completely populated.
 * 
*/
int check_population(struct matrix* matrix_in) {
        
    if(matrix_in == NULL) {
        printf("Error: matrix does not exist. please create a matrix and try again.\n");
        return -1;
    }
    else {

        if(matrix_in->orient == ROW) {

            //will be set to 1, unless loop finds a "NO_VAL" value in a matrix location,
            //in that case, 'is_populated' will be set to 0
            int is_populated = 1;

            for(int i = 0; i < matrix_in->rows; i++) {
                for(int j = 0; j < matrix_in->columns; j++) {
                    switch(matrix_in->data_type) {
                        case INT:
                            if(matrix_in->matrix_data[i].values[j].itgr == NO_VAL_INT) {
                                is_populated = 0;
                                break;
                            }
                            else {
                                break;
                            }
                        case FLOAT:
                            if(matrix_in->matrix_data[i].values[j].flt == NO_VAL_FLOAT) {
                                is_populated = 0;
                                break;
                            }
                            else {
                                break;
                            }
                        case DOUBLE:
                            if(matrix_in->matrix_data[i].values[j].dbl == NO_VAL_DOUBLE) {
                                is_populated = 0;
                                break;
                            }
                            else {
                                break;
                            }
                    }
                }
            }
            return is_populated;
        }
        else {
            //will be set to 1, unless loop finds a "NO_VAL" value in a matrix location,
            //in that case, 'is_populated' will be set to -1.
            int is_populated = 1;

            for(int i = 0; i < matrix_in->columns; i++) {
                for(int j = 0; j < matrix_in->rows; j++) {
                    switch(matrix_in->data_type) {
                        case INT:
                            if(matrix_in->matrix_data[i].values[j].itgr == NO_VAL_INT) {
                                is_populated = 0;
                                break;
                            }
                            else {
                                break;
                            }
                        case FLOAT:
                            if(matrix_in->matrix_data[i].values[j].flt == NO_VAL_FLOAT) {
                                is_populated = 0;
                                break;
                            }
                            else {
                                break;
                            }
                        case DOUBLE:
                            if(matrix_in->matrix_data[i].values[j].dbl == NO_VAL_DOUBLE) {
                                is_populated = 0;
                                break;
                            }
                            else {
                                break;
                            }
                    }
                }
            }
            return is_populated;
        }
    }
}


/**
 * @brief Initialize a Matrix with the number of rows and columns taken as arguments.
 * 
 * @param Rows number of rows.
 * @param Cols number of cols.
 * @param orient whether the matrix will be traversable in row or column major format.
 * @param data_type what type of data the matrix can store. Integers, Floats, and Doubles are accepted.
 * 
 * @return if successful, returns a pointer matrix with the input dimensions and orientation.
 * @return if unsuccessful, returns a NULL pointer.
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

        //sets all matrix indexes to NO_VALUE variables.
        devalue_matrix(new_matrix);
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
 * @param matrix_in the pointer to the matrix struct.
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

        if(matrix_in->matrix_data != NULL) {

            //freeing the union arrays stored in each dynamic array struct
            for(int x = 0; x < matrix_in->matrix_data->capacity; x++) {

                if(matrix_in->matrix_data[x].values != NULL) {
                    free(matrix_in->matrix_data[x].values);
                    matrix_in->matrix_data[x].values = NULL;
                }

            }

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
        //create variable that the value to return will be stored in.
        union data_val return_value;

        if(matrix_in->orient == ROW) {

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    return_value = matrix_in->matrix_data[row].values[column];
                    break;

                case FLOAT:

                    return_value = matrix_in->matrix_data[row].values[column];
                    break;

                case DOUBLE:
                
                    return_value = matrix_in->matrix_data[row].values[column];
                    break;
            }
            return return_value;
        }
        else {

            //switch to handle different data types
            switch (matrix_in->data_type) {
                case INT:

                    return_value = matrix_in->matrix_data[column].values[row];
                    break;

                case FLOAT:

                    return_value = matrix_in->matrix_data[column].values[row];
                    break;

                case DOUBLE:
                
                    return_value = matrix_in->matrix_data[column].values[row];
                    break;
            }
            return return_value;
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
                        //matrix_in->matrix_data[row].size+1;
                    }
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[row].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[row].size+1;
                    }
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[row].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[row].size+1;
                    }
                    break;

            }
            return 1;
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
                        //matrix_in->matrix_data[x].size+1;
                    }
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[row] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[x].size+1;
                    }
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->columns; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[row] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[x].size+1;
                    }
                    break;
            }
            return 1;
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
int set_column(struct matrix* matrix_in, int column, union data_val nums_to_set[], int arr_size) {

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
                        //matrix_in->matrix_data[x].size+1;
                    }
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[column] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[x].size+1;
                    }
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[x].values[column] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[x].size+1;
                    }
                    break;
            }
            return 1;
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
                        //matrix_in->matrix_data[column].size+1;
                    }
                    break;

                case FLOAT:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[column].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[column].size+1;
                    }
                    break;

                case DOUBLE:

                    //iterate through each element at desired row and set the element to that location
                    for(int x = 0; x < matrix_in->rows; x++) {

                        union data_val temp;
                        temp = nums_to_set[x];
                        matrix_in->matrix_data[column].values[x] = temp;

                        //increase size to keep track of how much of the row is filled
                        //matrix_in->matrix_data[column].size+1;
                    }
                    break;
            }
            return 1;
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
        //switch block to determine data type, which will be used to dynamically allocate memory for return values.
        int type_size;
        switch(matrix_in->data_type) {
            case INT:
                type_size = sizeof(int);
                break;
            case FLOAT:
                type_size = sizeof(float);
                break;
            case DOUBLE:
                type_size = sizeof(double);
                break;

        }
        //allocating memory based on switch block above
        union data_val* nums_to_return = (union data_val*)malloc(type_size * matrix_in->columns);


        if(matrix_in->orient == ROW) {

            switch (matrix_in->data_type) {
                case INT:

                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[row].values[x];
                    }
                    //returns a pointer to the array
                    
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[row].values[x];
                    }
                    break;

                case DOUBLE:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[row].values[x];
                    }
                    break;
            }
            
            return nums_to_return;
        }
        else {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[row];
                    }
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[row];
                    }
                    break;

                case DOUBLE:
                //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[row];
                    }
                    break;
            }
            return nums_to_return;
        }
    }
}


/**
 * 
 * @brief will return an array of the elements in a desired row in a given matrix.
 * 
 * @param matrix_in the pointer to the matrix struct.
 * @param column the column from which the elements will be returned.
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

        //switch block to determine data type, which will be used to dynamically allocate memory for return values.
        int type_size;
        switch(matrix_in->data_type) {
            case INT:
                type_size = sizeof(int);
                break;
            case FLOAT:
                type_size = sizeof(float);
                break;
            case DOUBLE:
                type_size = sizeof(double);
                break;

        }
        //allocating memory based on switch block above
        union data_val* nums_to_return = (union data_val*)malloc(type_size * matrix_in->columns);
        
        if(matrix_in->orient == ROW) {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[column];
                    }
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[column];
                    }
                    break;

                case DOUBLE:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[x].values[column];
                    }
                    break;
            }
            return nums_to_return;
        }
        else {

            switch (matrix_in->data_type) {
                case INT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[column].values[x];
                    }
                    break;

                case FLOAT:
                    //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[column].values[x];
                    }
                    break;

                case DOUBLE:
                //loop through desired row, and add all elements in row to array.
                    for(int x = 0; x < matrix_in->columns; x++) {
                        nums_to_return[x] = matrix_in->matrix_data[column].values[x];
                    }
                    break;
            }
            return nums_to_return;
        }
    }
}


/**
 * 
 * @brief will add of the respective elements in two matrices and return a new matrix with the sum values. 
 * 
 * @param matrix_1 pointer to a matrix struct.
 * @param matrix_2 pointer to a matrix struct.
 * 
 * @return on success returns a pointer to a matrix that is the sum of the two input matrices. 
 * @return on failure, returns a NULL pointer.
 * 
*/
void* add_matrices(struct matrix* matrix_1, struct matrix* matrix_2) {

    //error handling: do both matrices exist?
    if(matrix_1 == NULL || matrix_2 == NULL) {
        printf("Error: at least one matrix does not exist.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same dimensions?
    else if(matrix_1->rows != matrix_2->rows || matrix_1->columns != matrix_2->columns) {
        printf("Error: matrices are not the same size.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same orientation?
    else if(matrix_1->orient != matrix_2->orient) {
        printf("Error: matrices are not the same orientation.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same data type?
    else if(matrix_1->data_type != matrix_2->data_type) {
        printf("Error: matrices are not the same data type.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices fully populated?
    else if(check_population(matrix_1) != 1 || check_population(matrix_2) != 1 ) {
        printf("Error: at least one matrix is not fully populated.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //if all error handling is passed, function continues as expected.
    else {

        struct matrix* sum_matrix = matrix_init(matrix_1->rows, matrix_1->columns, matrix_1->orient, matrix_1->data_type);

        if(matrix_1->orient == ROW) {

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {

                    union data_val new_val;

                    switch(matrix_1->data_type) {
                        case INT:

                            //new_val stores sum of matrix elems at index [i][j]
                            //then, new_val is set to the corresponding index in the new 'sum_matrix'
                            new_val.itgr = matrix_1->matrix_data[i].values[j].itgr + matrix_2->matrix_data[i].values[j].itgr;
                            sum_matrix->matrix_data[i].values[j].itgr = new_val.itgr;
                            break;

                        case FLOAT:

                            new_val.flt = matrix_1->matrix_data[i].values[j].flt + matrix_2->matrix_data[i].values[j].flt;
                            sum_matrix->matrix_data[i].values[j].flt = new_val.flt;
                            break;

                        case DOUBLE:

                            new_val.dbl = matrix_1->matrix_data[i].values[j].dbl + matrix_2->matrix_data[i].values[j].dbl;
                            sum_matrix->matrix_data[i].values[j].flt = new_val.dbl;
                            break;
                    }
                }
            }
            return sum_matrix;
        }
        else {

            struct matrix* sum_matrix = matrix_init(matrix_1->rows, matrix_1->columns, matrix_1->orient, matrix_1->data_type);

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {

                    union data_val new_val;

                    switch(matrix_1->data_type) {
                        case INT:

                            //new_val stores sum of matrix elems at index [i][j]
                            //then, new_val is set to the corresponding index in the new 'sum_matrix'
                            new_val.itgr = matrix_1->matrix_data[i].values[j].itgr + matrix_2->matrix_data[i].values[j].itgr;
                            sum_matrix->matrix_data[i].values[j].itgr = new_val.itgr;
                            break;

                        case FLOAT:

                            new_val.flt = matrix_1->matrix_data[i].values[j].flt + matrix_2->matrix_data[i].values[j].flt;
                            sum_matrix->matrix_data[i].values[j].flt = new_val.flt;
                            break;

                        case DOUBLE:

                            new_val.dbl = matrix_1->matrix_data[i].values[j].dbl + matrix_2->matrix_data[i].values[j].dbl;
                            sum_matrix->matrix_data[i].values[j].flt = new_val.dbl;
                            break;
                    }
                }
            }
            return sum_matrix;
        }
    }
}


/**
 * 
 * @brief will subtract of the respective elements in two matrices and return a new matrix with the difference values. 
 * 
 * @param matrix_1 pointer to a matrix struct.
 * @param matrix_2 pointer to a matrix struct.
 * 
 * @return on success returns a pointer to a matrix that is the difference of the two input matrices. 
 * @return on failure, returns a NULL pointer.
 * 
*/
void* subtract_matrices(struct matrix* matrix_1, struct matrix* matrix_2) {

    //error handling: do both matrices exist?
    if(matrix_1 == NULL || matrix_2 == NULL) {
        printf("Error: at least one matrix does not exist.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same dimensions?
    else if(matrix_1->rows != matrix_2->rows || matrix_1->columns != matrix_2->columns) {
        printf("Error: matrices are not the same size.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same orientation?
    else if(matrix_1->orient != matrix_2->orient) {
        printf("Error: matrices are not the same orientation.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same data type?
    else if(matrix_1->data_type != matrix_2->data_type) {
        printf("Error: matrices are not the same data type.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices fully populated?
    else if(check_population(matrix_1) != 1 || check_population(matrix_2) != 1 ) {
        printf("Error: at least one matrix is not fully populated.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //if all error handling is passed, function continues as expected.
    else {

        struct matrix* diff_matrix = matrix_init(matrix_1->rows, matrix_1->columns, matrix_1->orient, matrix_1->data_type);

        if(matrix_1->orient == ROW) {

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {

                    union data_val new_val;

                    switch(matrix_1->data_type) {
                        case INT:

                            //new_val stores difference of matrix elems at index [i][j]
                            //then, new_val is set to the corresponding index in the new 'diff_matrix'
                            new_val.itgr = matrix_1->matrix_data[i].values[j].itgr - matrix_2->matrix_data[i].values[j].itgr;
                            diff_matrix->matrix_data[i].values[j].itgr = new_val.itgr;
                            break;

                        case FLOAT:

                            new_val.flt = matrix_1->matrix_data[i].values[j].flt - matrix_2->matrix_data[i].values[j].flt;
                            diff_matrix->matrix_data[i].values[j].flt = new_val.flt;
                            break;

                        case DOUBLE:

                            new_val.dbl = matrix_1->matrix_data[i].values[j].dbl - matrix_2->matrix_data[i].values[j].dbl;
                            diff_matrix->matrix_data[i].values[j].flt = new_val.dbl;
                            break;
                    }
                }
            }
            return diff_matrix;
        }
        else {

            struct matrix* diff_matrix = matrix_init(matrix_1->rows, matrix_1->columns, matrix_1->orient, matrix_1->data_type);

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {

                    union data_val new_val;

                    switch(matrix_1->data_type) {
                        case INT:

                            //new_val stores difference of matrix elems at index [i][j]
                            //then, new_val is set to the corresponding index in the new 'diff_matrix'
                            new_val.itgr = matrix_1->matrix_data[i].values[j].itgr - matrix_2->matrix_data[i].values[j].itgr;
                            diff_matrix->matrix_data[i].values[j].itgr = new_val.itgr;
                            break;

                        case FLOAT:

                            new_val.flt = matrix_1->matrix_data[i].values[j].flt - matrix_2->matrix_data[i].values[j].flt;
                            diff_matrix->matrix_data[i].values[j].flt = new_val.flt;
                            break;

                        case DOUBLE:

                            new_val.dbl = matrix_1->matrix_data[i].values[j].dbl - matrix_2->matrix_data[i].values[j].dbl;
                            diff_matrix->matrix_data[i].values[j].flt = new_val.dbl;
                            break;
                    }
                }
            }
            return diff_matrix;
        }
    }
}


/**
 * 
 * @brief will multiply of the respective elements in two matrices and return a new matrix with the product values. 
 * 
 * @param matrix_1 pointer to a matrix struct.
 * @param matrix_2 pointer to a matrix struct.
 * 
 * @return on success returns a pointer to a matrix that is the product of the two input matrices. 
 * @return on failure, returns a NULL pointer.
 * 
*/
void* multiply_matrices(struct matrix* matrix_1, struct matrix* matrix_2) {

    //error handling: do both matrices exist?
    if(matrix_1 == NULL || matrix_2 == NULL) {
        printf("Error: at least one matrix does not exist.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same dimensions?
    else if(matrix_1->rows != matrix_2->rows || matrix_1->columns != matrix_2->columns) {
        printf("Error: matrices are not the same size.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same orientation?
    else if(matrix_1->orient != matrix_2->orient) {
        printf("Error: matrices are not the same orientation.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same data type?
    else if(matrix_1->data_type != matrix_2->data_type) {
        printf("Error: matrices are not the same data type.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices fully populated?
    else if(check_population(matrix_1) != 1 || check_population(matrix_2) != 1 ) {
        printf("Error: at least one matrix is not fully populated.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //if all error handling is passed, function continues as expected.
    else {

        struct matrix* prod_matrix = matrix_init(matrix_1->rows, matrix_1->columns, matrix_1->orient, matrix_1->data_type);

        if(matrix_1->orient == ROW) {

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {

                    union data_val new_val;

                    switch(matrix_1->data_type) {
                        case INT:

                            //new_val stores product of matrix elems at index [i][j]
                            //then, new_val is set to the corresponding index in the new 'prod_matrix'
                            new_val.itgr = matrix_1->matrix_data[i].values[j].itgr * matrix_2->matrix_data[i].values[j].itgr;
                            prod_matrix->matrix_data[i].values[j].itgr = new_val.itgr;
                            break;

                        case FLOAT:

                            new_val.flt = matrix_1->matrix_data[i].values[j].flt * matrix_2->matrix_data[i].values[j].flt;
                            prod_matrix->matrix_data[i].values[j].flt = new_val.flt;
                            break;

                        case DOUBLE:

                            new_val.dbl = matrix_1->matrix_data[i].values[j].dbl * matrix_2->matrix_data[i].values[j].dbl;
                            prod_matrix->matrix_data[i].values[j].flt = new_val.dbl;
                            break;
                    }
                }
            }
            return prod_matrix;
        }
        else {

            struct matrix* prod_matrix = matrix_init(matrix_1->rows, matrix_1->columns, matrix_1->orient, matrix_1->data_type);

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {

                    union data_val new_val;

                    switch(matrix_1->data_type) {
                        case INT:

                            //new_val stores product of matrix elems at index [i][j]
                            //then, new_val is set to the corresponding index in the new 'prod_matrix'
                            new_val.itgr = matrix_1->matrix_data[i].values[j].itgr * matrix_2->matrix_data[i].values[j].itgr;
                            prod_matrix->matrix_data[i].values[j].itgr = new_val.itgr;
                            break;

                        case FLOAT:

                            new_val.flt = matrix_1->matrix_data[i].values[j].flt * matrix_2->matrix_data[i].values[j].flt;
                            prod_matrix->matrix_data[i].values[j].flt = new_val.flt;
                            break;

                        case DOUBLE:

                            new_val.dbl = matrix_1->matrix_data[i].values[j].dbl * matrix_2->matrix_data[i].values[j].dbl;
                            prod_matrix->matrix_data[i].values[j].flt = new_val.dbl;
                            break;
                    }
                }
            }
            return prod_matrix;
        }
    }
}


/**
 * 
 * @brief will create a duplicate (deep copy) of a given matrix, with the same parameters, and values as the original.
 * 
 * @param matrix_in pointer to a matrix struct.
 * 
 * @return if successful, returns a void pointer to the duplicate matrix.
 * @return if unsuccessful, returns a NULL pointer.
 * 
*/
void* duplicate_matrix(struct matrix* matrix_in) {
    //create new matrix with matching params as matrix_in
    struct matrix* dupe_matrix = matrix_init(matrix_in->rows, matrix_in->columns, matrix_in->orient, matrix_in->data_type);
    if(matrix_in == NULL) {
        printf("Error: the input matrix does not exist.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    else {
        //iterate through matrix_in, and add each elem to new matrix
        if(matrix_in->orient == ROW) {
            
            //iterate through each index of the matrix
            for(int i = 0; i < matrix_in->rows; i++) {

                for(int j = 0; j < matrix_in->columns; j++) {

                    union data_val temp_val;

                    switch(matrix_in->data_type) {
                        case INT:

                            temp_val.itgr = matrix_in->matrix_data[i].values[j].itgr;
                            dupe_matrix->matrix_data[i].values[j].itgr = temp_val.itgr;
                            break;

                        case FLOAT:

                            temp_val.flt = matrix_in->matrix_data[i].values[j].flt;
                            dupe_matrix->matrix_data[i].values[j].flt = temp_val.flt;
                            break;

                        case DOUBLE:

                            temp_val.dbl = matrix_in->matrix_data[i].values[j].dbl;
                            dupe_matrix->matrix_data[i].values[j].dbl = temp_val.dbl;
                            break;
                    }
                }
            }
            return dupe_matrix;
        }
        else {

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_in->columns; i++) {

                for(int j = 0; j < matrix_in->rows; j++) {

                    union data_val temp_val;

                    switch(matrix_in->data_type) {
                        case INT:

                            temp_val.itgr = matrix_in->matrix_data[i].values[j].itgr;
                            dupe_matrix->matrix_data[i].values[j].itgr = temp_val.itgr;
                            break;

                        case FLOAT:

                            temp_val.flt = matrix_in->matrix_data[i].values[j].flt;
                            dupe_matrix->matrix_data[i].values[j].flt = temp_val.flt;
                            break;

                        case DOUBLE:

                            temp_val.dbl = matrix_in->matrix_data[i].values[j].dbl;
                            dupe_matrix->matrix_data[i].values[j].dbl = temp_val.dbl;
                            break;
                    }
                }
            }
            return dupe_matrix;
        }
    }
}


/**
 * 
 * @brief will store a subset of a given matrix in a separate matrix structure. takes in the number of rows and columns the subset will have,
 * @brief as well as the upper-left index that the subset will start at.
 * 
 * @param matrix_in pointer to a matrix struct.
 * @param subset_rows the number of rows the subset will have.
 * @param subset_columns the number of columns the subset will have.
 * @param row_point the lowest row index that the subset will start at.
 * @param col_point the lowest column index that the subset will start at.
 * 
 * @return if successful, returns a void pointer to the subset matrix.
 * @return if unsuccessful, returns a NULL pointer. 
 * 
*/
void* create_subset(struct matrix* matrix_in, int subset_rows, int subset_columns, int row_point, int col_point) {
    //error handling

    //if passed error handling, create new matrix using the input dimensions: ss rows/cols

    //starting at row/col point, iterate through matrix until bounds of subset are reached
        //adding the value at each index to the new subset matrix



}




    //not sure what return type to do for this one
// int set_subset_to_matrix();

// void* resize_matrix();


/**
 * 
 * @brief will compare if two matrix pointers are storing the memory address of the same matrix. ie: they are the same instance-wise.
 * 
 * @param matrix_1 pointer to a matrix struct
 * @param matrix_2 pointer to a matrix strust
 * 
 * @return returns 1 if matrices are equal instance-wise.
 * @return returns -1 if matrices are not equal instance-wise.
 * 
*/
int compare_instance(struct matrix* matrix_1, struct matrix* matrix_2) {
    if(matrix_1 == NULL || matrix_2 == NULL) {
        printf("Error: at least one matrix does not exist.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    else {
        if(&matrix_1 == &matrix_2) {
            return 1;
        }
        else {
            return -1;
        }
    } 
}


/**
 * 
 * @brief will compare two matrices of equal size and orientation, to see if the values at each index are the same in both matrices.
 * 
 * @param matrix_1 pointer to a matrix struct
 * @param matrix_2 pointer to a matrix strust
 * 
 * @return returns 1 if matrices are equal instance-wise.
 * @return returns -1 if matrices are not equal instance-wise.
 * 
*/
int compare_contents(struct matrix* matrix_1, struct matrix* matrix_2) {
    //error handling: do both matrices exist?
    if(matrix_1 == NULL || matrix_2 == NULL) {
        printf("Error: at least one matrix does not exist.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same dimensions?
    else if(matrix_1->rows != matrix_2->rows || matrix_1->columns != matrix_2->columns) {
        printf("Error: matrices are not the same size.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same orientation?
    else if(matrix_1->orient != matrix_2->orient) {
        printf("Error: matrices are not the same orientation.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //error handling: are both matrices the same data type?
    else if(matrix_1->data_type != matrix_2->data_type) {
        printf("Error: matrices are not the same data type.");
        void* null_ptr = NULL;
        return null_ptr;
    }
    //if error handling is passed then function continues as expected
    else {
        //iterate through matrix_1, compare values at each index to see if they match
        //iterate through matrix_in, and add each elem to new matrix
        if(matrix_1->orient == ROW) {
            
            int ret_val = 1;

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->rows; i++) {

                for(int j = 0; j < matrix_1->columns; j++) {                    

                    switch(matrix_1->data_type) {
                        case INT:

                            if(matrix_1->matrix_data[i].values[j].itgr != matrix_2->matrix_data[i].values[j].itgr){
                                ret_val = -1;
                                break;
                            }
                            else {
                                break;
                            }

                        case FLOAT:

                            if(matrix_1->matrix_data[i].values[j].flt != matrix_2->matrix_data[i].values[j].flt){
                                ret_val = -1;
                                break;
                            }
                            else {
                                break;
                            }

                        case DOUBLE:

                            if(matrix_1->matrix_data[i].values[j].dbl != matrix_2->matrix_data[i].values[j].dbl){
                                ret_val = -1;
                                break;
                            }
                            else {
                                break;
                            }    

                    }
                }
            }
            return ret_val;
        }
        else {

            int ret_val;

            //iterate through each index of the matrix
            for(int i = 0; i < matrix_1->columns; i++) {

                for(int j = 0; j < matrix_1->rows; j++) {

                    switch(matrix_1->data_type) {
                        case INT:

                            if(matrix_1->matrix_data[i].values[j].itgr != matrix_2->matrix_data[i].values[j].itgr){
                                ret_val = -1;
                                break;
                            }
                            else {
                                break;
                            }

                        case FLOAT:

                            if(matrix_1->matrix_data[i].values[j].flt != matrix_2->matrix_data[i].values[j].flt){
                                ret_val = -1;
                                break;
                            }
                            else {
                                break;
                            }

                        case DOUBLE:

                        if(matrix_1->matrix_data[i].values[j].dbl != matrix_2->matrix_data[i].values[j].dbl){
                                ret_val = -1;
                                break;
                            }
                            else {
                                break;
                            }    
                        
                    }
                }
            }
            return ret_val;
        }
    }
    
}




// int main() {

    //setting variables up
    // enum orientation orient_row = ROW;
    // enum orientation orient_col = COL;
    // enum data_type dt_int = INT;
    // enum data_type dt_flt = FLOAT;
    // enum data_type dt_dbl = DOUBLE;

    // union data_val int1, int2, int3, int4, int5, int6, int7, int8, int9;
    // int1.itgr = 397;
    // int2.itgr = -82;
    // int3.itgr = 3;
    // int4.itgr = -8000;
    // int5.itgr = 0;
    // int6.itgr = 1;
    // int7.itgr = 23;
    // int8.itgr = 40;
    // int9.itgr = 66;
    
    // union data_val flt1, flt2, flt3, flt4, flt5;
    // flt1.flt = 10.7;
    // flt2.flt = 3.7;
    // flt3.flt = 5.4;
    // flt4.flt = 8.0;
    // flt5.flt = 100.3;

    // union data_val dbl1, dbl2, dbl3, dbl4, dbl5;
    // dbl1.dbl = 3.1415926;
    // dbl2.dbl = 3.1415926;
    // dbl3.dbl = 3.1415926;
    // dbl4.dbl = 3.1415926;
    // dbl5.dbl = 3.1415926;
    
    //initializing matrices
    // struct matrix* row_matrix_1 = matrix_init(1, 3, orient_row , dt_int);
    // struct matrix* row_matrix_2 = matrix_init(1, 3, orient_row , dt_int);

    // struct matrix* col_matrix_1 = matrix_init(2, 2, orient_col , dt_flt);
    // struct matrix* col_matrix_2 = matrix_init(2, 2, orient_col , dt_flt);

    //testing set/get row/col
    // union data_val row_to_set1[] = {int1, int2, int3};
    // union data_val row_to_set2[] = {int4, int5, int6};
    // union data_val row_to_set3[] = {int7, int8, int9};

    // union data_val col_to_set1[] = {flt1.flt, flt2.flt};
    // union data_val col_to_set2[] = {flt3.flt, flt4.flt};

    // set_row(row_matrix_1, 0, row_to_set1, 3);
    // set_row(row_matrix_2, 0, row_to_set1, 3);

    //add matrices + print row result
    // struct matrix* sum_matrix = (struct matrix*)add_matrices(row_matrix_1, row_matrix_2);
    
    //freeing matrices
    // free_matrix(row_matrix_1);
    // free_matrix(row_matrix_2);
    // free_matrix(col_matrix_1);
    // free_matrix(col_matrix_2);

// }

