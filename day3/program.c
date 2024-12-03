#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INPUT_FILE "input.txt"

bool char_is_valid(char ch) {
    if (
        isdigit(ch) ||
        (ch == ',') ||
        (ch == '(') ||
        (ch == ')')
    ) {
        return true;
    }
    return false;
}

bool is_string_valid(char *string) {

    bool open_bracket_found = false;
    bool comma_found = false;
    bool last_char_was_an_int = false;
    bool valid = false;

    int i = 2;

    if (
        (string[0] != 'u') ||
        (string[1] != 'l') ||
        (string[2] != '(')
        ) {
        return false;
    }

    while (string[i] != '\0') {
        char ch = string[i];
        i++;
        if (!char_is_valid(ch)) {
            return false;
        }
        if (ch == '(') {
            if (open_bracket_found) {
                return false;
            }
            open_bracket_found = true;
        }
        if (ch == ')') {
            if (!comma_found || !last_char_was_an_int || !open_bracket_found) {
                return false;
            }
            else {
                return true;
            }
        }
        if (ch == ',') {
            if (comma_found || !last_char_was_an_int || !open_bracket_found) {
                return false;
            }
            comma_found = true;
        }
        if (isdigit(ch)) {
            if (!open_bracket_found) {
                return false;
            }
            last_char_was_an_int = true;
        }
    }

    return false;
}

int result_from_str(char *string) {
    if (is_string_valid(string)){
        char numstr1[10];
        char numstr2[10];
        bool comma_found = false;

        int i = 0;
        int j = 0;
        int k = 0;
        while (string[i] != ')') {
            if (string[i] == ',') {
                comma_found = true;
            }
            if (isdigit(string[i])) {
                if (!comma_found) {
                    numstr1[j] = string[i];
                    j++;
                }
                else {
                    numstr2[k] = string[i];
                    k++;
                }
            }
            i++;
        }
        numstr1[j] = '\0';
        numstr2[k] = '\0';
        return atoi(numstr1) * atoi(numstr2);
    }
    else {
        return 0;
    }
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    char input[65535];
    char token[8191];
    int running_total = 0;

    fread(input, sizeof(char), 65535, input_file);

    int input_index = 0;
    int token_index = 0;
    bool enabled = true;

    while (input[input_index] != '\0') {
        while (input[input_index] != 'm') {
            /* Check for enablement commands */
            if (input[input_index] == 'd') {
                /* We can treat this as ending our current token,
                since 'd' is never a valid component of a mul command.
                We don't reset the token index until another 'm'
                has been found, though. */

                token[token_index] = '\0';
                int num = result_from_str(token);
                if (enabled) {
                    running_total = running_total + num;
                }
                token[token_index] = input[input_index];

                if ((input[input_index + 1] == 'o') &&
                    (input[input_index + 2] == 'n') &&
                    (input[input_index + 3] == '\'') &&
                    (input[input_index + 4] == 't') &&
                    (input[input_index + 5] == '(') &&
                    (input[input_index + 6] == ')')) {
                        enabled = false;
                        token_index = 0;
                }
                if ((input[input_index + 1] == 'o') &&
                    (input[input_index + 2] == '(') &&
                    (input[input_index + 3] == ')')) {
                        enabled = true;
                        token_index = 0;
                }
                input_index++;
            }
            else {
                /* assess token for correctness */
                token[token_index] = input[input_index];
                token_index++;
                input_index++;
            }
        }
        /* if we're here, it's because a new 'm' was found.*/
        token[token_index] = '\0';
        int num = result_from_str(token);
        if (enabled) {
            running_total = running_total + num;
        }
        token_index = 0;
        input_index++;
    }
    printf("Running total: %d\n", running_total);

    fclose(input_file);
    
}