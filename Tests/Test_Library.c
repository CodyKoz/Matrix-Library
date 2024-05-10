#include <stdio.h>
#include "../include/Matrix_Library.h"


void test_matrix_init (struct matrix* matrix_in) {
    void* result = matrix_in;
    if (result == NULL) {
        printf(" !!! Test fail: matrix_init(%p) = %p, expected: non-Null pointer\n", matrix_in, result);
    }
    else {
        printf("Test pass: matrix_init(%p) = %p. expected: non-Null pointer\n", matrix_in, result);
    }
    
}

void test_free_matrix(struct matrix* matrix_in, int expected) {
    int result = free_matrix(matrix_in);
    if (result == -1) {
        printf(" !!! Test fail: free_matrix(%p) = %d\n", matrix_in, result);
    }
    else {
        printf("Test pass: free_matrix(%p) = %d\n", matrix_in, result);
    }
};

void test_get_rows(struct matrix* matrix_in, int expected) {
    int result = get_rows(matrix_in);
    if(result != expected) {
        printf(" !!! Test fail: get_rows(%p) = %d. expected: %d\n", matrix_in, result, expected);
    }
    else {
        printf("Test pass: get_rows(%p) = %d. expected: %d\n", matrix_in, result, expected);
    }

}

void test_get_columns(struct matrix* matrix_in, int expected) {
    int result = get_columns(matrix_in);
    if(result != expected) {
        printf(" !!! Test fail: get_columns(%p) = %d. expected: %d\n", matrix_in, result, expected);
    }
    else {
        printf("Test pass: get_columns(%p) = %d. expected: %d\n", matrix_in, result, expected);
    }
}

void test_set_element(struct matrix* matrix_in, int row, int column, int elem_to_set, int expected) {
    int result = set_element(matrix_in, row, column, elem_to_set);
    if(result != expected) {
        printf(" !!! Test fail: set_element(%p,%d,%d,%d) = %d. expected: %d\n", matrix_in, row, column, elem_to_set, result, expected);
    }
    else {
        printf("Test pass: set_element(%p,%d,%d,%d) = %d. expected: %d\n", matrix_in, row, column, elem_to_set, result, expected);
    }
}

void test_print_element(struct matrix* matrix_in, int row, int column, union data_val expected) {
    union data_val result = get_element(matrix_in, row, column);

    switch (matrix_in->data_type) {
        case INT:
            if(result.itgr != expected.itgr) {
            printf(" !!! Test fail: print_element(%p,%d,%d) = %d. expected: %d\n", matrix_in, row, column, result.itgr, expected.itgr);
            }
            else {
            printf("Test pass: print_element(%p,%d,%d) = %d. expected: %d\n", matrix_in, row, column, result.itgr, expected.itgr);
            }
            break;

        case FLOAT:
            if(result.flt != expected.flt) {
            printf(" !!! Test fail: print_element(%p,%d,%d) = %f. expected: %f\n", matrix_in, row, column, result.flt, expected.flt);
            }
            else {
            printf("Test pass: print_element(%p,%d,%d) = %f. expected: %f\n", matrix_in, row, column, result.flt, expected.flt);
            }
            break;

        case DOUBLE:
            if(result.dbl != expected.dbl) {
            printf(" !!! Test fail: print_element(%p,%d,%d) = %.3f. expected: %.3f\n", matrix_in, row, column, result.dbl, expected.dbl);
            }
            else {
            printf("Test pass: print_element(%p,%d,%d) = %.3f. expected: %.3f\n", matrix_in, row, column, result.dbl, expected.dbl);
            }
            break;
    }

    
}

void test_set_row(struct matrix* matrix_in, int row, union data_val nums_to_set[], int arr_size, int expected) {
    int result = set_row(matrix_in, row, nums_to_set, arr_size);
    if(result != expected) {
        printf(" !!! Test fail: set_row(%p,%d,array of elems,%d) = %d. expected: %d\n", matrix_in, row, arr_size, result, expected);
    }
    else {
        printf("Test pass: set_row(%p,%d,array of elems,%d) = %d. expected: %d\n", matrix_in, row, arr_size, result, expected);
    }
}

