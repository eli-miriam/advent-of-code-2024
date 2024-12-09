#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define SCALE_VARIABLE 65535

void print_list(int list[SCALE_VARIABLE], int length) {
    int i = 0;
    for (i = 0; i < length; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int get_num1_from_string(char *string) {
    char temp_str[2];
    temp_str[0] = string[0];
    temp_str[1] = string[1];
    return atoi(temp_str);
}

int get_num2_from_string(char *string) {
    char temp_str[2];
    temp_str[0] = string[3];
    temp_str[1] = string[4];
    return atoi(temp_str);
}

int *get_int_list_from_ordering(char *string_ordering, int list[SCALE_VARIABLE]) {
    int i = 0;
    char *token = strtok(string_ordering, ",");
    while (token != NULL) {
        list[i] = atoi(token);
        i++;
        token = strtok(NULL, ",");
    }
    return list;
}

bool is_well_ordered(
    int int_ordering[SCALE_VARIABLE], 
    int list_length, 
    int rulepairs[SCALE_VARIABLE][2]) {
    
    int i = 0;
    while (rulepairs[i][0] != 0) {
        int first_index = -1;
        int second_index = -1;

        int j = 0;
        for (j = 0; j < list_length; j++){
            if (int_ordering[j] == rulepairs[i][0]) {
                first_index = j;
            }
            if (int_ordering[j] == rulepairs[i][1]) {
                second_index = j;
            }
        }
        if (second_index != -1) {
            if (first_index > second_index) {
                return false;
            }
        }
        i++;
    }
    return true;
}

void find_relevant_rulepairs_for_ordering(
                int relevant_rulepairs[SCALE_VARIABLE][2],
                int all_rulepairs[SCALE_VARIABLE][2],
                int int_ordering[SCALE_VARIABLE],
                int list_length) {
    int i = 0;
    int j = 0;
    while (all_rulepairs[i][0] != 0) {
        /* loop over the ordering and see if the rule is relevant */
        int k = 0;
        bool one_half_of_rule_in_list = false;
        for (k = 0; k < list_length; k++) {
            if ((int_ordering[k] == all_rulepairs[i][0]) ||
                (int_ordering[k] == all_rulepairs[i][1])) {
                if (!one_half_of_rule_in_list) {
                    one_half_of_rule_in_list = true;
                }
                else {
                    /* We found both halves; the rule is relevant */
                    relevant_rulepairs[j][0] = all_rulepairs[i][0];
                    relevant_rulepairs[j][1] = all_rulepairs[i][1];
                    j++;
                    relevant_rulepairs[j][0] = 0;
                    relevant_rulepairs[j][1] = 0;
                }
            }
        }
        i++;
    }

}

int *return_well_ordered_version(
    int int_ordering[SCALE_VARIABLE], 
    int list_length,
    int rulepairs[SCALE_VARIABLE][2]) {
    /* algorithm : 
    - start with one variable; by definition must be well ordered.
    - try to add the next number in by first adding in in position 0 and then 
    continuining the existing list; then if that fails to be valid, try in position 1, etc.
    - the formulation of the question implies that there is only one valid ordering.
    - when you've succeeded in adding in all numbers, you have a valid re-ordering.
    */
    int well_ordered_version[SCALE_VARIABLE] = {0};
    int i = 0;
    for (i = 0; i < list_length; i++) {
        int num_to_insert = int_ordering[i];
        int index_to_check = 0;
        bool intermediate_ordering_found = false;

        for (index_to_check = 0; index_to_check < i+1; index_to_check++) {
            if (!intermediate_ordering_found) {
                int test_version[SCALE_VARIABLE] = {0};
                bool num_already_inserted = false;
                int index_to_copy_to = 0;

                for (index_to_copy_to = 0; index_to_copy_to < i + 1; index_to_copy_to++) {
                    test_version[index_to_check] = num_to_insert;

                    if (index_to_copy_to == index_to_check) {
                        num_already_inserted = true;
                    }
                    test_version[index_to_copy_to + num_already_inserted] = well_ordered_version[index_to_copy_to];
                    
                }
                if (is_well_ordered(test_version, i+1, rulepairs)) {
                    int k = 0;
                    for (k = 0; k < i+1; k++) {
                        well_ordered_version[k] = test_version[k];
                    intermediate_ordering_found = true;
                    printf("test_index: %d, i: %d\n", index_to_check, i);
                    print_list(well_ordered_version, i+1);
                    }
                }
            }
        }
        
    }
    i = 0;
    for (i = 0; i < list_length; i++) {
        int_ordering[i] = well_ordered_version[i];
    }
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    int i = 0;
    int all_rulepairs[SCALE_VARIABLE][2];
    char line[SCALE_VARIABLE];
    int running_total_part_1 = 0;
    int running_total_part_2 = 0;

    while (fgets(line, SCALE_VARIABLE, input_file)) {
        line[strcspn(line, "\n")] =0;

        if (strlen(line) == 0){
            printf("BLANK NEWLINE\n");
        }
        else if (strlen(line) < 7) {
            /* this is a rule */
            all_rulepairs[i][0] = get_num1_from_string(line);
            all_rulepairs[i][1] = get_num2_from_string(line);
            i++;
        }
        else {
            /* this is an update ordering. */
            int list_length = (strlen(line) + 1) / 3;
            int median_index = list_length / 2;
            
            /* split string into list of ints, using a copy so as not to 
            consume the original with strtok */
            char copy_of_ordering[SCALE_VARIABLE];
            strcpy(copy_of_ordering, line);
            int list[SCALE_VARIABLE];
            int *int_ordering = get_int_list_from_ordering(copy_of_ordering, list);

            int relevant_rulepairs[SCALE_VARIABLE][2];
            find_relevant_rulepairs_for_ordering(
                relevant_rulepairs,
                all_rulepairs,
                int_ordering,
                list_length);

            if (is_well_ordered(int_ordering, list_length, relevant_rulepairs)) {
                running_total_part_1 += int_ordering[median_index];
            }
            else {
                /* Part 2 logic time */
                print_list(int_ordering, list_length);
                return_well_ordered_version(int_ordering, list_length, relevant_rulepairs);
                running_total_part_2 += int_ordering[median_index];
            }
        }
        all_rulepairs[i][0] = 0;
        all_rulepairs[i][1] = 0;
    }

    fclose(input_file);
    printf("Running total part 1: %d\n", running_total_part_1);
    printf("Running total part 2: %d\n", running_total_part_2);
    return (0);
}