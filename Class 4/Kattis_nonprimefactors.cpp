#include <iostream>
using namespace std;

const int maxn = 2000005;
int maxPrime[maxn];

void findMaxPrime(){
    maxPrime[0] = 0;
    maxPrime[1] = 1;
    for (int i=2; i<maxn; i++){
        if (maxPrime[i] > 0) continue;
        for (int j=i; j<maxn; j+=i){
            maxPrime[j] = i;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int lines, num;

    findMaxPrime();

    cin >> lines;
    while (lines--){
        cin >> num;
        int lastPrime = 0;
        int primeFactorNum = 0;
        int counter = 0;
        int factorNum = 1;

        while (num > 1){
            if (maxPrime[num] == lastPrime) counter++;
            else {
                factorNum *= (counter + 1);
                lastPrime = maxPrime[num];
                primeFactorNum++;
                counter = 1;
            }
            num /= maxPrime[num];
        }
        factorNum *= (counter + 1);
        cout << factorNum - primeFactorNum << '\n';
    }
    return 0;
}