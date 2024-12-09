#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "weird.txt"
#define SCALE_VARIABLE 16


int process_line_into_array(
    char line[SCALE_VARIABLE], 
    long long array[SCALE_VARIABLE]
) {
    char * token = strtok(line, ":");
    array[0] = atoll(token);

    int array_length = 1;
    token = strtok(NULL, " ");
    while (token != NULL) {
        array[array_length] = atoll(token);
        token = strtok(NULL, " ");
        array_length++;
    }
    return array_length;
}

long long apply_multiplication_to_first_two_inputs(
    long long input_list[SCALE_VARIABLE],
    long long new_input_list[SCALE_VARIABLE],
    int input_list_length
) {
    long long num1 = input_list[0];
    long long num2 = input_list[1];

    new_input_list[0] = num1 * num2;
    int i = 1;
    for (i = 1; i < input_list_length - 1; i++) {
        new_input_list[i] = input_list[i + 1];
    }
    return new_input_list[0];
}   

long long apply_addition_to_first_two_inputs(
    long long input_list[SCALE_VARIABLE],
    long long new_input_list[SCALE_VARIABLE],
    int input_list_length
) {
    long long num1 = input_list[0];
    long long num2 = input_list[1];

    new_input_list[0] = num1 + num2;
    int i = 1;
    for (i = 1; i < input_list_length - 1; i++) {
        new_input_list[i] = input_list[i + 1];
    }
    return new_input_list[0];
}

bool resolve_array(
    long long array[SCALE_VARIABLE], 
    int array_length,
    long long required_output
) {

    //printf("\n");
    //printf("Resolving array:\n");
    //print_array_of_long_longs(array, array_length);
    //printf("\n");

    if (array_length < 2) {
        //printf("Array cannot resolve.\n");
        return false;
    }

    long long multiplication_output = 0;
    long long try_multiplication_array[SCALE_VARIABLE];
    multiplication_output = apply_multiplication_to_first_two_inputs(
        array,
        try_multiplication_array,
        array_length
    );

    //printf("multiplication array:\n");
    //print_array_of_long_longs(try_multiplication_array, array_length - 1);

    long long addition_output = 0;
    long long try_addition_array[SCALE_VARIABLE];
    addition_output = apply_addition_to_first_two_inputs(
        array,
        try_addition_array,
        array_length
    );

    //printf("addition array:\n");
    //print_array_of_long_longs(try_addition_array, array_length - 1);

    if ((multiplication_output == required_output) ||
        (addition_output == required_output)) {
        return true;
    }
    else if (array_length > 2) {
        if ((resolve_array(try_multiplication_array, array_length - 1, required_output)) ||
            (resolve_array(try_addition_array, array_length - 1, required_output))) {
                return true;
            }
        else {
            return false;
        }
    }

    return false;
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    long long running_total = 0;

    char line[512];
    while (fgets(line, 512, input_file)) {
        line[strcspn(line, "\n")] =0;
        //printf("NEW OUTPUT CALCULATION: ------------------ %s\n", line);

        long long array[SCALE_VARIABLE] = {0};
        int array_length = process_line_into_array(line, array);

        long long number_under_test = array[0];

        int i = 0;
        for (i = 0; i < array_length; i++) {
            array[i] = array[i+1];
        }
        array_length = array_length - 1;

        if (resolve_array(array, array_length, number_under_test)) {
            running_total += number_under_test;
        //printf("Running total: %lld\n", running_total);
        };
    }
    printf("Running total: %lld\n", running_total);
    fclose(input_file);
    
    return (0);
}