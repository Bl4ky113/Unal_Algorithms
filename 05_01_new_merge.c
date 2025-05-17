
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MIN_INPUT_LIST 4

void print_arr (int *arr, size_t start, size_t end) {
    int i;

    for (i = start; i <= end; i++) {
        if (i != start) {
            fprintf(stdout, " ");
        }

        fprintf(stdout, "%d", arr[i]);
    }
    fprintf(stdout, "\n");
    return;
}

void new_merge_sort (int *arr, size_t left_index, size_t right_index) {
    int *left_arr, *right_arr;
    size_t left_arr_size, right_arr_size;

    size_t mid_index, i, j, k;

    mid_index = (left_index + right_index) / 2;
    print_arr(arr, left_index, right_index);

    if (left_index >= right_index) {
        return;
    }

    new_merge_sort(arr, mid_index + 1, right_index);
    new_merge_sort(arr, left_index, mid_index);

    left_arr_size = mid_index - left_index + 1;
    right_arr_size = right_index - mid_index;

    left_arr = (int *) alloca(sizeof(int) * left_arr_size);
    left_arr = (int *) memcpy(left_arr, (arr + left_index), sizeof(int) * left_arr_size);

    right_arr = (int *) alloca(sizeof(int) * right_arr_size);
    right_arr = (int *) memcpy(right_arr, (arr + mid_index + 1), sizeof(int) * right_arr_size);

    i = 0;
    j = 0;
    k = left_index;
    while (i < left_arr_size && j < right_arr_size) {
        if (left_arr[i] >= right_arr[j]) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }

    while (i < left_arr_size) {
        arr[k++] = left_arr[i++];
    }

    while (j < right_arr_size) {
        arr[k++] = right_arr[j++];
    }

    print_arr(arr, left_index, right_index);
    return;
}

int main (int args, char **argv) {
    char *input_string;
    size_t input_string_size, input_number;
    int input, i;

    int *number_arr;
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
    
    new_merge_sort(number_arr, 0, number_arr_size - 1);

    free(number_arr);
    return 0;
}
