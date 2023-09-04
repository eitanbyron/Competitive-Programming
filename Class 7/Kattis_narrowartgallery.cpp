#include <algorithm>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;

vector<vector<int>> aux;
int n;
int memo[201][3][201];

int dp (int row, int k, int previous)
{
    if (row == n) {
        if (k == 0)
            return 0;
        else
            return -1e4;
    }
    if (memo[row][previous][k] != -1)
        return memo[row][previous][k];
    if (k == 0){
        return memo[row][previous][k] = dp(row+1, 0, 0) + aux[row][0] + aux[row][1];
    }

    int ans = dp(row+1, k, 0) + aux[row][0] +  aux[row][1];

    if(previous == 0 || previous == 2){
        ans = max(ans, dp(row+1, k-1, 2) + aux[row][1]);
    }
    if(previous == 0 || previous == 1){
        ans = max(ans, dp(row+1, k-1, 1) + aux[row][0]);
    }

    return memo[row][previous][k] = ans;
}


int main() {
    int k, temp1, temp2;
    cin >> n >>k;
    aux.assign(n, vector<int>(2, -1));
    for (int i = 0; i<n; i++)
    {
        cin>> temp1 >> temp2;
        aux[i][0] = temp1;
        aux[i][1] = temp2;
    }
    memset(memo, -1, sizeof memo);
    cin >> temp1 >> temp2;
    cout << dp (0,k,0) << endl;
    return 0;
}