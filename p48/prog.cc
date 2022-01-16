/*
The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef unsigned long long ull;

// result: A * B % MOD
ull modmult(ull a, ull b, ull mod)
{
    if (true || a == 0 || b < ULLONG_MAX / a)
        return (a * b) % mod; //No overflow
    ull sum = 0;
    while (b > 0) {
        if (b % 2 == 1)
            sum = (sum + a) % mod;
        a = (2 * a) % mod;
        b >>= 1;
    }
    return sum;
}

ull mod_exp(ull base, ull exponent, ull mod) {
    if (mod == 1) {
        return 0;
    }
    base = base % mod;
    ull result = 1;
    while (exponent > 0) {
        if (exponent % 2) {
            result = modmult(result, base, mod);
        }
        base = modmult(base, base, mod);
        exponent = exponent >> 1;
    }
    return result;
}

ull self_powers(int upto_power) {
    ull sum = 0;
    const ull mod = 10000000000U;
    for (int i=1; i<=upto_power; i++) {
        sum += mod_exp(i, i, mod);
        sum %= mod;
    }   
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./%s [upto]\n", argv[0]);
        return 1;
    }
    printf("BROKEN, DUE TO INTEGER OVERFLOW\n");
    printf("%llu\n", mod_exp(atoi(argv[1]), atoi(argv[1]), 10000000000));
    printf("%llu\n", self_powers(atoi(argv[1])));
    return 0;
}
