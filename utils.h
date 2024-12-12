#ifndef MYUTILS_H
#define MYUTILS_H

#include <stdio.h>

int compare(const void* a, const void* b);
int sign(int number);
int do_nothing();
void print_array_of_long_longs(long long array[65535], int length);
void print_array_of_ints(int array[65535], int length);
void print_list_of_coordinates(int coords[65535][2], int length);

#endif