/*
The most optimal algorithm for computing prime numbers in the range 1:n in terms of time complexity
(space complexity is much bad compared to classic eratosthenes sieve)

We make use of the concept of finding the smallest prime factor of a number
smallest prime factor of a number is itself if its prime else some other prime number
we keep marking all the smallest prime factors of numbers which have prime factors smaller than
or equal to the current number
*/
#include <bits/stdc++.h>

using namespace std;

vector<int> linearSieve(int n){
    vector<int> lp(n + 1, 0);
    vector<int> pr;
    for(int i = 2; i <= n; i++){
        if(!lp[i]){
            lp[i] = i;
            pr.push_back(i);
        }
        for(int j = 0; i*pr[j] <= n; j++){
            lp[i*pr[j]] = pr[j];
            if(pr[j] == lp[i])
                break;
        }
    }
    return pr;
}
int main(){
    vector<int> pr = linearSieve(100);
    for(int p : pr)
        cout << p << " ";
    
    return 0;
}