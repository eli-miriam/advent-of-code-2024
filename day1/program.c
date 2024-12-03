#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

int how_many_times(int num, int* list, int list_length) {
    int times = 0;
    int i = 0;
    for (i = 0; i < list_length; i++) {
        if (list[i] == num) {
            times++;
        }
    }
    return times;
}

int main(void) {
    FILE *input_file = fopen("input.txt", "r");
    int list_length = 1000;
    char line[32];
    int left_list[list_length];
    int right_list[list_length];
    int i = 0;
    bool is_left_list = true;

    /* Extract the unsorted lists */
    while (fgets(line, 32, input_file)) {
        line[strcspn(line, "\n")] =0;

        char *token = strtok(line, " ");
        while (token != NULL) {
            if (is_left_list) {
                left_list[i] = atoi(token);
            }
            else {
                right_list[i] = atoi(token);
            }
            is_left_list = !is_left_list;
            token = strtok(NULL, " ");

        }
        i++;
    }
    fclose(input_file);

    /* Part 1 */

    /* Sort the lists */
    qsort(left_list, list_length, sizeof(int), compare);
    qsort(right_list, list_length, sizeof(int), compare);

    /* Find the diffs and total distance */
    int running_total = 0;
    int diff = 0;

    for (i = 0; i < list_length; i++) {
        diff = abs(left_list[i] - right_list[i]);
        running_total = running_total + diff;
    }
    printf("the distance between the lists is %d\n", running_total);

    /* Part 2 */

    /* Reset loop variables for reuse */
    running_total = 0;
    diff = 0;

    int occurrences = 0;

    /* Find distance */
    for (i = 0; i < list_length; i++) {
        occurrences = how_many_times(left_list[i], right_list, list_length);
        diff = occurrences * left_list[i];
        running_total = running_total + diff;
    }

    printf("the similarity score between the lists is %d\n", running_total);

    return (0);
}