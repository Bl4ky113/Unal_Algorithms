
#include <stdlib.h>
#include <stdio.h>

#define MIN_MATRIX_ORDER 2

typedef enum operation_type {
    SUM = 1,
    SUB = -1
} op_type;

void print_matrix (int **matrix, size_t i_offset, size_t j_offset, size_t order) {
    int *row;
    int i, j;

    for (i = 0; i < order; i++) {
        row = matrix[i + i_offset];
        
        for (j = 0; j < order; j++) {
            fprintf(stdout, "%d ", row[j + j_offset]);
        }

        fprintf(stdout, "\n");
    }

    return;
}

void operate_matrixes (
        int **mat_1, int **mat_2, int **mat_result, size_t mat_order, 
        size_t i_start, size_t i_end, 
        size_t j_start, size_t j_end,
        unsigned int op
    ) {
    size_t new_mat_order;

    if (mat_order == 1) {
        mat_result[i_start][j_start] = mat_1[i_start][j_start] + (op * mat_2[i_start][j_start]);
        return;
    }

    new_mat_order = mat_order / 2;

    if (new_mat_order > 1) {
        print_matrix(mat_1, i_start, j_start, new_mat_order);
        print_matrix(mat_2, i_start, j_start, new_mat_order);
    }

    operate_matrixes(
        mat_1, mat_2, mat_result,
        new_mat_order,
        i_start, i_start + new_mat_order,
        j_start, j_start + new_mat_order,
        op
    );

    if (new_mat_order > 1) {
        print_matrix(mat_1, i_start, j_start + new_mat_order, new_mat_order);
        print_matrix(mat_2, i_start, j_start + new_mat_order, new_mat_order);
    }

    operate_matrixes(
        mat_1, mat_2, mat_result,
        new_mat_order,
        i_start, i_start + new_mat_order,
        j_start + new_mat_order, j_end,
        op
    );

    if (new_mat_order > 1) {
        print_matrix(mat_1, i_start + new_mat_order, j_start, new_mat_order);
        print_matrix(mat_2, i_start + new_mat_order, j_start, new_mat_order);
    }

    operate_matrixes(
        mat_1, mat_2, mat_result,
        new_mat_order,
        i_start + new_mat_order, i_end,
        j_start, j_start + new_mat_order,
        op
    );

    if (new_mat_order > 1) {
        print_matrix(mat_1, i_start + new_mat_order, j_start + new_mat_order, new_mat_order);
        print_matrix(mat_2, i_start + new_mat_order, j_start + new_mat_order, new_mat_order);
    }

    operate_matrixes(
        mat_1, mat_2, mat_result,
        new_mat_order,
        i_start + new_mat_order, i_end,
        j_start + new_mat_order, j_end,
        op
    );

    return;
}

void destroy_matrix (int **matrix, size_t order) {
    int *row;
    int i = 0;

    for (i = 0; i < order; i++) {
        row = matrix[i];

        free(row);
    }

    return;
}

