#include <stdio.h>
#include <string.h>


int main(void) {
    FILE *input_file = fopen("test.txt", "r");
    char line[32];
    int left_list[6];
    int right_list[6];
    while (fgets(line, 32, input_file)) {
        line[strcspn(line, "\n")] =0;
        printf("%s\n", line);
    }

    fclose(input_file);
    
    return (0);
}