#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "test.txt"
#define SCALE_VARIABLE 255


int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    int i = 0;
    char line[SCALE_VARIABLE];
    while (fgets(line, 255, input_file)) {
        line[strcspn(line, "\n")] =0;
        printf("%s\n", line);
    }

    fclose(input_file);
    
    return (0);
}