int main (int args, char **argv) {
    char *input_operation, *input_number_str, *tmp_input_number_str;
    size_t input_number_str_size;
    unsigned int operation;
    int input, i, j, k;

    int **matrix_a, **matrix_b, **matrix_c;
    int *row_a, *row_b;
    size_t matrix_order, row_size;
    
    input_operation = (char *) alloca(sizeof(char));
    fscanf(stdin, "%1[+-]\n", input_operation);

    switch (*input_operation) {
        case '+':
            operation = SUM;
            break;
        case '-':
            operation = SUB;
            break;
        default:
            fprintf(stderr, "OPERATION NOT FOUND");
            return -1;
    }

    input_number_str = NULL;
    input_number_str_size = 0;

    if (getline(&input_number_str, &input_number_str_size, stdin) < 0) {
        fprintf(stderr, "ERROR READING FIRST LINE OF MATRIX A");
        return -1;
    }

    tmp_input_number_str = input_number_str;

    matrix_a = (int **) malloc(sizeof(int*) * MIN_MATRIX_ORDER);
    matrix_a[0] = (int *) malloc(sizeof(int) * MIN_MATRIX_ORDER);

    row_a = matrix_a[0];
    row_size = MIN_MATRIX_ORDER;
    matrix_order = 0;

    while (sscanf(tmp_input_number_str, "%d %n", &input, &i) > 0) {  
        if (row_size <= matrix_order) {
            row_size *= 2;
            row_a = (int *) realloc(row_a, sizeof(int) * row_size);

            if (row_a == NULL) {
                fprintf(stderr, "ERROR REALOCATING NEW MEMORY FOR FIRST ROW");
                return -1;
            }
        }

        row_a[matrix_order++] = input;
        tmp_input_number_str += i;
    }

    tmp_input_number_str = NULL;
    free(input_number_str);

    matrix_a = (int **) realloc(matrix_a, sizeof(int *) * matrix_order);
    if (matrix_a == NULL) {
        fprintf(stderr, "ERROR REALOCATING MEMORY FOR MATRIX A");
        return -1;
    }

    for (i = 1; i < matrix_order; i++) {
        input_number_str = NULL;
        input_number_str_size = 0;
        j = 0;
        k = 0;

        matrix_a[i] = (int *) malloc(sizeof(int) * matrix_order);
        if (row_a == NULL) {
            fprintf(stderr, "ERROR ALLOCATING MEMORY FOR %d ROW OF MATRIX A", i);
            return -1;
        }
        row_a = matrix_a[i];

        if (getline(&input_number_str, &input_number_str_size, stdin) < 0) {
            fprintf(stderr, "ERROR READING %d LINE OF MATRIX A", i);
            return -1;
        }

        tmp_input_number_str = input_number_str;

        while (sscanf(tmp_input_number_str, "%d %n", &input, &k) > 0) {
            row_a[j++] = input;
            tmp_input_number_str += k;
        }

        tmp_input_number_str = NULL;
        free(input_number_str);
    }

    matrix_b = (int **) malloc(sizeof(int *) * matrix_order);
    if (matrix_b == NULL) {
        fprintf(stderr, "ERROR ALLOCATING MEMORY FOR MATRIX B");
        return -1;
    }

    for (i = 0; i < matrix_order; i++) {
        input_number_str = NULL;
        input_number_str_size = 0;
        j = 0;
        k = 0;

        matrix_b[i] = (int *) malloc(sizeof(int) * matrix_order);
        row_b = matrix_b[i];
        if (row_b == NULL) {
            fprintf(stderr, "ERROR ALLOCATING MEMORY FOR %d ROW OF MATRIX B", i);
            return -1;
        }

        if (getline(&input_number_str, &input_number_str_size, stdin) < 0) {
            fprintf(stderr, "ERROR READING %d LINE OF MATRIX B", i);
            return -1;
        }

        tmp_input_number_str = input_number_str;

        while (sscanf(tmp_input_number_str, "%d %n", &input, &k) > 0) {
            row_b[j++] = input;
            tmp_input_number_str += k;
        }

        tmp_input_number_str = NULL;
        free(input_number_str);
    }

    matrix_c = (int **) malloc(sizeof(int *) * matrix_order);
    if (matrix_c == NULL) {
        fprintf(stderr, "ERROR ALLOCATING MEMORY FOR MATRIX C");
        return -1;
    }
    for (i = 0; i < matrix_order; i++) {
        matrix_c[i] = (int *) calloc(matrix_order, sizeof(int));
        if (matrix_c[i] == NULL) {
            fprintf(stderr, "ERROR ALLOCATING MEMORY FOR %d ROW OF MATRIX C", i);
            return -1;
        }
    }

    operate_matrixes(
        matrix_a, matrix_b, matrix_c, matrix_order,
        0, matrix_order,
        0, matrix_order,
        operation
    );

    print_matrix(matrix_c, 0, 0, matrix_order);

    destroy_matrix(matrix_a, matrix_order);
    destroy_matrix(matrix_b, matrix_order);
    destroy_matrix(matrix_c, matrix_order);

    free(matrix_a);
    free(matrix_b);
    free(matrix_c);
    return 0;
}
