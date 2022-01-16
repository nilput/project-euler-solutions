/*
The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2² × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?
*/
package main
import "fmt"

func factorize(n int) []int {
    factors := []int{}
    if n % 2 == 0 {
        factors = append(factors, 2);
        for (n % 2 == 0) {
            n /= 2;
        }
    }
    for p := 3; p <= n; p+=2 {
        if (n % p == 0) {
            factors = append(factors, p);
            for (n % p == 0) {
                n /= p;
            }
        }
        if (p <= 1) {
            break;
        }
    }
    return factors;
}

func NIntegerDistinctPrimes(count int) {
    for i:=2; ; i++ {
        match := true
        for j := 0; j<count; j++ {
            factors := factorize(i+j)
            if len(factors) != count {
                match = false
                break
            }
        }
        if match {
            fmt.Println(i)
            for j := 0; j<count; j++ {
                factors := factorize(i+j)
                fmt.Println(j, factors)
            }
            return
        }
    }
}

func main() {
    NIntegerDistinctPrimes(2)
    NIntegerDistinctPrimes(3)
    NIntegerDistinctPrimes(4)
}
