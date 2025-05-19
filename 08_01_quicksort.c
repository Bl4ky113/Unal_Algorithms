
#include <stdlib.h>
#include <stdio.h>

#define MIN_LIST_SIZE 2

size_t quick_sort_partition (int *list, int low, int top) {
    int pivot, tmp;
    size_t i, j;

    pivot = list[top];
    i = low - 1;

    for (j = low; j < top; j++) {
        if (list[j] <= pivot) {
            i++;

            tmp = list[i];
            list[i] = list[j];
            list[j] = tmp;
        }
    }

    tmp = list[i + 1];
    list[i + 1] = list[top];
    list[top] = tmp;

    return i + 1;
}

void quick_sort (int *list, int low, int top) {
    int index;

    if (low < top) {
        index = quick_sort_partition(list, low, top);
        fprintf(stdout, "%d\n", list[index]);

        quick_sort(list, low, index - 1);
        quick_sort(list, index + 1, top);
    }

    return;
}

void print_list (int *list, size_t size) {
    int i;

    for (i = 0; i < size; i++) {
        fprintf(stdout, "%d ", list[i]);
    }
    fprintf(stdout, "\n");

    return;
}

int main (int args, char** argv) {
    char *input_str, *tmp_input_str;
    size_t input_str_size;
    int input, input_number, i;

    int *number_list;
    size_t number_list_size;

    input_str = NULL;
    input_str_size = 0;

    if (getline(&input_str, &input_str_size, stdin) < 0) {
        fprintf(stderr, "ERROR GETTING INPUT LINE");
        return -1;
    }

    number_list = (int *) malloc(sizeof(int) * MIN_LIST_SIZE);
    number_list_size = MIN_LIST_SIZE;

    tmp_input_str = input_str;
    input_number = 0;

    while (sscanf(tmp_input_str, "%d %n", &input, &i) > 0) {
        if (number_list_size <= input_number) {
            number_list_size *= 2;
            number_list = (int *) realloc(number_list, sizeof(int) * number_list_size);

            if (number_list == NULL) {
                fprintf(stderr, "ERROR REALOCATING MEMORY FOR NUMBER LIST");
                return -1;
            }
        }

        number_list[input_number++] = input;
        tmp_input_str += i;
    }

    if (number_list_size > input_number) {
        number_list_size = input_number;

        number_list = (int *) realloc(number_list, sizeof(int) * number_list_size);
        if (number_list == NULL) {
            fprintf(stderr, "ERROR DEALLOCATING MEMORY IN NUMBER LIST");
            return -1;
        }
    }

    tmp_input_str = NULL;
    free(input_str);

    quick_sort(number_list, 0, number_list_size - 1);

    print_list(number_list, number_list_size);
    free(number_list);
    return 0;
}
