#include <stdio.h>
#include <Matrix_Library.h>


void test_matrix_init (int rows, int cols, enum orientation orient) {
    void* result = matrix_init(rows, cols, orient);

    if (result == NULL) {
        printf(" !!! Test fail: matrix_init(%d, %d) = %d, expected: not Null pointer\n", rows, cols, result);
    }
    else {
        printf("Test pass: add(%d, %d) = %d\n", rows, cols, result);
    }

}


void test_get_rows(struct header_array* head_ptr, int expected) {
    
    int result = get_rows(head_ptr);
    if(result != expected) {
        printf(" !!! Test failed: get_rows(%p,%d) = %d. expected: %d\n", head_ptr, result, expected);
    }
    else {
        printf("Test pass: get_rows(%p,%d) = %d. expected: %d\n", head_ptr, result, expected);
    }

}


void test_get_columns(struct header_array* head_ptr, int expected) {

    int result = get_columns(head_ptr);
    if(result != expected) {
        printf(" !!! Test failed: get_columns(%p,%d) = %d. expected: %d\n", head_ptr, result, expected);
    }
    else {
        printf("Test pass: get_columns(%p,%d) = %d. expected: %d\n", head_ptr, result, expected);
    }
}


void test_print_element() {
    
}


void test_print_row() {

}


void test_print_column() {

}


int main () {

}