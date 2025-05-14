
#include <stdio.h>
#include <cmath>

int main (int args, char **argv) {
    int i, input_number;
    int input_1, input_2;

    fscanf(stdin, "%d", &input_number);

    for (i = 0; i < input_number; i++) {
        fscanf(stdin, "%d %d", &input_1, &input_2);

        fprintf(
            stdout, 
            "%d %d %.0lf\n", 
            input_1 + input_2,
            input_1 * input_2,
            pow((double) input_1, (double) input_2)
        );
    }

    return 0;
}
