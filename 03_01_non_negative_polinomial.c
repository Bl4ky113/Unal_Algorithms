
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>

#include <malloc.h>

typedef struct polynomial_node {
    int val;
    struct polynomial_node *next;
} pol_n;

typedef struct queue_node {
    void *val;
    struct queue_node *next;
    struct queue_node *prev;
} que_n;

que_n *new_queue () {
    que_n *que = (que_n *) malloc(sizeof(que_n));
    que->val = NULL;
    que->next = que;
    que->prev = que;

    return que;
}

pol_n *new_polinomial () {
    pol_n *pol = (pol_n *) malloc(sizeof(pol_n));
    pol->val = -1; // On Sentinel, value is the degree of the node
    pol->next = NULL;

    return pol;
}

void enqueue (que_n *que, void *new_value) {
    que_n *new_node;

    new_node = (que_n *) malloc(sizeof(que_n));
    new_node->val = new_value;

    new_node->next = que->next;
    que->next = new_node;

    new_node->next->prev = new_node;
    new_node->prev = que;

    return;
}

void add_pol (pol_n *pol, int new_value) {
    pol_n *new_node, *tmp_node;

    tmp_node = pol->next;

    new_node = (pol_n *) malloc(sizeof(pol_n));
    new_node->val = new_value;
    pol->val++;
    new_node->next = tmp_node;

    pol->next = new_node;
    return;
}

pol_n *add_after_pol (pol_n *pol, pol_n *pol_node, int new_value) {
    if (pol_node->next != NULL) {
        return NULL;
    }

    pol_n *new_node;

    new_node = (pol_n *) malloc(sizeof(pol_n));
    new_node->val = new_value;
    pol->val++;
    new_node->next = NULL;

    pol_node->next = new_node;
    return new_node;
}

void *dequeue (que_n *que) {
    que_n *dequeue_node; 
    void *val;

    dequeue_node = que->prev; 
    val = dequeue_node->val;

    dequeue_node->prev->next = que; 
    que->prev = dequeue_node->prev;
    free(dequeue_node);
    return val;
}

int pop_pol (pol_n *pol) {
    pol_n *pop_node;
    int val;

    if (pol->next == NULL) {
        return INT_MIN;
    }

    pop_node = pol->next;
    val = pop_node->val;

    pol->next = pop_node->next;
    pol->val--;
    free(pop_node);
    return val;
}

void delete_que (que_n *que) {
    while(que->next != que) {
        dequeue(que);
    }
}

void delete_pol (pol_n *pol) {
    while(pol->next != NULL) {
        pop_pol(pol);
    }
}

que_n *synthetic_division (pol_n *pol) {
    que_n *polinomial_que;
    pol_n *new_pol, *prev_pol, *prev_pol_last_node;
    int current_pol_val;

    polinomial_que = new_queue();
    current_pol_val = pop_pol(pol);

    prev_pol = NULL;

    while (pol->next != NULL || current_pol_val != INT_MIN) {
        new_pol = new_polinomial();

        if (prev_pol == NULL) {
            add_pol(new_pol, current_pol_val);

            prev_pol = new_pol;
            prev_pol_last_node = new_pol->next;

            enqueue(polinomial_que, new_pol);
            current_pol_val = pop_pol(pol);
            continue;
        }

        new_pol->val = prev_pol->val;
        new_pol->next = prev_pol->next;
        prev_pol_last_node = add_after_pol(new_pol, prev_pol_last_node, current_pol_val);

        prev_pol = new_pol;
        enqueue(polinomial_que, new_pol);
        current_pol_val = pop_pol(pol);
    }

    return polinomial_que;
}

long double evaluate_polinomial (pol_n *pol, int value) {
    pol_n *current_node;
    int current_degree;
    long double result;

    result = 0.0;

    if (pol->next == NULL) {
        return 0;
    }

    current_node = pol->next;
    current_degree = pol->val;
    while (current_node != NULL && current_degree >= 0) {
        if (current_degree > 0) {
            result += (double) current_node->val * pow(value, current_degree--);
        } else {
            result += (double) current_node->val;
            current_degree--;
        }

        current_node = current_node->next;
    }

    return result;
}

int main (int arg, char **argv) {
    int num_inputs, input, i, j;
    char *line_input;
    size_t line_size;

    int mininum_variable;
    long double current_poly_value;
    pol_n *poly, *current_poly;
    que_n *pol_queue;

    poly = new_polinomial();

    fscanf(stdin, "%d\n", &num_inputs);

    for (i = 0; i < num_inputs; i++) {
        line_input = NULL;
        line_size = 0;

        if (getline(&line_input, &line_size, stdin) < 0) {
            fprintf(stdout, "ERROR READING LINE!");
            break;
        }

        while (sscanf(line_input, "%d %n", &input, &j) > 0) {
            add_pol(poly, input);
            line_input += j;
        }
        
        pol_queue = synthetic_division(poly);
        current_poly = (pol_n *) dequeue(pol_queue);
        current_poly_value = INT_MIN;
        mininum_variable = 0;

        while (current_poly != NULL) {
            current_poly_value = evaluate_polinomial(current_poly, mininum_variable);

            if (current_poly_value >= 0) {
                if (pol_queue->next == pol_queue) {
                    delete_pol(current_poly);
                }
                free(current_poly);

                current_poly = (pol_n *) dequeue(pol_queue);
                continue;
            }

            mininum_variable++;
        }

        fprintf(stdout, "%d\n", mininum_variable);
    }

    return 0;
}
