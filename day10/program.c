#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define SCALE_VARIABLE 2048

int given_location_find_uplevel_neighbours(
    int location[2],
    char grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int grid_height,
    int grid_width,
    int neighbours[4][2]
) {
    char current_level = grid[location[0]][location[1]];
    char uplevel = current_level + 1; /* ASCII arithmetic FTW */

    int num_uplevel_neighbours = 0;
    if (location[0] > 0) {
        if (grid[location[0] - 1][location[1]] == uplevel) {
            neighbours[num_uplevel_neighbours][0] = location[0] - 1;
            neighbours[num_uplevel_neighbours][1] = location[1];
            num_uplevel_neighbours++;
        }
    }
    if (location[1] > 0) {
        if (grid[location[0]][location[1] - 1] == uplevel) {
            neighbours[num_uplevel_neighbours][0] = location[0];
            neighbours[num_uplevel_neighbours][1] = location[1] - 1;
            num_uplevel_neighbours++;
        }
    }
    if (location[0] < grid_height - 1) {
        if (grid[location[0] + 1][location[1]] == uplevel) {
            neighbours[num_uplevel_neighbours][0] = location[0] + 1;
            neighbours[num_uplevel_neighbours][1] = location[1];
            num_uplevel_neighbours++;
        }
    }
    if (location[1] < grid_width - 1) {
        if (grid[location[0]][location[1] + 1] == uplevel) {
            neighbours[num_uplevel_neighbours][0] = location[0];
            neighbours[num_uplevel_neighbours][1] = location[1] + 1;
            num_uplevel_neighbours++;
        }
    }
    return num_uplevel_neighbours;
}

int get_unique_coordinate_number(
    int list[SCALE_VARIABLE][2],
    int list_length
) {
    int set_length = 0;
    int i = 0;
    for (i = list_length - 1; i > 0; i--) {
        int j = 0;
        for (j = 0; j < i; j++) {
            if ((list[i][0] == list[j][0]) && (list[i][1] == list[j][1])) {
                /* dupe */
                list[j][0] = - 1;
                list[j][1] = - 1;
            }
        }
    }
    i = 0;
    for (i = 0; i < list_length; i++) {
        if (list[i][0] != -1) {
            set_length++;
        }
    }

    return set_length;
}

int given_0_find_9s(
    int zero_location[2],
    char grid[SCALE_VARIABLE][SCALE_VARIABLE],
    int grid_height,
    int grid_width
) {
    int total_nine_locations[SCALE_VARIABLE][2];
    int num_nines_so_far = 0;
    printf("searching from (%d, %d)\n", zero_location[0], zero_location[1]);

    int one_locations[4][2];
    int num_one_locations = given_location_find_uplevel_neighbours(
        zero_location,
        grid,
        grid_height,
        grid_width,
        one_locations
    );

    if (zero_location[0] == 0) {print_list_of_coordinates(one_locations, num_one_locations);}
    int ones = 0;
    for (ones = 0; ones < num_one_locations; ones++) {
        int two_locations[4][2];
        int num_two_locations = given_location_find_uplevel_neighbours(
            one_locations[ones],
            grid,
            grid_height,
            grid_width,
            two_locations
        );
        if (zero_location[0] == 0) {print_list_of_coordinates(two_locations, num_two_locations);}
    
        int twos = 0;
        for (twos = 0; twos < num_two_locations; twos++) {
            int three_locations[4][2];
            int num_three_locations = given_location_find_uplevel_neighbours(
                two_locations[twos],
                grid,
                grid_height,
                grid_width,
                three_locations
            );
            if (zero_location[0] == 0) {print_list_of_coordinates(three_locations, num_three_locations);}
    
            int threes = 0;
            for (threes = 0; threes < num_three_locations; threes++) {
                int four_locations[4][2];
                int num_four_locations = given_location_find_uplevel_neighbours(
                    three_locations[threes],
                    grid,
                    grid_height,
                    grid_width,
                    four_locations
                );
                if (zero_location[0] == 0) {print_list_of_coordinates(four_locations, num_four_locations);}
    
                int fours = 0;
                for (fours = 0; fours < num_four_locations; fours++) {
                    int five_locations[4][2];
                    int num_five_locations = given_location_find_uplevel_neighbours(
                        four_locations[fours],
                        grid,
                        grid_height,
                        grid_width,
                        five_locations
                    );
                    if (zero_location[0] == 0) {print_list_of_coordinates(five_locations, num_five_locations);}
    
                    int fives = 0;
                    for (fives = 0; fives < num_five_locations; fives++) {
                        int six_locations[4][2];
                        int num_six_locations = given_location_find_uplevel_neighbours(
                            five_locations[fives],
                            grid,
                            grid_height,
                            grid_width,
                            six_locations
                        );
                        int sixes = 0;
                        for (sixes = 0; sixes < num_six_locations; sixes++) {
                            int seven_locations[4][2];
                            int num_seven_locations = given_location_find_uplevel_neighbours(
                                six_locations[sixes],
                                grid,
                                grid_height,
                                grid_width,
                                seven_locations
                            );
                            int sevens = 0;
                            for (sevens = 0; sevens < num_seven_locations; sevens++) {
                                int eight_locations[4][2];
                                int num_eight_locations = given_location_find_uplevel_neighbours(
                                    seven_locations[sevens],
                                    grid,
                                    grid_height,
                                    grid_width,
                                    eight_locations
                                );
                                int eights = 0;
                                for (eights = 0; eights < num_eight_locations; eights++) {
                                    int nine_locations[4][2];
                                    int num_nine_locations = given_location_find_uplevel_neighbours(
                                        eight_locations[eights],
                                        grid,
                                        grid_height,
                                        grid_width,
                                        nine_locations
                                    );
                                    int nines = 0;
                                    for (nines = 0; nines < num_nine_locations; nines++) {
                                        total_nine_locations[num_nines_so_far][0] = nine_locations[nines][0];
                                        total_nine_locations[num_nines_so_far][1] = nine_locations[nines][1];
                                        num_nines_so_far++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    int num_unique_nines = get_unique_coordinate_number(
        total_nine_locations,
        num_nines_so_far
    );
    if (zero_location[0] == 0) {
    printf(
        "Found %d nines from zero at (%d, %d); %d before reducing\n", 
        num_unique_nines,
        zero_location[0], 
        zero_location[1],
        num_nines_so_far
    );}
    return num_nines_so_far;
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    int i = 0;

    int grid_width = 0;
    int grid_height = 0;
    char grid[SCALE_VARIABLE][SCALE_VARIABLE];
    int zero_locations[SCALE_VARIABLE][2];
    int num_zeroes = 0;

    char line[SCALE_VARIABLE];
    while (fgets(line, 255, input_file)) {
        line[strcspn(line, "\n")] = 0;
        grid_width = strlen(line);

        for (i = 0; i < grid_width; i++) {
            grid[grid_height][i] = line[i];
            if (line[i] == '0') {
                zero_locations[num_zeroes][0] = grid_height;
                zero_locations[num_zeroes][1] = i;
                num_zeroes++;
            }
        }
        grid_height++;
    }

    printf("Zeroes found at following locations:\n");
    print_list_of_coordinates(zero_locations, num_zeroes);
    printf("\n");

    int running_total = 0;

    i = 0;
    for (i = 0; i < num_zeroes; i++) {
        int zero_location[2];
        zero_location[0] = zero_locations[i][0];
        zero_location[1] = zero_locations[i][1];
        running_total += given_0_find_9s(zero_location, grid, grid_height, grid_width);
    }
    printf("Running total: %d\n", running_total);

    fclose(input_file);
    
    return (0);
}