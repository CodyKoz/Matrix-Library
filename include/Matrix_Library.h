#ifndef Matrix_Library
#define Matrix_Library

#define NO_VAL_INT 5113
#define NO_VAL_FLOAT 5113.1
#define NO_VAL_DOUBLE 5113.118965624515

struct dynamic_array
{
    int size;
    int capacity;
    union data_val* values;
};


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

struct matrix {

    int rows;
    int columns;
    enum orientation orient;
    enum data_type data_type;
    struct dynamic_array* matrix_data;  

};


int devalue_matrix();

int check_population();

void* matrix_init();

int free_matrix();

int get_rows();

int get_columns();

union data_val get_element();

int set_element();

int set_row();

int set_column();

void* print_row();

void* print_column();

void* add_matrices();

void* subtract_matrices();

void* multiply_matrices();

void* duplicate_matrix();

void* create_subset();

int set_subset_to_matrix();

void* resize_matrix();

int compare_instance();

int compare_contents();

void* rotate_matrix();

#endif