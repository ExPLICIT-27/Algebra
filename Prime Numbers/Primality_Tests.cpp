/*
Basic trial tests till root n
*/
#include <bits/stdc++.h>

using namespace std;

bool TrialTest(int n){
    for(int d = 2; d*d <= n; d++){
        if(n%d == 0)
            return false;
    }
    return n >= 2;
}
/*
Probabilistic Fermat's Theorem
If p is a prime number, then any base a ( >= 2) a^(p - 1) should be equal to 1%p
if not it is highly likely to be a composite number 
*/
long long binpow(int a, int p, int mod){
    long long result = 1;
    while(p){
        if(p&1)
            result = result*a%mod;
        p >>= 1;
        a = a*a%mod;
    }
    return result;
}
// fermat's test
bool probabilisticFermat(int n, int iters = 5){
    if(n <= 4)
        return n == 3 || n == 2;
    for(int i = 0; i < iters; i++){
        int a = 2 + rand()%(n - 3);
        if(binpow(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
// miller - rabin primality test => higher version of Fermat's test
using u64 = uint64_t;
using u128 = __uint128_t;
u64 binpower(u64 base, u64 e, u64 mod){
    u64 result = 1;
    while(e){
        if(e & 1)
            result = (u128)result*base%mod;
        base = (u128)base*base%mod;
        e >>= 1;
    }
    return result;
}
bool check_composite(u64 a, u64 d, int s, u64 n){
    u64 x = binpower(a, d, n);
    if(x == 1 || x == n - 1)
        return false;
    for(int r = 1; r < s; r++){
        x = (u128)x*x%n;
        if(x == n - 1)
            return false;
    }
    return true;
}
bool MillerRabin(u64 n, int iter = 5){
    if(n < 4)
        return n == 3 || n == 4;
    u64 d = n - 1;
    int s = 0;
    while((d & 1) == 0){
        s++;
        d >>= 1;
    }
    for(int i = 0; i < iter; i++){
        u64 a = 2 + rand()%(n - 3);
        if(check_composite(a, d, s, n))
            return false;
    }
    return true;
}

// the miller rabin can be made deterministic for 64 bit integers using just
//the first 12 prime numbers as bases
bool deterministicMillerRabin(u64 n){
    if(n < 2)
        return false;
    int s = 0;
    u64 d = n - 1;
    while((d & 1) == 0){
        s++, d >>= 1;
    }
    for(int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}){
        if(n == a)
            return true;
        if(check_composite(a, d, s, n))
            return false;
    }
    return true;
}
int main(){
    cout << TrialTest(6) << endl;
    cout << probabilisticFermat(6) << endl;
    cout << MillerRabin(6) << endl;
    cout << deterministicMillerRabin(6) << endl;
    return 0;
}