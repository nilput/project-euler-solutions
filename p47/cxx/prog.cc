#include <stdio.h>
#include <memory>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include "../../common/cxx/sieve.hpp"


int firstOfConsecutiveIntsWithNFactors(int nFactors) {
    static Sieve s;
    int max = 1024;
    while (true) {
        s.resieve(max);
        uint8_t *data = s.data();
        for (int i=2; i<max; i++) {
            bool match = true;
            for (int j=0; j<nFactors; j++) {
                if (data[i+j] != nFactors) {
                    match = false;
                    break;
                }
            }
            if (match) {
                return i;
            }
        }
        max *= 2;
        s.resieve(max);
    }
    //std::cout << s.toString() << std::endl;
    return -1;
}

int main(void) {
    for (int i=2; i<=4; i++) {
        std::cout << "FOCIWNF(" << i << "): " << firstOfConsecutiveIntsWithNFactors(i) << std::endl;
    }
}
