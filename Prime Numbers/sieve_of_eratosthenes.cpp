/*
Sieve of eratosthenes is an algorithm for finding all the prime numbers in the 
range 1:n; using O(nlog(log(n))) operations


Logic : mark all numbers as prime initially
starting from 2 which is the first prime number, mark all its multiples as non prime
keep doing the same till you reach the integral value of root(n)
*/

#include <bits/stdc++.h>

using namespace std;

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
int main(){
    PrimeNumbers(20);
    return 0;
}