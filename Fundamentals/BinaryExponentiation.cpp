/*
Binary exponentiation allows you to calculate a^n using log(n) multiplications rather
than n

logic => consider the binary representation of a number
for eg: 3^13 -> 3^(1101) -> (can be obtained by 3*3^4*3^8)
hence for a^b, start with a,
right shift b, if rightmost bit is set, then multuply result with a,
keep taking the square of a and assign it to itself
3^5
initially a = 3, b = 5 (101)
result = 1
while b > 0
    if b & 1
        result = result*a (becomes 3, then 3*3^4)
    a = a*a (3^2, 3^4)
return result
*/
#include <bits/stdc++.h>

using namespace std;
long long binexp(long long a, long long b)
{
    long long result = 1;
    while (b > 0)
    {
        if (b & 1)
            result *= a;
        a *= a;
        b >>= 1;
    }
    return result;
}
int main()
{
    cout << binexp(2, 7);
    return 0;
}