#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define SCALE_VARIABLE 32


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

bool could_last_op_be_multiplication(
    long long new_input_list[SCALE_VARIABLE],
    long long input_list[SCALE_VARIABLE],
    int input_list_length
) {
    long long required_output = input_list[0];
    long long last_num = input_list[input_list_length -1];

    if ((required_output % last_num) == 0) {
        new_input_list[0] = required_output / last_num;
        int i = 1;
        for (i = 1; i < input_list_length - 1; i++) {
            new_input_list[i] = input_list[i];
        }
        return true;
    }

    return false;
}

bool could_last_op_be_addition(
    long long new_input_list[SCALE_VARIABLE],
    long long input_list[SCALE_VARIABLE],
    int input_list_length
) {
    long long required_output = input_list[0];
    long long last_num = input_list[input_list_length -1];
    if ((required_output - last_num) >=0) {
        new_input_list[0] = required_output - last_num;
        int i = 1;
        for (i = 1; i < input_list_length - 1; i++) {
            new_input_list[i] = input_list[i];
        }
        return true;
    }
    return false;
}

bool could_last_op_be_concatenation(
    long long new_input_list[SCALE_VARIABLE],
    long long input_list[SCALE_VARIABLE],
    int input_list_length
) {
    long long required_output = input_list[0];
    long long last_num = input_list[input_list_length -1];


    char str[SCALE_VARIABLE];
    sprintf(str, "%lld", last_num);
    int last_num_length = strlen(str);

    int must_divide_by = 10;
    int i = 1;
    while (i < last_num_length) {
        must_divide_by = must_divide_by * 10;
        i++;
    }

    long long diff = required_output - last_num;

    if ((diff % must_divide_by) == 0) {
        new_input_list[0] = diff / must_divide_by;
        int i = 1;
        for (i = 1; i < input_list_length - 1; i++) {
            new_input_list[i] = input_list[i];
        }
        return true;
    }
    return false;
}

bool resolve_array(
    long long array[SCALE_VARIABLE], 
    int array_length
) {
    long long required_output = array[0];

    if (array_length < 3) {
        return false;
    }
    printf("Resolving array:\n");
    print_array_of_long_longs(array, array_length);

    long long addition_array[SCALE_VARIABLE];
    bool could_be_addition = could_last_op_be_addition(addition_array, array, array_length);

    long long multiplication_array[SCALE_VARIABLE];
    bool could_be_multiplication = could_last_op_be_multiplication(multiplication_array, array, array_length);

    long long concatenation_array[SCALE_VARIABLE];
    bool could_be_concatenation = could_last_op_be_concatenation(concatenation_array, array, array_length);
    
    if (could_be_addition) {
        if (addition_array[0] == addition_array[1]) {
            return true;
        }
        else if (resolve_array(addition_array, array_length -1)) {
            return true;
        }
    }

    if (could_be_multiplication) {
        if (multiplication_array[0] == multiplication_array[1]) {
            return true;
        }
        else if (resolve_array(multiplication_array, array_length -1)) {
            return true;
        }
    }

    if (could_be_concatenation) {
        if (concatenation_array[0] == concatenation_array[1]) {
            return true;
        }
        else if (resolve_array(concatenation_array, array_length - 1)) {
            return true;
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
        printf("NEW OUTPUT CALCULATION: ------------------ %s\n", line);

        long long array[SCALE_VARIABLE] = {0};
        int array_length = process_line_into_array(line, array);

        long long number_under_test = array[0];

        if (resolve_array(array, array_length)) {
            running_total += number_under_test;
        //printf("Running total: %lld\n", running_total);
        };
    }
    printf("Running total: %lld\n", running_total);
    fclose(input_file);
    
    return (0);
}