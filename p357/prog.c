/*
Consider the divisors of 30: 1,2,3,5,6,10,15,30.
It can be seen that for every divisor d of 30, d+30/d is prime.

Find the sum of all positive integers n not exceeding 100 000 000
such that for every divisor d of n, d+n/d is prime.
*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t numbers[100000000 + 1] = {0};
const int numbers_len = sizeof numbers / sizeof numbers[0];
#define IS_NOT_PRIME    1
#define IS_NOT_MATCHING 2

static bool is_prime(uint8_t value) {
    return !(value & IS_NOT_PRIME);
}
static bool is_matching(uint8_t value) {
    return !(value & IS_NOT_MATCHING);
}

int main(void) {
    numbers[0] = numbers[1] = IS_NOT_PRIME;
    for (int i=2; i<numbers_len; i++) {
        if (!is_prime(numbers[i]))
            continue;
        for (int j=2; j<numbers_len; j++) {
            int product = i * j;
            if (product >= numbers_len) {
                break;
            }
            numbers[product] |= IS_NOT_PRIME;
        }
    }
    for (int i=1; i<numbers_len; i++) {
        for (int j=1; j<numbers_len; j++) {
            // a = d+n/d
            // where:
            //  d : i
            //  product: n
            // a = i + (product / i)
            // a = i + j
            int product = i * j;
            int a = i + j;
            if (product >= numbers_len || 
                a       >= numbers_len   ) 
            {
                break;
            }
            if (!is_prime(numbers[a])) {
                numbers[product] |= IS_NOT_MATCHING;
            }
        }
    }
    long sum = 0;
    for (int i=1; i<numbers_len; i++) {
        if (is_matching(numbers[i])) {
            sum += i;
        }
    }
    printf("Sum: %ld\n", sum);
}
