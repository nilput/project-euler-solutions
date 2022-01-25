#include <stdio.h>
#include <memory>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

class Sieve {
public:
    Sieve(): max(0), buckets() {
    }

    void resieve(long new_max) {
        if (new_max < max || new_max < 2) {
            return;
        }
        buckets.resize(new_max);
        buckets[0] = buckets[1] = 1;
        for (long i=2; i<new_max; i++) {
            if (buckets[i] != 0) {
                continue;
            }
            long product = i * 2;
            while (product < new_max) {
                buckets[product]++;
                product += i;
            }
        }
        max = new_max;
    }

    std::vector<long> getPrimes() {
        std::vector<long> r;
        for (long i=0; i<max; i++) {
            if (!buckets[i]) r.push_back(i);
        }
        return r;
    }

    uint8_t *data() {
        return buckets.data();
    }

    size_t length() {
        return max;
    }

    bool isPrime(long n) {
        if (n >= max) {
            long m = max;
            while (m <= n) {
                m *= 2;
            }
            resieve(m);
        }
        return buckets[n] == 0;
    }

    std::string toString() {
        std::stringstream ss;
        for (int i=0; i<max; i++) {
            ss << i << ": " << (int)buckets[i] << std::endl;
        }
        return ss.str();
    }

private:
    long max;
    std::vector<uint8_t> buckets; //stores factors count
};
