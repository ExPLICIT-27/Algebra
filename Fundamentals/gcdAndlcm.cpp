/*
Euclidean method of finding GCD
gcd(a, b) = (b == 0)? a : gcd(b, a%b)
lcm = (a*b)/gcd(a, b)
T.C O(log(min(a, b)))
*/
#include <bits/stdc++.h>

using namespace std;

int gcdRec(int a, int b)
{
    return (b) ? gcdRec(b, a % b) : a;
}
int gcdIter(int a, int b)
{
    while (b)
    {
        a %= b;
        swap(a, b);
    }
    return a;
}
int lcm(int a, int b)
{
    return a * b / gcdIter(a, b);
}
int extendedGCD(int a, int b, int &x, int &y);
int main()
{
    cout << gcdRec(7, 21) << " " << gcdIter(7, 21) << endl;
    cout << lcm(7, 21) << endl;
    int x, y;
    extendedGCD(7, 21, x, y);
    cout << x * 7 + y * 21;
    return 0;
}
/*
extended euclidean algorithm
given a and b
find values x and y such that a*x + b*y = gcd(a, b)
note :
at last stage, b = 0 and a = gcd(a, b)
therefore for last stage x = 1, b = 0
we need to find the relationship between the previous stage and the next stage
gcd(a, b) => extends to gcd(b, a%b)
ax + by = g
bx1 + (a%b)y1 = g
bx1 + (a - (a//b)*b)y1 = g
rearraning,
ay1 + b(x1 - y1*(a//b)) = g
comparing, x = y1, y = x1 - y1*(a//b)
(note : this logic is also used in finding all possible solutions to a pair of
linear equations)
*/
int extendedGCD(int a, int b, int &x, int &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int d = extendedGCD(b, a % b, x1, y1);
    x = y1, y = x1 - y1 * (a / b);
    return d;
}