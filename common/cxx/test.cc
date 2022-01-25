#include "sieve.hpp"
#include <stdlib.h>
#include <assert.h>

#define UPTO 1000
int main(void) {
    srand(0);
    Sieve s1;
    s1.resieve(UPTO);
    for (int i=0; i<42; i++) {
        Sieve s2;
        int ntries = 0;
        if (i == 0) ntries = 0;
        else if (i == 1) ntries = UPTO - 1;
        else ntries = abs(rand()) % UPTO;
        s2.resieve(ntries);
        s2.resieve(UPTO);
        for (int j=0; j<s2.length(); j++) {
            assert(s2.data()[j] == s1.data()[j]);
        }
    }
}
