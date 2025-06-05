
#include <stdlib.h>
#include <stdio.h>

#define MIN_HEAP_SIZE 2

void print_arr (int *arr, size_t arr_size) {
    int *ptr;

    for (ptr = arr; ptr < (arr + arr_size); ptr++) {
        if (ptr != arr) {
            fprintf(stdout, " ");
        }

        fprintf(stdout, "%d", *ptr);
    }
    fprintf(stdout, "\n");

    return;
}

void min_heapify (int *heap, int index, int *heap_size) {
    int l_index, r_index, smallest_index, tmp;

    l_index = ((index + 1) * 2) - 1;
    r_index = ((index + 1) * 2);
    smallest_index = index;

    if (l_index < (*heap_size) && heap[l_index] < heap[index]) {
        smallest_index = l_index;
    }

    if (r_index < (*heap_size) && heap[r_index] < heap[smallest_index]) {
        smallest_index = r_index;
    }

    if (smallest_index == index) {
        return;
    }

    tmp = heap[index];
    heap[index] = heap[smallest_index];
    heap[smallest_index] = tmp;

    min_heapify(heap, smallest_index, heap_size);
    return;
}

void max_heapify (int *heap, int index, int *heap_size) {
    int l_index, r_index, largest_index, tmp;

    l_index = ((index + 1) * 2) - 1;
    r_index = ((index + 1) * 2);
    largest_index = index;

    if (l_index < (*heap_size) && heap[l_index] > heap[index]) {
        largest_index = l_index;
    }

    if (r_index < (*heap_size) && heap[r_index] > heap[largest_index]) {
        largest_index = r_index;
    }

    if (largest_index == index) {
        return;
    }

    tmp = heap[index];
    heap[index] = heap[largest_index];
    heap[largest_index] = tmp;

    max_heapify(heap, largest_index, heap_size);
    return;
}

void build_min_heap(int *heap, int *heap_size) {
    int i;

    for (i = ((*heap_size) / 2) - 1; i >= 0; i--) {
        min_heapify(heap, i, heap_size);
        print_arr(heap, *heap_size);
    }

    return;
}

void build_max_heap(int *heap, int *heap_size) {
    int i;

    for (i = ((*heap_size) / 2) - 1; i >= 0; i--) {
        max_heapify(heap, i, heap_size);
        print_arr(heap, *heap_size);
    }

    return;
}

int main (int args, char **varg) {
    char *input_str, *input_str_ptr;
    size_t input_str_size;
    int input, input_size, i;

    int *heap_arr;
    int heap_size, heap_length;

    input_str = NULL;
    input_str_size = 0;

    if (getline(&input_str, &input_str_size, stdin) < 0) {
        fprintf(stderr, "ERROR GETTING INPUT LINE\n");
        return -1;
    }

    input_str_ptr = input_str;
    input_size = 0;

    heap_length = MIN_HEAP_SIZE;
    heap_arr = (int *) malloc(sizeof(int) * heap_length);

    while (sscanf(input_str_ptr, "%d %n", &input, &i) >= 0) {
        if (input_size >= heap_length) {
            heap_length *= 2;
            heap_arr = (int *) realloc(heap_arr, sizeof(int) * heap_length);

            if (heap_arr == NULL) {
                fprintf(stderr, "ERROR ALLOCATING MORE MEMORY FOR HEAP\n");
                return -1;
            }
        }

        heap_arr[input_size++] = input;    
        input_str_ptr += i;
    }

    if (input_size < heap_length) {
        heap_length = input_size;
        heap_arr = (int *) realloc(heap_arr, sizeof(int) * heap_length);

        if (heap_arr == NULL) {
            fprintf(stderr, "ERROR ALLOCATING LESS MEMORY FOR HEAP\n");
        }
    }

    heap_size = heap_length;

    if (heap_arr[0] > heap_arr[heap_size - 1]) {
        build_min_heap(heap_arr, &heap_size);
    } else {
        build_max_heap(heap_arr, &heap_size);
    }
    
    return 0;
}
