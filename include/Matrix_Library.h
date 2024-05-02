#ifndef Matrix_Library.h
#define Matrix_Library.h


struct dynamic_array;

struct header_array;

enum orientation {
    ROW,
    COL
};


void* matrix_init();

int free_matrix();

int get_rows();

int get_columns();

int print_element();

int print_row();

int print_column();

#endif