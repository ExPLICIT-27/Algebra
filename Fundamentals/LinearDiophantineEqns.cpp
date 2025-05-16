/*
Linear diophantine equations are of the form
ax + by = c
multiple cases can be asked such as
- finding one solution
- finding all solutions
- finding the number of solutions and the solutions in a given interval
- finding a solution with minimum value of x and y
degenerate case, when c = 0, or a = 0, b = 0 leading to infinitely many sols
or no sols
Analytic solution

ax + by = c
hence c can be considered as some multiple of b that leaves ax as remainder
or ax = c mod b
similarly
by = c mod a
assuming b != 0 and a and b are co prime
x = ca^(-1) mod b
a^-1 is the modular inverse of a mod b
when it is not prime, consider the algorithmic solution (Bezout's Lemma)

we know ax + by = g, where g is the gcd of a, b has multiple solutions
we need to find solutions for ax + by = c
divide by g and multiply by c
ax*c/g + by*c/g = c
x0 = x*c/g, y0 = y*c/g
ax0 + by0 = c
*/
#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = x1, y = x1 - y1 * (a / b);
    return d;
}
bool findAnySolution(int a, int b, int c, int &x0, int &y0, int g)
{
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g)
        return false; // no integral solution to the equation
    x0 *= c / g;
    y0 *= c / g;
    if (a < 0)
        x0 *= -1;
    if (b < 0)
        y0 *= -1;
    return true;
}
int main()
{
    return 0;
}
