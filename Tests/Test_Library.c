#include <stdio.h>
#include "../include/Matrix_Library.h"



void test_matrix_init (int rows, int cols, enum orientation orient) {
    void* result = matrix_init(rows, cols, orient);

    if (result == NULL) {
        printf(" !!! Test fail: matrix_init(%d, %d) = %p, expected: not Null pointer\n", rows, cols, result);
    }
    else {
        printf("Test pass: add(%d, %d) = %p\n", rows, cols, result);
    }

}


void test_get_rows(struct header_array* head_ptr, int expected) {
    
    int result = get_rows(head_ptr);
    if(result != expected) {
        printf(" !!! Test fail: get_rows(%p) = %d. expected: %d\n", head_ptr, result, expected);
    }
    else {
        printf("Test pass: get_rows(%p) = %d. expected: %d\n", head_ptr, result, expected);
    }

}


void test_get_columns(struct header_array* head_ptr, int expected) {

    int result = get_columns(head_ptr);
    if(result != expected) {
        printf(" !!! Test fail: get_columns(%p) = %d. expected: %d\n", head_ptr, result, expected);
    }
    else {
        printf("Test pass: get_columns(%p) = %d. expected: %d\n", head_ptr, result, expected);
    }
}


void test_print_element(struct header_array* head_ptr, int row, int column, int expected) {
    int result = print_element(head_ptr, row, column);
    if (result != expected) {
        printf(" !!! Test fail: print_element(%p,%d,%d) = %d. expected: %d\n", head_ptr, row, column, result, expected);
    }
    else {
        printf("Test pass: print_element(%p,%d,%d) = %d. expected: %d\n", head_ptr, row, column, result, expected);
    }
}


void test_print_row() {

}


void test_print_column() {

}


int main () {

    enum orientation orient_row = ROW;
    //enum orientation orient_col = COL;
    struct header_array* head_ptr_row = matrix_init(5,5.8,orient_row);
    get_rows(head_ptr_row);
    get_columns(head_ptr_row);

}