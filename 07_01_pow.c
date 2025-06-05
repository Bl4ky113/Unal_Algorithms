
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <math.h>

#define CUSTOM_INT_DIGITS 128

typedef struct buffer_int {
    size_t index;
    char sign;
    char buff[CUSTOM_INT_DIGITS + 1];
} bint;

typedef struct queue_node {
    bint *val;
    struct queue_node *next;
    struct queue_node *prev;
} qu_n;

qu_n *new_queue () {
    qu_n *qu = (qu_n *) malloc(sizeof(qu_n));
    qu->val = NULL;
    qu->next = qu;
    qu->prev = qu;

    return qu;
}

void enqueue (qu_n *qu, bint *new_value) {
    qu_n *new_node;

    new_node = (qu_n *) malloc(sizeof(qu_n));
    new_node->val = new_value;

    new_node->next = qu->next;
    qu->next = new_node;

    new_node->next->prev = new_node;
    new_node->prev = qu;

    return;
}

bint *dequeue (qu_n *qu) {
    qu_n *dequeue_node; 
    bint *val;

    dequeue_node = qu->prev; 
    val = dequeue_node->val;

    dequeue_node->prev->next = qu; 
    qu->prev = dequeue_node->prev;
    free(dequeue_node);
    return val;
}

bint *new_bint () { 
    bint *new_int;
    size_t i;

    new_int = (bint *) malloc(sizeof(bint));

    new_int->index = 0;
    new_int->sign = 1;
    for (i = 0; i < CUSTOM_INT_DIGITS; i++) {
        new_int->buff[i] = 0;
    }

    return new_int;
}

bint *new_bint_from_int (int old_int) {
    bint *new_int;
    int tmp_int, i;

    new_int = new_bint();
    i = 0;
    
    for (tmp_int = old_int; tmp_int > 0; tmp_int /= 10) {
        new_int->buff[i++] = tmp_int % 10;
    }

    new_int->index = i - 1;
    return new_int;
}

void print_bint (bint *number) {
    int current_digit;

    if (number->index > CUSTOM_INT_DIGITS) {
        current_digit = CUSTOM_INT_DIGITS;
    } else {
        current_digit = number->index;
    }

    for (; current_digit >= 0; current_digit--) {
        fprintf(stdout, "%d", number->buff[current_digit]);
    }

    return;
}

int compare_bint (bint *val_1, bint *val_2) {
    int i;

    if (val_1->index > val_2->index) {
        return 1;
    } else if (val_1->index < val_2->index) {
        return -1;
    }

    for (i = val_1->index; i >= 0; i--) {
        if (val_1->buff[i] > val_2->buff[i]) {
            return 1;
        } else if (val_1->buff[i] < val_2->buff[i]) {
            return -1;
        }
    }

    return 0;
}

bint *mult_bint (bint *val_1, bint *val_2) {
    int current_result, current_digit, next_digit_remainder, tmp_result, i, j, k;
    bint *multiplicant, *multiplier, *result;

    result = new_bint();
    next_digit_remainder = 0;

    if (val_1->index > val_2->index) {
        multiplicant = val_1;
        multiplier = val_2;
    } else {
        multiplicant = val_2;
        multiplier = val_1;
    }

    for (i = 0; i <= multiplier->index; i++) {
        k = i;
        for (j = 0; j <= multiplicant->index; j++) {
            current_result = multiplicant->buff[j] * multiplier->buff[i];

            if (next_digit_remainder > 0) {
                current_result += next_digit_remainder;
            }
            
            current_digit = current_result % 10;
            next_digit_remainder = (current_result - current_digit) / 10;

            result->buff[k] += current_digit;

            if (result->buff[k] >= 10) {
                tmp_result = result->buff[k];
                result->buff[k] = tmp_result % 10;
                next_digit_remainder += (tmp_result - result->buff[k]) / 10;
            }

            k++;
        }

        if (next_digit_remainder > 0) {
            result->buff[k++] += next_digit_remainder;
            next_digit_remainder = 0;
        }
    }

    result->index = k - 1;

    if (val_1->sign * val_2->sign > 0) {
        result->sign = 1;
    } else {
        result->sign = -1;
    }

    return result;
}

bint *recursive_pow (bint *a, int n, qu_n *pow_qu) {
    double n_half;
    bint *result_t, *result_1, *result_2, *tmp_bint;

    if (n == 0) {
        return new_bint_from_int(1);
    } else if (n == 1) {
        return a;
    }

    n_half = floor((double) n / 2.0);

    result_1 = recursive_pow(a, n_half, pow_qu);
    result_2 = recursive_pow(a, n_half, pow_qu);

    if (n % 2 != 0) {
        tmp_bint = mult_bint(result_2, a);

        if (result_2 != a) {
            free(result_2);
        }

        result_2 = tmp_bint;
    }

    result_t = mult_bint(result_1, result_2);

    if (result_2 != a) {
        free(result_2);
    }

    if (pow_qu->next != pow_qu) {
        if (compare_bint(result_1, pow_qu->next->val) == 1) {
            enqueue(pow_qu, result_1);
        } else if (result_1 != a) {
            free(result_1);
        }
    } else {
        enqueue(pow_qu, result_1);
    }


    return result_t;
}

int main (int args, char **argv) {
    int input_a, input_n, input_number, i;
    bint *bint_a, *num;
    qu_n *pow_queue;

    fscanf(stdin, "%d\n", &input_number);

    pow_queue = new_queue();

    for (i = 0; i < input_number; i++) {
        fscanf(stdin, "%d\t%d", &input_a, &input_n);
        bint_a = new_bint_from_int(input_a);
        
        enqueue(pow_queue, recursive_pow(bint_a, input_n, pow_queue));
        
        while (pow_queue->next != pow_queue) {
            num = dequeue(pow_queue);

            print_bint(num);
            fprintf(stdout, " ");

            free(num);
        }
        fprintf(stdout, "\n");
    }

    return 0;
}
