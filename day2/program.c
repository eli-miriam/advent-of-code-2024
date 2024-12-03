#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <utils.h>

#define LIST_LENGTH 1000
#define INPUT_FILE "input.txt"

bool list_is_safe(int *list, int list_length) {
    int i = 0;
    int intertwingled[list_length - 1];
    int list_sign;
    bool first = true;
    for (i = 0; i < list_length - 1; i++) {
        intertwingled[i] = list[i+ 1] - list[i];

        if (first) {
            list_sign = sign(intertwingled[i]);
            if (list_sign == 0) {
                return false;
            }
            first = !first;
        }
        else {
            if (list_sign != sign(intertwingled[i])) {
                return false;
            }
            if (intertwingled[i] == 0) {
                return false;
            }
        }
        
        if (abs(intertwingled[i]) > 3) {
            return false;
        }
    }
    return true;
}

bool dampened_list_is_safe(int *list, int list_length) {
    if (list_is_safe(list, list_length)) {
        return true;
    }

    int i = 0;
    int j = 0;
    int dampened_list[list_length - 1];
    for (i = 0; i < list_length; i++) {
        for (j = 0; j < list_length - 1; j++) {
            if ( j < i ) {
                dampened_list[j] = list[j];
            }
            else {
                dampened_list[j] = list[j+1];
            }
        }
        if (list_is_safe(dampened_list, list_length - 1)) {
            return true;
        }
    }
    return false;
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    char line[255];
    int is_safe[LIST_LENGTH];
    int running_total = 0;
    
    while (fgets(line, 255, input_file)) {
        /* We don't need to store these off -
         just deal with them and move on */
        line[strcspn(line, "\n")] =0;

        int i = 0;
        int list[100] = {0}; /* we assume non-zero input */

        char *token = strtok(line, " ");
        while (token != NULL) {
            list[i] = atoi(token);
            token = strtok(NULL, " ");
            i++;
        }

        if (dampened_list_is_safe(list, i)) {
            running_total++;
        }
    }
    fclose(input_file);
    
    printf("Running total: %d", running_total);
    return (0);
}