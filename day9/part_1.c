#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <utils.h>

#define INPUT_FILE "input.txt"
#define SCALE_VARIABLE 600000

int decompress_disk_map(
    char *disk_map,
    int file_storage[SCALE_VARIABLE]
) {
    int disk_map_index = 0;
    int file_storage_index = 0;
    int file_id = 0;
    int paint = - 1;
    bool is_file = true;

    while(disk_map[disk_map_index] != '\0') {
        int block_size = disk_map[disk_map_index] - '0';
        if (is_file) {
            paint = file_id;
            file_id++;
        }
        else {
            paint = -1;
        }

        int i = 0;
        for (i = 0; i < block_size; i++) {
            file_storage[file_storage_index + i] = paint;
        }

        file_storage_index += block_size;
        is_file = !is_file;
        disk_map_index++;
    }
    printf("Highest file ID found: %d\n", file_id - 1);
    return file_storage_index;
}


int reorganise_file_storage(
    int file_storage[SCALE_VARIABLE],
    int file_storage_length
) {
    int next_index_to_check_for_space = 0;

    while (next_index_to_check_for_space < file_storage_length - 1) {
        if (file_storage[file_storage_length - 1] != -1) {
            /* we have some memory to move */
            int file_id = file_storage[file_storage_length - 1];
            bool moved = false;
            while (!moved) {
                if (file_storage[next_index_to_check_for_space] == - 1) {
                    file_storage[next_index_to_check_for_space] = file_id;
                    moved = true;
                }
                next_index_to_check_for_space++;
            }
        }
        file_storage_length--;
    }
    file_storage_length++;
    printf("Length of reorganised storage: %d\n", file_storage_length);
    return file_storage_length;
}

long long get_checksum_from_storage(
    int file_storage[SCALE_VARIABLE], 
    int storage_length
) {
    long long checksum = 0;
    int i = 0;
    for (i = 0; i < storage_length; i++) {
        long diff = file_storage[i] * i;
        printf("multiplying file ID %d by index %d\n", file_storage[i], i);
        checksum += diff;
    }
    return checksum;
}

int main(void) {
    FILE *input_file = fopen(INPUT_FILE, "r");
    int i = 0;
    char line[SCALE_VARIABLE];
    int file_storage[SCALE_VARIABLE];
    int storage_length = 0;
    while (fgets(line, SCALE_VARIABLE, input_file)) {
        line[strcspn(line, "\n")] =0;
        storage_length = decompress_disk_map(line, file_storage);
        printf("Storage length: %d\n", storage_length);
    }
    print_array_of_ints(file_storage, storage_length);
    storage_length = reorganise_file_storage(file_storage, storage_length);
    print_array_of_ints(file_storage, storage_length);

    long long checksum = get_checksum_from_storage(file_storage, storage_length);
    printf("Checksum: %lld\n", checksum);
    fclose(input_file);
    
    return (0);
}