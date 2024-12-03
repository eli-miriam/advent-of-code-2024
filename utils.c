
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