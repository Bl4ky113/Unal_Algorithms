
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_INPUT_LIST 4

void print_arr (int *arr, size_t arr_size) {
    for (int i = 0; i < arr_size; i++) {
        if (i != 0) {
            fprintf(stdout, " ");
        }

        fprintf(stdout, "%d", arr[i]);
    }
    fprintf(stdout, "\n");
    return;
}

void bubble_float_called (int *arr, size_t arr_size, int *float_calls) {
    fprintf(stdout, "%d -> ", ++(*float_calls));
    print_arr(arr, arr_size);
    return;
}

void bubble_float (int *arr, size_t i, size_t k, int *float_calls) {
    int tmp;

    if (i == k - 1) {
        return;
    }

    if (arr[i] > arr[i + 1]) {
        tmp = arr[i + 1];
        arr[i + 1] = arr[i];
        arr[i] = tmp;
    }
    
    bubble_float_called(arr, k, float_calls);
    return bubble_float(arr, i + 1, k, float_calls);
}

void bubble_aux (int *arr, size_t i, size_t n, int *float_calls) {
    if (i == n) {
        return;
    }

    bubble_float_called(arr, n, float_calls);
    bubble_float(arr, 0, n, float_calls);

    return bubble_aux(arr, 0, n - 1, float_calls);
}

void bubble_sort (int *arr, size_t arr_size) {
    int float_calls;
    float_calls = 0;

    bubble_aux(arr, 0, arr_size, &float_calls);
    return;
}

void bubble_sort_normal (int *arr, size_t arr_size) {
    int i, j, tmp, float_calls;

    float_calls = 0;

    for (i = arr_size; i > 0; i--) {
        /* 'called' */
        bubble_float_called(arr, i, &float_calls);

        for (j = 0; j < i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }

            /* 'called' */
            bubble_float_called(arr, i, &float_calls);
        }
    }

    return;
}

int main (int args, char **argv) {
    char *input_string;
    size_t input_string_size, input_number;
    int input, i;

    int *number_arr;
    int *cpy_number_arr;
    size_t number_arr_size;
    
    input_string = NULL;
    input_string_size = 0;
    input_number = 0;

    if (getline(&input_string, &input_string_size, stdin) < 0) {
        fprintf(stderr, "ERROR READING INPUT");
        return -1;
    }

    number_arr = (int *) malloc(sizeof(int) * MIN_INPUT_LIST);
    number_arr_size = MIN_INPUT_LIST;

    while(sscanf(input_string, "%d %n", &input, &i) > 0) {
        if (number_arr_size <= input_number) {
            number_arr_size *= 2;
            number_arr = (int *) realloc(number_arr, sizeof(int) * number_arr_size);

            if (number_arr == NULL) {
                fprintf(stderr, "ERROR RE-ALLOCATING NEW MEMORY");
                return -1;
            }
        }

        number_arr[input_number] = input;

        input_number++;
        input_string += i;
    }

    if (number_arr_size > input_number) {
        number_arr = (int *) realloc(number_arr, sizeof(int) * input_number);
        number_arr_size = input_number;

        if (number_arr == NULL) {
            fprintf(stderr, "ERROR DE-ALLOCATING NEW MEMORY");
            return -1;
        }
    }

    cpy_number_arr = (int *) malloc(sizeof(int) * number_arr_size);
    cpy_number_arr = (int *) memcpy(cpy_number_arr, number_arr, sizeof(int) * number_arr_size);

    /*print_arr(number_arr, number_arr_size);*/
    /*print_arr(cpy_number_arr, number_arr_size);*/

    /*bubble_sort(number_arr, number_arr_size);*/
    bubble_sort_normal(cpy_number_arr, number_arr_size);

    /*print_arr(number_arr, number_arr_size);*/
    print_arr(cpy_number_arr, number_arr_size);
    
    /*free(number_arr);*/
    free(cpy_number_arr);
    return 0;
}