void test_set_column(struct matrix* matrix_in, int column, union data_val nums_to_set[], int arr_size, int expected) {
    int result = set_column(matrix_in, column, nums_to_set, arr_size);
    if(result != expected) {
        printf(" !!! Test fail: set_column(%p,%d,array of elems,%d) = %d. expected: %d\n", matrix_in, column, arr_size, result, expected);
    }
    else {
        printf("Test pass: set_column(%p,%d,array of elems,%d) = %d. expected: %d\n", matrix_in, column, arr_size, result, expected);
    }
}

void test_print_row(struct matrix* matrix_in, int row) {
    void* result = print_row(matrix_in, row);
    if(result == NULL) {
        printf(" !!! Test fail: print_row(%p,%d) = %p. expected: non-Null pointer\n", matrix_in, row, result);
    }
    else {
        printf("Test pass: print_row(%p,%d) = %p. expected: non-Null pointer\n", matrix_in, row, result);
    }
}

void test_print_column(struct matrix* matrix_in, int column) {
    void* result = print_column(matrix_in, column);
    if(result == NULL) {
        printf(" !!! Test fail: print_column(%p,%d) = %p. expected: non-Null pointer\n", matrix_in, column, result);
    }
    else {
        printf("Test pass: print_column(%p,%d) = %p. expected: non-Null pointer\n", matrix_in, column, result);
    }
}

void test_add_matrices();


