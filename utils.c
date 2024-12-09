
#include <stdio.h>
#include <string.h>

int compare(const void* a, const void* b) {
   return (*(int*)a - *(int*)b);
}

int sign(int number) {
   if (number < 0) {
      return - 1;
   }
   else if (number > 0) {
      return 1;
   }
   else {
      return 0;
   }
}

int do_nothing() {
   return 0;
}

void print_array_of_long_longs(long long array[65535], int length) {
   int i = 0;
   for (i = 0; i < length; i++) {
      printf(" %lld", array[i]);
   }
   printf("\n");
}