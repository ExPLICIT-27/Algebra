/*
Sieve of eratosthenes is an algorithm for finding all the prime numbers in the 
range 1:n; using O(nlog(log(n))) operations


Logic : mark all numbers as prime initially
starting from 2 which is the first prime number, mark all its multiples as non prime
keep doing the same till you reach the integral value of root(n)
*/

#include <bits/stdc++.h>

using namespace std;

// Sieving till root
void PrimeNumbers(long long n){
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    cout << "Prime numbers in the range [1:n] are : ";
    for(long long i = 2; i*i <= n; i++){
        if(isPrime[i]){
            for(long long j = i*i; j <= n; j += i){
                isPrime[j] = false;
            }
        }
    }
    for(int i = 2; i <= n; i++){
        if(isPrime[i])
            cout << i << " ";
    }
}

// segmented sieve
/*
storing prime numbers until root(n) then using them to find all the prime numbers in the 
range [1:n], 
dividing the range into fixed size blocks of size S, we reuse the same block to 
reduce space complexity to root(n) + S
using vector<char> for isPrime is found to be faster
*/
int countPrimes(int n){

    const int S = 10000; // block size
    vector<int> primes;
    int nsqrt = sqrt(n);
    vector<char> isPrime(nsqrt + 2, true);
    for(int i = 2; i <= nsqrt; i++){
        if(isPrime[i]){
            primes.push_back(i);
            for(int j = i*i; j <= nsqrt; j += i){
                isPrime[j] = false;
            }
        }
    }
    
    int result = 0;
    vector<char> block(S);
    for(int k = 0; k*S <= n; k++){
        fill(block.begin(), block.end(), true);
        int start = k*S;
        for(int p : primes){
            int start_idx = (start + p - 1)/p;
            int j = max(start_idx, p)*p - start;
            for(; j < S; j += p){
                block[j] = false;
            }
        }

        if(k == 0)
            block[0] = block[1] = false;
        for(int i = 0; i < S && start + i <= n; i++){
            if(block[i])
                result++;
        }
    }
    return result;
}

// Primes in the range [L, R]
vector<char> primesInRange(long long L, long long R){
    long long lim = sqrt(R);
    vector<char> isPrime(lim + 1, true);
    vector<long long> primes;
    for(long long i = 2; i <= lim; i++){
        if(isPrime[i]){
            primes.push_back(i);
            for(long long j = i*i; j <= lim; j += i)
                isPrime[j] = false;
        }
    }
    vector<char> result(R - L + 1, true);
    for(long long p : primes){
        for(long long j = max(p*p, ((L + p - 1)/p)*p); j <= R; j += p)
            result[j - L] = false;
    }
    if(L == 1)
        result[0] = false;
    return result;
}
int main(){
    PrimeNumbers(20);
    cout << endl;
    cout << countPrimes(10000) << endl;
    long long L = 100, R = 200;
    vector<char> res = primesInRange(L, R);
    for(long long i = 0; i < res.size(); i++){
        if(res[i])
            cout << L + i << " ";
    }
    return 0;
}