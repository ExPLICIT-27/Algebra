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
    cout << fermat(55);
    return 0;
}