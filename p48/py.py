import math

def selfPowers(upto):
    s = 0
    m = 10000000000
    for i in range(1, upto+1):
        s += pow(i, i, m)
        s %= m
    return s

print(selfPowers(10))
print(selfPowers(1000))
