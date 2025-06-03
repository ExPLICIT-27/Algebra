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
int main(){
    vector<long long> factors = trialDiv2(13);
    for(long long i : factors)
        cout << i << " ";
    return 0;
}