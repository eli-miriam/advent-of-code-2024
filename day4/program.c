#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define GRID_SIZE 255

/* be careful about off-by-ones from subtracting i,j from GRID_SIZE */

int given_x_check_cardinals(char grid[GRID_SIZE][GRID_SIZE], int i, int j) {
    int xmases_found = 0;
    /* check up */
    if (i >= 3) {
        if (
            (grid[i-1][j] == 'M') &&
            (grid[i-2][j] == 'A') &&
            (grid[i-3][j] == 'S')
        ) {
            xmases_found++;
        }
    }
    /* check down */
    if (i < GRID_SIZE - 3) {
        if (
            (grid[i+1][j] == 'M') &&
            (grid[i+2][j] == 'A') &&
            (grid[i+3][j] == 'S')
        ) {
            xmases_found++;
        }
    }
    /* check right */
    if (j < GRID_SIZE - 3) {
        if (
            (grid[i][j+1] == 'M') &&
            (grid[i][j+2] == 'A') &&
            (grid[i][j+3] == 'S')
        ) {
            xmases_found++;
        }
    }
    /* check left */
    if (j >= 3) {
        if (
            (grid[i][j-1] == 'M') &&
            (grid[i][j-2] == 'A') &&
            (grid[i][j-3] == 'S')
        ) {
            xmases_found++;
        }
    }
    return xmases_found;
}

int given_x_check_diagonals(char grid[GRID_SIZE][GRID_SIZE], int i, int j) {
    int xmases_found = 0;
    /* check up-right */
    if ((i >= 3) && (j < GRID_SIZE - 3)) {
        if (
            (grid[i-1][j+1] == 'M') &&
            (grid[i-2][j+2] == 'A') &&
            (grid[i-3][j+3] == 'S')
        ) {
            xmases_found++;
        }
    }
    /* check up-left */
    if ((i >= 3) && (j >= 3)) {
        if (
            (grid[i-1][j-1] == 'M') &&
            (grid[i-2][j-2] == 'A') &&
            (grid[i-3][j-3] == 'S')
        ) {
            xmases_found++;
        }
    }
    /* check down-right */
    if ((i < GRID_SIZE - 3) && (j < GRID_SIZE - 3)) {
        if (
            (grid[i+1][j+1] == 'M') &&
            (grid[i+2][j+2] == 'A') &&
            (grid[i+3][j+3] == 'S')
        ) {
            xmases_found++;
        }
    }
    /* check down-left */
    if ((i < GRID_SIZE - 3) && (j >= 3)) {
        if (
            (grid[i+1][j-1] == 'M') &&
            (grid[i+2][j-2] == 'A') &&
            (grid[i+3][j-3] == 'S')
        ) {
            xmases_found++;
        }
    }
    return xmases_found;
}


int given_grid_find_xmases(char grid[GRID_SIZE][GRID_SIZE]) {
    int i = 0;
    int j = 0;
    int xmases_found = 0;

    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 'X') {
                xmases_found += given_x_check_cardinals(grid, i, j);
                xmases_found += given_x_check_diagonals(grid, i, j);
            }
        }
    }
    printf("xmases found: %d\n", xmases_found);
    return 0;
}


int given_a_check_corners(char grid[GRID_SIZE][GRID_SIZE], int i, int j) {
    bool first_diagonal_found = false;
    if (
        (i == 0) ||
        (i == GRID_SIZE - 1) ||
        (j == 0) ||
        (j == GRID_SIZE - 1)
    ) {
        return 0;
    }
    /*check up-right <-> down-left diagonal*/
    if (grid[i-1][j+1] == 'M') {
        if (grid[i+1][j-1] == 'S') {
            first_diagonal_found = true;
        }
    }
    if (grid[i-1][j+1] == 'S') {
        if (grid[i+1][j-1] == 'M') {
            first_diagonal_found = true;
        }
    }
    if (!first_diagonal_found) {
        return 0;
    }
    /*check up-left <-> down-right diagonal*/
    if (grid[i+1][j+1] == 'M') {
        if (grid[i-1][j-1] == 'S') {
            return 1;
        }
    }
    if (grid[i+1][j+1] == 'S') {
        if (grid[i-1][j-1] == 'M') {
            return 1;
        }
    }
    return 0;
}


int given_grid_find_x_mases(char grid[GRID_SIZE][GRID_SIZE]) {
    int i = 0;
    int j = 0;
    int x_mases_found = 0;
    for (i = 0; i < GRID_SIZE; i++) {
        for (j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == 'A') {
                x_mases_found += given_a_check_corners(grid, i, j);
            }
        }
    }
    printf("x_mases found: %d\n", x_mases_found);
    return 0;
}


int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    char grid[GRID_SIZE][GRID_SIZE];
    int i = 0;

    /* Extract the file into the array */
    while (fgets(grid[i], GRID_SIZE, input_file)) {
        grid[i][strcspn(grid[i], "\n")] = 0;
        printf("%s\n", grid[i]);
        i++;
    }
    fclose(input_file);

    /* part 1 */
    given_grid_find_xmases(grid);

    /* part 2 */
    given_grid_find_x_mases(grid);
    return (0);
}