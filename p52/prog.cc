/*
It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.
*/
#include <stdio.h>
#include <signal.h>
#define NDIGITS 9

bool same_digits(int a, int b) {
    int digit_hash_a[10] = {0};
    int digit_hash_b[10] = {0};
    for (int i=0; i<NDIGITS && a; i++) {
        int digit_a = a % 10;
        digit_hash_a[digit_a]++;
        a /= 10;
    }
    for (int i=0; i<NDIGITS && b; i++) {
        int digit_b = b % 10;
        digit_hash_b[digit_b]++;
        b /= 10;
    }
    bool match = true;
    for (int i=0; i<NDIGITS; i++) {
        if (digit_hash_a[i] != digit_hash_b[i]) {
            match = false;
            break;
        }
    }
    return match;
}

bool full_check(int a) {
    return same_digits(a, a * 2) &&
           same_digits(a, a * 6) &&
           same_digits(a, a * 5) &&
           same_digits(a, a * 4) &&
           same_digits(a, a * 3)
                                    ;
}

int main(void) {
    int digits_1[NDIGITS + 1] = {0};
    int digits_3[NDIGITS + 1] = {0};
    int digits_1_int = 0;
    while (true) {
        int digits_hash[10] = {0};
        digits_1_int++;
        digits_1[0]++;
        digits_3[0] += 3;
        for (int i=0; i<NDIGITS; i++) {
            int added_1 = digits_1[i];
            if (added_1 >= 10) {
                added_1 -= 10;
                digits_1[i+1]++;
            }
            digits_1[i] = added_1;
            digits_hash[digits_1[i]]++;

            int added_3 = digits_3[i];
            if (added_3 >= 10) {
                added_3 -= 10;
                digits_3[i+1]++;
            }
            digits_3[i] = added_3;
            digits_hash[digits_3[i]]++;
        }
        bool match = true;
        for (int i=0; i<10; i++) {
            if (digits_hash[i] % 2 != 0) { 
                match = false;
                break;
            }
        }
        if (match && full_check(digits_1_int)) {
            printf("%d\n", digits_1_int);
            break;
        }
    }
}
