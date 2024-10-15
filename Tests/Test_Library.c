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
        printf(" !!! Test fail: free_matrix(%p) = %d. expected: %d\n", matrix_in, result, expected);
    }
    else {
        printf("Test pass: free_matrix(%p) = %d. expected: %d\n", matrix_in, result, expected);
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

void test_set_element(struct matrix* matrix_in, int row, int column, union data_val elem_to_set, int expected) {
    union data_val elem_in;
    switch(matrix_in->data_type) {
        case INT:
            elem_in.itgr = elem_to_set.itgr;
            break;
        case FLOAT:
            elem_in.dbl = elem_to_set.flt;
            break;
        case DOUBLE:
            elem_in.dbl = elem_to_set.dbl;
            break;
    }

    int result = set_element(matrix_in, row, column, elem_in);

    switch(matrix_in->data_type) {
        case INT:
            if(result != expected) {
                printf(" !!! Test fail: set_element(%p,%d,%d,%d) = %d. expected: %d\n", matrix_in, row, column, elem_to_set.itgr, result, expected);
                }
                else {
                    printf("Test pass: set_element(%p,%d,%d,%d) = %d. expected: %d\n", matrix_in, row, column, elem_to_set.itgr, result, expected);
                }
                break;
        case FLOAT:
            if(result != expected) {
                printf(" !!! Test fail: set_element(%p,%d,%d,%f) = %d. expected: %d\n", matrix_in, row, column, elem_to_set.flt, result, expected);
                }
                else {
                    printf("Test pass: set_element(%p,%d,%d,%f) = %d. expected: %d\n", matrix_in, row, column, elem_to_set.flt, result, expected);
                }
                break;
        case DOUBLE:
            if(result != expected) {
                printf(" !!! Test fail: set_element(%p,%d,%d,%.3f) = %d. expected: %d\n", matrix_in, row, column, elem_to_set.dbl, result, expected);
                }
                else {
                    printf("Test pass: set_element(%p,%d,%d,%.3f) = %d. expected: %d\n", matrix_in, row, column, elem_to_set.dbl, result, expected);
                }
                break;
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

void test_add_matrices(struct matrix* matrix_1, struct matrix* matrix_2) {
    void* result = add_matrices(matrix_1, matrix_2);
    if(result == NULL){
        printf(" !!! Test fail: add_matrices(%p,%p) = %p, expected: non-Null pointer\n", matrix_1, matrix_2, result);
    }
    else {
        printf("Test pass: add_matrices(%p,%p) = %p, expected: non-Null pointer\n", matrix_1, matrix_2, result);
    }
}

void test_subtract_matrices(struct matrix* matrix_1, struct matrix* matrix_2) {
    void* result = subtract_matrices(matrix_1, matrix_2);
    if(result == NULL){
        printf(" !!! Test fail: subtract_matrices(%p,%p) = %p, expected: non-Null pointer\n", matrix_1, matrix_2, result);
    }
    else {
        printf("Test pass: subtract_matrices(%p,%p) = %p, expected: non-Null pointer\n", matrix_1, matrix_2, result);
    }
}

void test_multiply_matrices(struct matrix* matrix_1, struct matrix* matrix_2) {
    void* result = multiply_matrices(matrix_1, matrix_2);
    if(result == NULL){
        printf(" !!! Test fail: multiply_matrices(%p,%p) = %p, expected: non-Null pointer\n", matrix_1, matrix_2, result);
    }
    else {
        printf("Test pass: multiply_matrices(%p,%p) = %p, expected: non-Null pointer\n", matrix_1, matrix_2, result);
    }
}

void test_duplicate_matrix(struct matrix* matrix_in) {
    void* result = duplicate_matrix(matrix_in);
    if (result == NULL) {
        printf(" !!! Test fail: duplicate_matrix(%p) = %p, expected: non-Null pointer\n", matrix_in, result);
    }
    else {
        printf("Test pass: duplicate_matrix(%p) = %p. expected: non-Null pointer\n", matrix_in, result);
    }
}

void test_create_subset(struct matrix* matrix_in) {
    void* result = create_subset(matrix_in);
    if (result == NULL) {
        printf(" !!! Test fail: create_subset(%p) = %p, expected: non-Null pointer\n", matrix_in, result);
    }
    else {
        printf("Test pass: create_subset(%p) = %p. expected: non-Null pointer\n", matrix_in, result);
    }
}

void test_set_subset_to_matrix(struct matrix* matrix_to_set, struct matrix* subset_matrix, int row_point, int col_point, int expected) {
    int result = set_subset_to_matrix(matrix_to_set, subset_matrix, row_point, col_point);
    if (result == -1) {
        printf(" !!! Test fail: set_subset_to_matrix(%p,%p,%d,%d) = %d. expected: %d\n", matrix_to_set, subset_matrix, row_point, col_point, result, expected);
    }
    else {
        printf("Test pass: set_subset_to_matrix(%p,%p,%d,%d) = %d. expected: %d\n", matrix_to_set, subset_matrix, row_point, col_point, result, expected);
    }
}

void test_resize_matrix(struct matrix* matrix_in, int new_rows, int new_columns) {
    void* result = resize_matrix(matrix_in);
    if (result == NULL) {
        printf(" !!! Test fail: resize_matrix(%p) = %p, expected: non-Null pointer\n", matrix_in, result);
    }
    else {
        printf("Test pass: resize_matrix(%p) = %p. expected: non-Null pointer\n", matrix_in, result);
    }
}

void test_compare_instance(struct matrix* matrix_1, struct matrix* matrix_2, int expected) {
    int result = compare_instance(matrix_1, matrix_2);
    if (result == -1) {
        printf(" !!! Test fail: compare_instance(%p,%p) = %d. expected: %d\n", matrix_1, matrix_2, result, expected);
    }
    else {
        printf("Test pass: compare_instance(%p,%p) = %d. expected: %d\n", matrix_1, matrix_2, result, expected);
    }
}

void test_compare_contents(struct matrix* matrix_1, struct matrix* matrix_2, int expected) {
    int result = compare_contents(matrix_1, matrix_2);
    if (result == -1) {
        printf(" !!! Test fail: compare_contents(%p,%p) = %d. expected: %d\n", matrix_1, matrix_2, result, expected);
    }
    else {
        printf("Test pass: compare_contents(%p,%p) = %d. expected: %d\n", matrix_1, matrix_2, result, expected);
    }
}

void test_rotate_matrix(struct matrix* matrix_in) {
    void* result = rotate_matrix(matrix_in);
    if (result == NULL) {
        printf(" !!! Test fail: rotate_matrix(%p) = %p, expected: non-Null pointer\n", matrix_in, result);
    }
    else {
        printf("Test pass: rotate_matrix(%p) = %p. expected: non-Null pointer\n", matrix_in, result);
    }
}


int main () {
    enum orientation orient_row = ROW;
    enum orientation orient_col = COL;
    enum data_type dt_int = INT;
    enum data_type dt_flt = FLOAT;
    enum data_type dt_dbl = DOUBLE;

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Integer Matrix Testing\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    struct matrix* row_int_1 = matrix_init(3, 3, orient_row, dt_int);
    test_matrix_init(row_int_1);
    struct matrix* row_int_2 = matrix_init(5, 4, orient_row, dt_int);
    test_matrix_init(row_int_2);
    struct matrix* row_int_3 = matrix_init(5, 4, orient_row, dt_int);
    test_matrix_init(row_int_3);
    struct matrix* row_int_4 = matrix_init(10, 10, orient_row, dt_int);
    test_matrix_init(row_int_4);

    struct matrix* col_int_1 = matrix_init(3, 3, orient_col, dt_int);
    test_matrix_init(col_int_1);
    struct matrix* col_int_2 = matrix_init(5, 4, orient_col, dt_int);
    test_matrix_init(col_int_2);
    struct matrix* col_int_3 = matrix_init(5, 4, orient_col, dt_int);
    test_matrix_init(col_int_3);
    struct matrix* col_int_4 = matrix_init(10, 10, orient_col, dt_int);
    test_matrix_init(col_int_4);

    printf("\n");

    test_get_rows(row_int_1, 3);
    test_get_rows(col_int_4, 10);

    printf("\n");

    test_get_columns(col_int_2, 4);
    test_get_columns(row_int_4, 10);

    printf("\n");
    union data_val elem_to_set;
    elem_to_set.itgr = 1;
    test_set_element(row_int_2, 3, 3, elem_to_set, 1);
    elem_to_set.itgr = -30;
    // test_set_element(col_int_3, 5, 4, elem_to_set, 1); ///
    // elem_to_set.itgr = 10;
    test_set_element(col_int_4, -5, 3, elem_to_set, -1); // testing error handling

    printf("\n");

    union data_val expected_elem;
    expected_elem.itgr = 1;
    test_print_element(row_int_2, 3, 3, expected_elem);
    expected_elem.itgr = -30;
    test_print_element(col_int_3, 5, 4, expected_elem);

    printf("\n");

    // union data_val expected_elem;
    // expected_elem.itgr = NO_VAL_INT;
    

    printf("\n");

    // union data_val int1, int2, int3, int4, int5, int6, int7, int8, int9, int10;
    // int1.itgr = 1;
    // int2.itgr = 10;
    // int3.itgr = 37;
    // int4.itgr = -56;
    // int5.itgr = 80;
    // int6.itgr = 151;
    // int7.itgr = -349;
    // int8.itgr = 1000;
    // int9.itgr = 2673;
    // int10.itgr = -12000;

    // union data_val int_arr1[] = {int1, int2};
    // union data_val int_arr2[] = {int2, int3, int4, int5};
    // union data_val int_arr3[] = {int6, int7, int8, int9, int10};


    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Float Matrix Testing\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    struct matrix* row_flt_1 = matrix_init(3, 3, orient_row, dt_flt);
    test_matrix_init(row_flt_1);
    struct matrix* row_flt_2 = matrix_init(5, 4, orient_row, dt_flt);
    test_matrix_init(row_flt_2);
    struct matrix* row_flt_3 = matrix_init(5, 4, orient_row, dt_flt);
    test_matrix_init(row_flt_3);
    struct matrix* row_flt_4 = matrix_init(10, 10, orient_row, dt_flt);
    test_matrix_init(row_flt_4);

    struct matrix* col_flt_1 = matrix_init(3, 3, orient_col, dt_flt);
    test_matrix_init(col_flt_1);
    struct matrix* col_flt_2 = matrix_init(5, 4, orient_col, dt_flt);
    test_matrix_init(col_flt_2);
    struct matrix* col_flt_3 = matrix_init(5, 4, orient_col, dt_flt);
    test_matrix_init(col_flt_3);
    struct matrix* col_flt_4 = matrix_init(10, 10, orient_col, dt_flt);
    test_matrix_init(col_flt_4);

    printf("\n");

    //returns actual value of rows/cols
    

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Double Matrix Testing\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    struct matrix* row_dbl_1 = matrix_init(3, 3, orient_row, dt_dbl);
    test_matrix_init(row_dbl_1);
    struct matrix* row_dbl_2 = matrix_init(5, 4, orient_row, dt_dbl);
    test_matrix_init(row_dbl_2);
    struct matrix* row_dbl_3 = matrix_init(5, 4, orient_row, dt_dbl);
    test_matrix_init(row_dbl_3);
    struct matrix* row_dbl_4 = matrix_init(10, 10, orient_row, dt_dbl);
    test_matrix_init(row_dbl_4);

    struct matrix* col_dbl_1 = matrix_init(3, 3, orient_col, dt_dbl);
    test_matrix_init(col_dbl_1);
    struct matrix* col_dbl_2 = matrix_init(5, 4, orient_col, dt_dbl);
    test_matrix_init(col_dbl_2);
    struct matrix* col_dbl_3 = matrix_init(5, 4, orient_col, dt_dbl);
    test_matrix_init(col_dbl_3);
    struct matrix* col_dbl_4 = matrix_init(10, 10, orient_col, dt_dbl);
    test_matrix_init(col_dbl_4);

    printf("\n");

    //returns actual value of rows/cols
    

    printf("\n///----------------------------------------------------------------------------\n");
    printf("///     Freeing Matrix Memory\n");    
    printf("///----------------------------------------------------------------------------\n\n");

    
    test_free_matrix(row_int_1, 1);
    test_free_matrix(row_int_2, 1);
    test_free_matrix(row_int_3, 1);
    test_free_matrix(row_int_4, 1);

    test_free_matrix(col_int_1, 1);
    test_free_matrix(col_int_2, 1);
    test_free_matrix(col_int_3, 1);
    test_free_matrix(col_int_4, 1);

    printf("\n");

    test_free_matrix(row_flt_1, 1);
    test_free_matrix(row_flt_2, 1);
    test_free_matrix(row_flt_3, 1);
    test_free_matrix(row_flt_4, 1);

    test_free_matrix(col_flt_1, 1);
    test_free_matrix(col_flt_2, 1);
    test_free_matrix(col_flt_3, 1);
    test_free_matrix(col_flt_4, 1);

    printf("\n");

    test_free_matrix(row_dbl_1, 1);
    test_free_matrix(row_dbl_2, 1);
    test_free_matrix(row_dbl_3, 1);
    test_free_matrix(row_dbl_4, 1);

    test_free_matrix(col_dbl_1, 1);
    test_free_matrix(col_dbl_2, 1);
    test_free_matrix(col_dbl_3, 1);
    test_free_matrix(col_dbl_4, 1);

    printf("\n");

}