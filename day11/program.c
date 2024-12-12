#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "babytest.txt"
#define SCALE_VARIABLE 255

bool has_even_length(long long number) {
    char string[SCALE_VARIABLE];
    sprintf(string, "%lld", number);
    int length = strlen(string);
    if (length % 2) {
        return false;
    }
    else {
        return true;
    }
}

void split_even_length_number_into_two(
    long long number,
    long long output_list[2]
) {
    char string[SCALE_VARIABLE];
    sprintf(string, "%lld", number);
    int length = strlen(string);
    int half = length / 2;
    
    long long splitter = power(10, half);

    output_list[1] = number % splitter;
    output_list[0] = (number - output_list[1]) / splitter;

}

int blink_at_number(
    long long number,
    long long output_list[2]
) {
    if (number == 0) {
        output_list[0] = 1;
        return 1;
    }
    else if (has_even_length(number)) {
        split_even_length_number_into_two(number, output_list);
        return 2;
    }
    else {
        output_list[0] = number * 2024;
        return 1;
    }
}

int resolve_number(
    long long number,
    int blinks_so_far
) {
    if (blinks_so_far == 50) {
        return 1;
    }
    else {
        long long output_list[2];
        int num_outputs = blink_at_number(number, output_list);
        int i = 0;
        int total = 0;
        for (i = 0; i < num_outputs; i++) {
            total += resolve_number(output_list[i], blinks_so_far + 1);
        }
        return total;
    }
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    int i = 0;
    int initial_list[SCALE_VARIABLE];

    char line[SCALE_VARIABLE];
    while (fgets(line, 255, input_file)) {
        line[strcspn(line, "\n")] =0;

        char *token = strtok(line, " ");
        while (token != NULL) {
            initial_list[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }
    }

    //print_array_of_ints(initial_list, i);

    int j = 0;
    int total = 0;
    for (j = 0; j < i; j++) {
        total += resolve_number(initial_list[j], 0);
    }
    printf("total: %d\n", total);
    fclose(input_file);
    
    return (0);
}