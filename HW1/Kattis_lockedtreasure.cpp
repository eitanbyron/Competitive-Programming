#include <iostream>

using namespace std;

int fact(int n);

int nCr(int n, int r)
{
    double sum = 1;
    for(int i = 1; i <= r; i++){
        sum = sum * (n - r + i) / i;
    }
    return (int)sum;
}

int main() {
    int k, n,m;
    cin >> k;
    for (int i =0 ; i< k; i++)
    {
        cin >> n >>m;
        cout << nCr(n,m-1) << endl;
    }
    return 0;
}