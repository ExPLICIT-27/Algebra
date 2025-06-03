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
int main(){
    cout << TrialTest(6) << endl;
    cout << probabilisticFermat(6) << endl;
    return 0;
}