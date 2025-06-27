#include <bits/stdc++.h>
using namespace std;

// The trial division method, most basic

vector<long long> trialDiv1(long long n){
    vector<long long> factors;
    for(long long d = 2; d*d <= n; d++){
        while(n%d == 0){
            factors.push_back(d);
            n /= d;
        }
    }
    if(n > 1)
        factors.push_back(n);
    return factors;
}

// Wheel trial div, eliminate all even factors by factoring out the 2s first
vector<long long> trialDiv2(long long n){
    vector<long long> factors;
    while(n%2 == 0){
        n /= 2;
        factors.push_back(2);
    }
    for(long long d = 3; d*d <= n; d += 2){
        while(n%d == 0){
            factors.push_back(d);
            n /= d;
        }
    }
    if(n > 1){
        factors.push_back(n);
    }
    return factors;
}
// extending the method to include 2, 3 and 5 reducing the numbers to be checked to 33.33%
vector<long long> trialDiv3(long long n){
    vector<long long> factors;
    for(int d : {2, 3, 5}){
        while(n % d == 0){
            factors.push_back(d);
            n /= d;
        }
    }
    static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
    int i = 0;
    for(long long d = 7; d*d <= n; d += increments[i]){
        while(n % d == 0){
            factors.push_back(d);
            n /= d;
        }
        i = (i + 1)%increments.size();
    }
    if(n > 1)
        factors.push_back(n);
    return factors;
}
// extending wheel factorization indefinitely, we compute all prime numbers in the range n and factorize it
vector<long long> FindPrimes(long long n){
    vector<long long> primes;
    long long nsqrt = sqrt(n);
    vector<long long> isPrime(n + 2, true);
    for(long long i = 2; i*i <= nsqrt; i++){
        if(isPrime[i]){
            primes.push_back(i);
            for(long long j = i*i; j <= nsqrt; j += i)
                isPrime[j] = false;
        }
    }
    return primes;
}
vector<long long> trialDiv4(long long n, vector<long long> &primes){
    vector<long long> result;
    for(long long d : primes){
        if(d * d > n)
            break;
        while(n % d == 0){
            result.push_back(d);
            n /= d;
        }
    }
    if(n > 1)
        result.push_back(n);
    return result;
}
// Fermat's Factorization method
int fermat(int n){
    int a = ceil(sqrt(n));
    int b2 = a*a - n;
    int b = round(sqrt(b2));
    while(b*b != b2){
        a++;
        b2 = a*a - n;
        b = round(sqrt(b2));
    }
    return  a - b;
}
// Fermat's method is not guaranteed to work for all numbers, it works best for numbers that are products of two primes
// and is not efficient for numbers with large prime factors or many prime factors.
// It is also not efficient for numbers that are powers of primes or have small prime factors.


// Pollard's p-1 method
// Pollard's p-1 method is a probabilistic algorithm for integer factorization.
// It is based on the idea that if p is a prime factor of n, then p divides a^k - 1 for some integer k.
// Time Compexity : O(B*log(B)*log^2(n))
long long gcd(long long a, long long b){
    return (b)? gcd(b, a%b) : a;
}
long long power(long long a, long long p, long long n){
    long long result = 1;
    while(p){
        if(p & 1)
            result = (result*a)%n;
        a = (a*a)%n;
        p >>= 1;
    }
    return result;
}
vector<long long> primes_in_range(long long n){
    vector<long long> primes;
    vector<char> isPrime(n + 1, true);
    for(long long i = 2; i*i <= n; i++){
        if(isPrime[i]){
            for(int j = i*i; j <= n; j += i){
                isPrime[j] = false;
            }
        }
    }
    for(int i = 2; i <= n; i++){
        if(isPrime[i])
            primes.push_back(i);
    }
    return primes;
}
long long pollardsp_minus_1(long long n, vector<long long> &primes){
    int B = 10;
    long long g = 1;
    while(B <= 1000000 && g < n){
        long long a = 2 + rand()%(n - 3);
        g = gcd(a, n);
        if(g > 1)
            return g;
        for(long long p : primes){
            if(p >= B)
                continue;
            long long p_power = 1;
            while(p_power*p <= B)
                p_power *= p;
            a = power(a, p_power, n);
            g = gcd(a - 1, n);
            if(g > 1 && g < n)
                return g;
        }
        B *= 2;
    }
    return 1;
}
// pollards rho method is another probabilistic algorithm for integer factorization.
// It is based on the idea that if p is a prime factor of n, then p divides a^k - 1 for some integer k.
// It is more efficient than Pollard's p-1 method for numbers with large prime factors or many prime factors.
// Pollard's rho method is not guaranteed to work for all numbers, it works best for numbers that are products of two primes
// and is not efficient for numbers with large prime factors or many prime factors.
// It is also not efficient for numbers that are powers of primes or have small prime factors.

long long mult(long long a, long long b, long long n){
    return (__int128)a*b % n;
}
long long f(long long x, long long c, long long n){
    return (mult(x, x, n) + c) % n;
}
long long rho(long long n, long long x0 = 2, long long c = 1){
    long long x = x0;
    long long y = x0;
    long long g = 1;
    while(g == 1){
        x = f(x, c, n);
        y = f(f(y, c, n), c, n);
        g = gcd(abs(x - y), n);
    }
    return g;
}
int main(){
    vector<long long> factors = trialDiv2(13);
    for(long long i : factors)
        cout << i << " ";
    cout << endl;
    factors = trialDiv3(62);
    for(long long i : factors)
        cout << i << " ";
    cout << endl;
    factors = trialDiv3(162);
    for(long long i : factors)
        cout << i << " ";
    cout << endl;
    cout << fermat(55) << endl;
    vector<long long> primes = primes_in_range(49);
    cout << pollardsp_minus_1(49, primes) << endl;
    cout << rho(49) << endl;
    return 0;
}