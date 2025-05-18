
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define LOG_EPSILON 0.000001 // Smallest possible double (?)

typedef enum {
    CONSTANT = 2, /* d = 0 */
    LINEAR = 3, /* d = 1 */
    NPOWER = 5, /* d > 1 */
    INTLOG = 7,
    LOG2 = 11,
    LOGB = 13
} func_cases;

typedef enum {
    ALTBD = 17,
    AEQBD = 19,
    AGTBD = 23
} master_theorem_cases;

void print_d_power (long int current_case, int d) {
    if (current_case % CONSTANT == 0) {
        if (current_case % AEQBD == 0) {
            return;
        }

        fprintf(stdout, "1");
    } else if (current_case % LINEAR == 0) {
        fprintf(stdout, "n");
    } else {
        fprintf(stdout, "n^(%d)", d);
    }

    return;
}

void print_log (long int current_case, int b, int a, long double log_b_a) {
    if ((current_case % INTLOG == 0) && (current_case % AGTBD == 0)) {
        fprintf(stdout, "%.0LF", log_b_a);
        return;
    } else if ((current_case % LOG2 == 0) || (current_case % AEQBD == 0)) {
        fprintf(stdout, "lg");
    } else {
        fprintf(stdout, "log_(%d)", b);
    }

    if (current_case % AEQBD == 0) {
        fprintf(stdout, "(n)");
    } else {
        fprintf(stdout, "(%d)", a);
    }

    return;
}

void print_log_power (long int current_case, int b, int a, long double log_b_a) {
    if (log_b_a == 1) {
        fprintf(stdout, "n");
        return;
    }
    
    fprintf(stdout, "n^(");
    print_log(current_case, b, a, log_b_a);
    fprintf(stdout, ")");
    return;
}


int main (int args, char **argv) {
    int a, b, c, d;
    long int current_case;
    long double log_a, log_b, log_b_a, pow_b_d;

    current_case = 1;

    printf("\n%lf\n", LOG_EPSILON);

    fscanf(stdin, "f(n) = %d", &a);
    fscanf(stdin, "f(n/%d)", &b);
    fscanf(stdin, "+%dn^%d", &c, &d);

    log_a = logl((long double) a);
    log_b = logl((long double) b);
    log_b_a = log_a / log_b;

    pow_b_d = powl((long double) b, (long double) d);

    if (d == 0) {
        current_case *= CONSTANT;
    } else if (d == 1) {
        current_case *= LINEAR;
    } else {
        current_case *= NPOWER;
    }

    if (
        (
            (log_b_a - floorl(log_b_a) < LOG_EPSILON) && 
            (log_b_a - floorl(log_b_a) > -1 * LOG_EPSILON)
        ) ||
        (
            (log_b_a - ceill(log_b_a) < LOG_EPSILON) && 
            (log_b_a - ceill(log_b_a) > -1 * LOG_EPSILON)
        )
    ) {
        current_case *= INTLOG;
    }

    if (b == 2) {
        current_case *= LOG2;
    } else {
        current_case *= LOGB;
    }

    if ((long double) a < pow_b_d) {
        current_case *= ALTBD;
    } else if ((long double) a > pow_b_d) {
        current_case *= AGTBD;
    } else {
        current_case *= AEQBD;
    }

    fprintf(stdout, "O(");
    if (current_case % ALTBD == 0) {
        print_d_power(current_case, d);
    } else if (current_case % AGTBD == 0) {
        print_log_power(current_case, b, a, log_b_a);
    } else {
        print_d_power(current_case, d);
        print_log(current_case, b, a, log_b_a);
    }
    fprintf(stdout, ")\n");
    printf("%d %d : %LF : %LF %LF\n", b, a, log_b_a, floorl(log_b_a), ceill(log_b_a));
    printf("%LF : %LF\n", log_b_a - floorl(log_b_a), log_b_a - ceill(log_b_a));

    return 0;
}
