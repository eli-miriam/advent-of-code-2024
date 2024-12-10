#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define SCALE_VARIABLE 256

int build_directory_of_antennae(
    int antennae[SCALE_VARIABLE][2],
    char ch,
    char antenna_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int grid_height,
    int grid_width
) {
    int num_found = 0;
    int row = 0;
    for (row = 0; row < grid_height; row++) {
        int column = 0;
        for (column = 0; column < grid_width; column++) {
            if (antenna_grid[row][column] == ch) {
                antennae[num_found][0] = row;
                antennae[num_found][1] = column;
                num_found++;
            }
        }
    }
    return num_found;
}

int get_antinodes_from_pair_of_antennae(
    int node1[2],
    int node2[2],
    int grid_height,
    int grid_width,
    int antinodes[SCALE_VARIABLE][2],
    int previously_found
) {
    printf("Getting antinodes from pair of antennae\n");
    printf("Variables: grid height: %d, grid_width %d\n", grid_height, grid_width);
    int new_antinodes_found = 0;

    int diff[2];
    diff[0] = node1[0] - node2[0];
    diff[1] = node1[1] - node2[1];

    bool on_grid = true;
    int i = 0;

    printf("Finding antinodes for pair (%d, %d) and (%d, %d)\n",
    node1[0], node1[1], node2[0], node2[1]);

    /* work outwards from node1 */
    while (on_grid) {
        int row = node1[0] + i*diff[0];
        int column = node1[1] + i*diff[1];
        if ((row > grid_height) || 
            (column > grid_width) ||
            (row < 0) ||
            (column < 0)) {
            on_grid = false;
        }
        else {
            antinodes[previously_found + new_antinodes_found][0] = row;
            antinodes[previously_found + new_antinodes_found][1] = column;
            new_antinodes_found++;
        }
        i++;
    }

    i = 0;
    on_grid = true;
    /* work outwards from node2 */
    while (on_grid) {
        int row = node2[0] - i*diff[0];
        int column = node2[1] - i*diff[1];
        if ((row >= grid_height) || 
            (column >= grid_width) ||
            (row < 0) ||
            (column < 0)) {
            on_grid = false;
        }
        else {
            antinodes[previously_found + new_antinodes_found][0] = row;
            antinodes[previously_found + new_antinodes_found][1] = column;
            new_antinodes_found++;
        }
        i++;
    }
    return new_antinodes_found;
}

int get_antinodes_from_antennae(
    int antinodes[SCALE_VARIABLE][2],
    int antennae[SCALE_VARIABLE][2],
    int num_antennae,
    int grid_height,
    int grid_width
) {
    printf("Getting antinodes from antennae\n");
    int index = num_antennae - 1;
    int num_antinodes = 0;

    while (index >= 0) {
        int node[2];
        node[0] = antennae[index][0];
        node[1] = antennae[index][1];
        
        int sub_index = index - 1;
        while (sub_index >= 0) {
            int sub_node[2];
            sub_node[0] = antennae[sub_index][0];
            sub_node[1] = antennae[sub_index][1];

            int new_antinodes = get_antinodes_from_pair_of_antennae(
                node,
                sub_node,
                grid_height,
                grid_width,
                antinodes,
                num_antinodes
            );
            
            num_antinodes = num_antinodes + new_antinodes;
            sub_index--;
        }
        index--;
    }
    return num_antinodes;
}

int add_antinodes_to_antinode_grid(
    char antinode_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int antinodes[SCALE_VARIABLE][2],
    int num_antinodes,
    int grid_height,
    int grid_width
) {
    int i = 0;
    int num_antinodes_added = 0;
    for (i = 0; i < num_antinodes; i++) {
        if ((antinodes[i][0] < 0) ||
            (antinodes[i][1] < 0) ||
            (antinodes[i][0] >= grid_height) ||
            (antinodes[i][1] >= grid_width)) {
            printf(
                "Node (%d,%d) out of range\n",
                antinodes[i][0],
                antinodes[i][1]
            );
            do_nothing();
        }
        else if (antinode_grid[antinodes[i][0]][antinodes[i][1]] == '#') {
            do_nothing();
        }
        else {
            antinode_grid[antinodes[i][0]][antinodes[i][1]] = '#';
            num_antinodes_added++;
        }
    }
    return num_antinodes_added;
}


int populate_antinode_grid_for_character(
    char ch,
    char antinode_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    char antenna_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int grid_height,
    int grid_width
) {
    int antennae[SCALE_VARIABLE][2];
    int num_antennae = build_directory_of_antennae(
        antennae, 
        ch, 
        antenna_grid, 
        grid_height, 
        grid_width
    );

    if (num_antennae > 0) {
        printf("Found %d antennae of type %c\n", num_antennae, ch);
        int antinodes[SCALE_VARIABLE][2];
        int num_antinodes = get_antinodes_from_antennae(
            antinodes, 
            antennae, 
            num_antennae,
            grid_height,
            grid_width
        );
        printf("Found %d antinodes\n", num_antinodes);

        int num_antinodes_added = add_antinodes_to_antinode_grid(
            antinode_grid,
            antinodes,
            num_antinodes,
            grid_height,
            grid_width
        );
        printf("Added %d antinodes\n\n", num_antinodes_added);

        return num_antinodes_added;
    }
    else {
        return 0;
    }

}



int populate_antinode_grid(
    char antinode_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    char antenna_grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int grid_height,
    int grid_width
) {
    char *antenna_type_list = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789\0";
    int i = 0;
    int running_total = 0;
    while (antenna_type_list[i] != '\0') {
        int num_antinodes_added = populate_antinode_grid_for_character(
            antenna_type_list[i],
            antinode_grid,
            antenna_grid,
            grid_height,
            grid_width
        );
        running_total += num_antinodes_added;
        i++;
    }
    return running_total;
}


int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");

    char antenna_grid[SCALE_VARIABLE][SCALE_VARIABLE];
    char antinode_grid[SCALE_VARIABLE][SCALE_VARIABLE];

    int row = 0;
    int grid_width = 0;
    char line[SCALE_VARIABLE];
    while (fgets(line, 255, input_file)) {
        line[strcspn(line, "\n")] =0;
        grid_width = strlen(line);
        int column = 0;
        for (column = 0; column < grid_width; column++) {
            antenna_grid[row][column] = line[column];
        }
        row++;
    }
    int grid_height = row;

    printf("Antenna grid with width %d and height %d\n", grid_width, grid_height);
    int total = populate_antinode_grid(
        antinode_grid, 
        antenna_grid, 
        grid_height, 
        grid_width
    );

    printf("Total added: %d\n", total);
    
    fclose(input_file);
    
    return (0);
}