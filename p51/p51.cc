/*
By replacing the 1st digit of the 2-digit number *3, it turns out that six of the nine possible values:
 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit number 
is the first example having seven primes among the ten generated numbers, yielding the family:
 56003, 56113, 56333, 56443, 56663, 56773, and 56993. Consequently 56003, being the first member of this family,
 is the smallest prime with this property.

Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) 
with the same digit, is part of an eight prime value family.
*/


#include <stdio.h>
#include <assert.h>
#include "../common/cxx/sieve.hpp"

Sieve S;

struct unpacked {
    uint8_t digits[12]; //this contains either digits [0 to 9] (not '0' to '9') OR it contains '*' as a wildcard
    int digits_count;
};

//unpack a number into base10 digits
unpacked unpack(long n) {
    unpacked u = {0};
    while (n) {
        u.digits[u.digits_count++] = n % 10;
        n /= 10;
    }
    return u;
}

//compares two numbers and puts wildcard '*' where they differ
// cmp(101, 102)   =>  10*
// cmp(4241, 5243) => *24*
// the numbers must have the same digits_count
unpacked compare(unpacked a, unpacked b) {
    assert(a.digits_count == b.digits_count);
    unpacked r = {0};
    for (int i=0; i<a.digits_count; i++) {
        r.digits[i] = a.digits[i] == b.digits[i] ? a.digits[i] : '*';
    }
    r.digits_count = a.digits_count;
    return r;
}

long repack(unpacked p, uint8_t fill) {
    long sum = 0;
    long base = 1;
    for (int i=0; i<p.digits_count; i++) {
        uint8_t digit = p.digits[i];
        if (digit == '*') {
            digit = fill;
        }
        sum += digit * base;
        base *= 10;
    }
    return sum;
}

int prime_cmp_family_count(unpacked p) {
    int family_count = 0;
    for (int i=0; i<10; i++) {
        if (i == 0 && p.digits[p.digits_count - 1] == '*') continue; //Doesn't count
        long num = repack(p, i);
        family_count += S.isPrime(num);
    }
    return family_count;
}

void prime_cmp_family_print(unpacked p) {
    for (int i=0; i<10; i++) {
        if (i == 0 && p.digits[p.digits_count - 1] == '*') continue; //Doesn't count
        long num = repack(p, i);
        if (S.isPrime(num)) {
            printf("|-> %ld\n", num);
        }
    }
}

std::string unpacked_repr(unpacked p) {
    std::string s = "";
    for (int i=p.digits_count-1; i>=0; i--) {
        if (p.digits[i] == '*')
            s += p.digits[i];
        else
            s += p.digits[i] + '0'; //FIXME
    }
    return s;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error, expected an argument for the number of primes in family\n");
        return 1;
    }
    int requested_family_count = std::max(atoi(argv[1]), 1);
    long upto = 1000000;
    while (true) {
        S.resieve(upto);
        std::vector<long> primes = S.getPrimes();
        for (int i=0; i<primes.size(); i++) {
            unpacked p1 = unpack(primes[i]);
            for (int j=i+1; j<primes.size(); j++) {
                unpacked p2 = unpack(primes[j]);
                if (p2.digits_count > p1.digits_count)
                    break;
                else if (p2.digits_count != p1.digits_count)
                    continue;
                unpacked cmp = compare(p1, p2);
                int family_count = prime_cmp_family_count(cmp);
                if (family_count == requested_family_count) {
                    printf("%s\n", unpacked_repr(cmp).c_str());
                    prime_cmp_family_print(cmp);
                    goto end;
                }
            }
        }
        upto *= 10;
    }
end:
    return 0;
    
}