int main () {
    enum orientation orient_row = ROW;
    enum orientation orient_col = COL;
    enum data_type dt_int = INT;
    enum data_type dt_flt = FLOAT;
    enum data_type dt_dbl = DOUBLE;

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Integer Matrix Testing\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    struct matrix* matrix_row_int_1 = matrix_init(2,2,orient_row, dt_int);
    test_matrix_init(matrix_row_int_1);
    struct matrix* matrix_row_int_2 = matrix_init(10,10,orient_row, dt_int);
    test_matrix_init(matrix_row_int_2);
    struct matrix* matrix_row_int_3 = matrix_init(20,40,orient_row, dt_int);
    test_matrix_init(matrix_row_int_3);
    struct matrix* matrix_row_int_4 = matrix_init(100,150,orient_row, dt_int);
    test_matrix_init(matrix_row_int_4);
   
    struct matrix* matrix_col_int_1 = matrix_init(2,2,orient_col, dt_int);
    test_matrix_init(matrix_col_int_1);
    struct matrix* matrix_col_int_2 = matrix_init(10,10,orient_col, dt_int);
    test_matrix_init(matrix_col_int_2);
    struct matrix* matrix_col_int_3 = matrix_init(20,40,orient_col, dt_int);
    test_matrix_init(matrix_col_int_3);
    struct matrix* matrix_col_int_4 = matrix_init(100,150,orient_col, dt_int);
    test_matrix_init(matrix_col_int_4);


    //returns actual value of rows/cols
    test_get_rows(matrix_row_int_1, 2);
    test_get_rows(matrix_row_int_3, 20);
    test_get_rows(matrix_col_int_2, 10);
    test_get_rows(matrix_col_int_4, 100);

    test_get_columns(matrix_row_int_2, 10);
    test_get_columns(matrix_row_int_4, 150);
    test_get_columns(matrix_col_int_1, 2);
    test_get_columns(matrix_col_int_3, 40);

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Float Matrix Testing\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    struct matrix* matrix_row_flt_1 = matrix_init(2,2,orient_row, dt_flt);
    test_matrix_init(matrix_row_flt_1);
    struct matrix* matrix_row_flt_2 = matrix_init(10,10,orient_row, dt_flt);
    test_matrix_init(matrix_row_flt_2);
    struct matrix* matrix_row_flt_3 = matrix_init(20,40,orient_row, dt_flt);
    test_matrix_init(matrix_row_flt_3);
    struct matrix* matrix_row_flt_4 = matrix_init(100,150,orient_row, dt_flt);
    test_matrix_init(matrix_row_flt_4);
   
    struct matrix* matrix_col_flt_1 = matrix_init(2,2,orient_col, dt_flt);
    test_matrix_init(matrix_col_flt_1);
    struct matrix* matrix_col_flt_2 = matrix_init(10,10,orient_col, dt_flt);
    test_matrix_init(matrix_col_flt_2);
    struct matrix* matrix_col_flt_3 = matrix_init(20,40,orient_col, dt_flt);
    test_matrix_init(matrix_col_flt_3);
    struct matrix* matrix_col_flt_4 = matrix_init(100,150,orient_col, dt_flt);
    test_matrix_init(matrix_col_flt_4);

    //returns actual value of rows/cols
    test_get_rows(matrix_row_flt_1, 2);
    test_get_rows(matrix_row_flt_3, 20);
    test_get_rows(matrix_col_flt_2, 10);
    test_get_rows(matrix_col_flt_4, 100);

    test_get_columns(matrix_row_flt_2, 10);
    test_get_columns(matrix_row_flt_4, 150);
    test_get_columns(matrix_col_flt_1, 2);
    test_get_columns(matrix_col_flt_3, 40);

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Double Matrix Testing\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    struct matrix* matrix_row_dbl_1 = matrix_init(2,2,orient_row, dt_dbl);
    test_matrix_init(matrix_row_dbl_1);
    struct matrix* matrix_row_dbl_2 = matrix_init(10,10,orient_row, dt_dbl);
    test_matrix_init(matrix_row_dbl_2);
    struct matrix* matrix_row_dbl_3 = matrix_init(20,40,orient_row, dt_dbl);
    test_matrix_init(matrix_row_dbl_3);
    struct matrix* matrix_row_dbl_4 = matrix_init(100,150,orient_row, dt_dbl);
    test_matrix_init(matrix_row_dbl_4);
   
    struct matrix* matrix_col_dbl_1 = matrix_init(2,2,orient_col, dt_dbl);
    test_matrix_init(matrix_col_dbl_1);
    struct matrix* matrix_col_dbl_2 = matrix_init(10,10,orient_col, dt_dbl);
    test_matrix_init(matrix_col_dbl_2);
    struct matrix* matrix_col_dbl_3 = matrix_init(20,40,orient_col, dt_dbl);
    test_matrix_init(matrix_col_dbl_3);
    struct matrix* matrix_col_dbl_4 = matrix_init(100,150,orient_col, dt_dbl);
    test_matrix_init(matrix_col_dbl_4);


    //returns actual value of rows/cols
    test_get_rows(matrix_row_flt_1, 2);
    test_get_rows(matrix_row_flt_3, 20);
    test_get_rows(matrix_col_flt_2, 10);
    test_get_rows(matrix_col_flt_4, 100);

    test_get_columns(matrix_row_flt_2, 10);
    test_get_columns(matrix_row_flt_4, 150);
    test_get_columns(matrix_col_flt_1, 2);
    test_get_columns(matrix_col_flt_3, 40);

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Freeing Matrix Memory\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    test_free_matrix(matrix_row_int_1, 1);
    test_free_matrix(matrix_row_int_2, 1);
    test_free_matrix(matrix_row_int_3, 1);
    test_free_matrix(matrix_row_int_4, 1);

    test_free_matrix(matrix_col_int_1, 1);
    test_free_matrix(matrix_col_int_2, 1);
    test_free_matrix(matrix_col_int_3, 1);
    test_free_matrix(matrix_col_int_4, 1);


    test_free_matrix(matrix_row_flt_1, 1);
    test_free_matrix(matrix_row_flt_2, 1);
    test_free_matrix(matrix_row_flt_3, 1);
    test_free_matrix(matrix_row_flt_4, 1);
    
    test_free_matrix(matrix_col_flt_1, 1);
    test_free_matrix(matrix_col_flt_2, 1);
    test_free_matrix(matrix_col_flt_3, 1);
    test_free_matrix(matrix_col_flt_4, 1);


    test_free_matrix(matrix_row_dbl_1, 1);
    test_free_matrix(matrix_row_dbl_2, 1);
    test_free_matrix(matrix_row_dbl_3, 1);
    test_free_matrix(matrix_row_dbl_4, 1);
    
    test_free_matrix(matrix_col_dbl_1, 1);
    test_free_matrix(matrix_col_dbl_2, 1);
    test_free_matrix(matrix_col_dbl_3, 1);
    test_free_matrix(matrix_col_dbl_4, 1);

    ///----------------------------------------------------------------------------
    ///----------------------------------------------------------------------------

    //union data_val print_test;
    //print_test.itgr = 7;
    //test_print_element(matrix_row, 0, 0, print_test);

    

}