#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define SCALE_VARIABLE 150

bool is_arrow(char ch) {
    if ((ch == '^') ||
        (ch == '>') ||
        (ch == 'v') ||
        (ch == '<')) {
            return true;
        }
    return false;
 }

 char turn_arrow(char arrow_type) {
    if (arrow_type == '^') {
        return '>';
    }
    if (arrow_type == '>') {
        return'v';
    }
    if (arrow_type == 'v') {
        return '<';
    }
    if (arrow_type == '<') {
        return '^';
    }
 }

bool out_of_bounds(
    int position[2], 
    char grid[SCALE_VARIABLE][SCALE_VARIABLE]
) {
    if ((position[0] < 0) || (position[1] < 0)) {
        return true;
    }
    if (grid[position[0]][position[1]] == '\0') {
        return true;
    }
    return false;
}

void get_proposed_position(
    char arrow_type,
    int arrow_position[2],
    int proposed_position[2]
){
    if (arrow_type == '^') {
        proposed_position[0] = arrow_position[0] - 1;
        proposed_position[1] = arrow_position[1];
    }
    if (arrow_type == '>') {
        proposed_position[0] = arrow_position[0];
        proposed_position[1] = arrow_position[1] + 1;
    }
    if (arrow_type == 'v') {
        proposed_position[0] = arrow_position[0] + 1;
        proposed_position[1] = arrow_position[1];
    }
    if (arrow_type == '<') {
        proposed_position[0] = arrow_position[0];
        proposed_position[1] = arrow_position[1] - 1;
    }
}

int follow_arrow_around_grid(
    int arrow_position[2], 
    char grid[SCALE_VARIABLE][SCALE_VARIABLE]
) {

    int total_positions = 1;
    char arrow_type = grid[arrow_position[0]][arrow_position[1]];

    while (true) {
        int proposed_position[2] = {0};

        get_proposed_position(arrow_type, arrow_position, proposed_position);

        if (out_of_bounds(proposed_position, grid)) {
            return total_positions;
        }

        char character_under_test = grid[proposed_position[0]][proposed_position[1]];

        if (character_under_test == '#') {
            arrow_type = turn_arrow(arrow_type);
            /* do not update arrow position */
        }
        else if (character_under_test == arrow_type) {
            /* we've found ourselves where we've been before. Infinite loop */
            return 0;
        }
        else {
            if (!is_arrow(character_under_test)) {
                grid[proposed_position[0]][proposed_position[1]] = arrow_type;
                total_positions++;
            }
            arrow_position[0] = proposed_position[0];
            arrow_position[1] = proposed_position[1];
        }
    }
    return 0;
}

void make_deep_copy_of_grid(
    char initial_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    char target_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int height,
    int width
) {
    int row = 0;
    int column = 0;
    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++) {
            target_grid[row][column] = initial_grid[row][column];
        }
    }
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    char grid[SCALE_VARIABLE][SCALE_VARIABLE] = {0};

    int row = 0;
    int column = 0;
    char line[SCALE_VARIABLE] = {0};

    int arrow_position[2] = {0};

    while (fgets(line, SCALE_VARIABLE, input_file)) {
        line[strcspn(line, "\n")] = '\0';
        for (column = 0; column < strlen(line); column++) {
            grid[row][column] = line[column];
            if (is_arrow(line[column])) {
                arrow_position[0] = row;
                arrow_position[1] = column;
            }
        }
        row++;
    }

    int grid_height = row;
    int grid_width = strlen(line);


    int initial_arrow_position[2];
    initial_arrow_position[0] = arrow_position[0];
    initial_arrow_position[1] = arrow_position[1];

    char fresh_grid[SCALE_VARIABLE][SCALE_VARIABLE] = {0};
    make_deep_copy_of_grid(grid, fresh_grid, grid_height, grid_width);

    int total_positions = follow_arrow_around_grid(
        arrow_position, 
        grid
    );
    if (total_positions == 0) {
        printf("infinite loop\n");
    }
    else {
        printf("Total positions: %d\n", total_positions);
    }

    row = 0;
    column = 0;
    char temp_char = 0;
    int result_from_walk = 0;
    int total_blocking_positions = 0;

    for (row = 0; row < grid_height; row++) {
        for (column = 0; column < grid_width; column++) {
            if (is_arrow(grid[row][column])) {
                if ((row == initial_arrow_position[0]) &&
                    (column == initial_arrow_position[1])){
                        /* skip; this is the guard's start position */
                        do_nothing();
                    }
                else {
                    /* make a new grid copy and slap a new '#' 
                    in there to see if we get an infiniloop. */
                    char temp_grid[SCALE_VARIABLE][SCALE_VARIABLE] = {0};
                    make_deep_copy_of_grid(fresh_grid, temp_grid, grid_height, grid_width);
                    temp_grid[row][column] = '#';

                    /* reset arrow position since it also gets mutated */
                    arrow_position[0] = initial_arrow_position[0];
                    arrow_position[1] = initial_arrow_position[1];

                    result_from_walk = follow_arrow_around_grid(
                        arrow_position, 
                        temp_grid
                    );
                    if (result_from_walk == 0) {
                        total_blocking_positions++;
                    }
                }
            }

        }
    }

    printf("Total blocking positions: %d\n", total_blocking_positions);
    fclose(input_file);
    return (0);
}