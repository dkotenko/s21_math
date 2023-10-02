#include <stdio.h>
#include "s21_math.h"
#include "math.h"

int main(){

    printf("atan TESTS!!!\n\n Original: %d\n ", atanf(2));
    printf("S21_test: %d\n ", s21_atan_test(2));
    printf("s21:      %d\n", s21_atan(2));
    //printf("TESTS!!!\n\n Original: %ld.\n S21: %ld\n\n\n", sin(-3), s21_sin_test(-3));
    //printf("TESTS!!!\n\n Original: %ld.\n S21: %ld\n\n\n", s21_sin(-3), s21_sin(-3));

    return 0;
}

//  gcc main.c s21_math.c -o math_test 