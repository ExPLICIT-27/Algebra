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
bool findAnySolution(int a, int b, int c, int &x0, int &y0, int &g)
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
//finding all solutions within the constraint
//minx <= x <= maxx, miny <= y <= maxy
// logic : if you add b/g to x0 and subtract a/g from x1, the equation remains the same
// (a*b/g gets added and subtracted, hence the equation is same but x0 and x1 have another
// valid value)
void shift_solution(int &x, int &y, int a, int b, int cnt){
    x += cnt*b;
    y -= cnt*a;
}
int find_all_solutions(int a, int b, int c, int minx, int maxx, int miny, int maxy){
    int x, y, g;
    if(!findAnySolution(a, b, c, x, y, g))
        return 0;
    a /= g;
    b /= g;
    int sign_a = (a > 0)? 1 : -1;
    int sign_b = (b > 0)? 1 : -1;

    // finding x values within x constraint
    shift_solution(x, y, a, b, (minx - x)/b);
    if(x < minx)
        shift_solution(x, y, a, b, sign_b);
    if(x > maxx)
        return 0;
    int lx1 = x;

    shift_solution(x, y, a, b, (maxx - x)/b);
    if(x > maxx)
        shift_solution(x, y, a, b, -sign_b);
    if(x < minx)
        return 0;
    int rx1 = x;

    //finding x values within y constraint
    shift_solution(x, y, a, b, -(miny - y)/a);
    if(y < miny)
        shift_solution(x, y, a, b, -sign_a);
    if(y > maxy)
        return 0;
    int lx2 = x;

    shift_solution(x, y, a, b, -(maxy - y)/a);
    if(y > maxy)
        shift_solution(x, y, a, b, sign_a);
    if(y < miny)
        return 0;
    int rx2 = x;

    // finding intersection for the range (lx1, rx1), (lx2, rx2);
    if(lx2 > rx2)
        swap(lx2, rx2);
    int lx = max(lx1, lx2);
    int rx = min(rx1, rx2);

    // number of solutions
    return (rx - lx)/abs(b) + 1;
    
}
int main() {
    int a = 6, b = 9, c = 30;
    int minx = 0, maxx = 100;
    int miny = 0, maxy = 100;

    int count = find_all_solutions(a, b, c, minx, maxx, miny, maxy);
    cout << "Number of solutions: " << count << endl;

    return 0;
}
