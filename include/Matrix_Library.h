#ifndef Matrix_Library
#define Matrix_Library

struct Matrix;

enum data_type {
    INT,
    FLOAT,
    DOUBLE,
};

union data_val {
    int itgr;
    float flt;
    double dbl;
};

enum orientation {
    ROW,
    COL,
};


void* matrix_init();

int free_matrix();

int get_rows();

int get_columns();

int print_element();

int set_element();

int set_row();

int set_column();

void* print_row();

void* print_column();

#endif