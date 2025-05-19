
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <math.h>

typedef struct queue_node {
    long long int val;
    struct queue_node *next;
    struct queue_node *prev;
} qu_n;

qu_n *new_queue () {
    qu_n *qu = (qu_n *) malloc(sizeof(qu_n));
    qu->val = 0;
    qu->next = qu;
    qu->prev = qu;

    return qu;
}

void enqueue (qu_n *qu, long long int new_value) {
    qu_n *new_node;

    new_node = (qu_n *) malloc(sizeof(qu_n));
    new_node->val = new_value;

    new_node->next = qu->next;
    qu->next = new_node;

    new_node->next->prev = new_node;
    new_node->prev = qu;

    return;
}

long long int dequeue (qu_n *qu) {
    qu_n *dequeue_node; 
    long long int val;

    dequeue_node = qu->prev; 
    val = dequeue_node->val;

    dequeue_node->prev->next = qu; 
    qu->prev = dequeue_node->prev;
    free(dequeue_node);
    return val;
}

long long int recursive_pow (int a, int n, qu_n *pow_qu) {
    double n_half;
    long long int result_1, result_2;

    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    }

    n_half = floor((double) n / 2.0);

    result_1 = recursive_pow(a, n_half, pow_qu);
    result_2 = recursive_pow(a, n_half, pow_qu);

    if (n % 2 != 0) {
        result_2 *= (long long int) a;
    }

    if (result_1 > pow_qu->next->val) {
        enqueue(pow_qu, result_1);
    }

    return (long long int) result_1 * (long long int) result_2;
}

int main (int args, char **argv) {
    int input_a, input_n, input_number, i;
    long long int result;
    qu_n *pow_queue;

    fscanf(stdin, "%d\n", &input_number);

    pow_queue = new_queue();

    for (i = 0; i < input_number; i++) {
        fscanf(stdin, "%d\t%d", &input_a, &input_n);
        result = (long long int) recursive_pow(input_a, input_n, pow_queue);

        enqueue(pow_queue, result);
        
        while (pow_queue->next != pow_queue) {
            fprintf(stdout, "%Ld ", dequeue(pow_queue));
        }
        fprintf(stdout, "\n");
    }

    return 0;
}
