#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_FILE "test.txt"

bool char_is_valid(char ch) {
    if (
        isdigit(ch) ||
        (ch == ',') ||
        (ch == ')') ||
        (ch == ' ')
    ) {
        return true;
    }
    return false;
}

bool is_string_valid(char *string) {
    bool comma_found = false;
    bool last_char_was_an_int = false;

    int i = 0;

    printf("string: %s ,", string);

    while (string[i] != '\0') {
        char ch = string[i];
        i++;
        if (!char_is_valid(ch)) {
            return false;
        }
        if (ch == ')') {
            if (!comma_found || !last_char_was_an_int) {
                return false;
            }
            else {
                return true;
            }
        }
        if (ch == ',') {
            if (comma_found || !last_char_was_an_int) {
                return false;
            }
            comma_found = true;
        }
        if (isdigit(ch)) {
            last_char_was_an_int = true;
        }
    }
    return false;
}

int result_from_str(char *string) {
    bool valid = is_string_valid(string);

    printf(" valid: %d\n", valid);
    
    return 0;
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    char input[65535];
    int running_total = 0;

    fread(input, sizeof(char), 65535, input_file);

    char *token = strtok(input, "mul(");
    while (token != NULL) {
        /* assess token for correctness */
        result_from_str(token);
        token = strtok(NULL, "mul(");
    }

    fclose(input_file);
    
}