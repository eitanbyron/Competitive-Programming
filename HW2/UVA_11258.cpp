#include <iostream>
#include <cstring>
#include<algorithm>
#include<vector>

using namespace std;

typedef long long ll;


int main() {
    int n, length;
    ll sum;
    string str;
    vector <ll> DP;
    cin >> n;
    while (n--) {
        cin >> str;
        length = str.length();
        DP.assign(201, 0);
        for (int i = 0; i < length; i++) {
            if (str[i] != 0) {
                sum = 0;
                for (int j = i; j < length; j++) {
                    sum = sum * 10 + (str[j] - '0');
                    if (sum > INT32_MAX)
                        break;
                    DP[j + 1] = max(DP[j + 1], DP[i] + sum);
                }
            } else {
                DP[i + 1] = max(DP[i + 1], DP[i]);
            }
        }
        cout << DP[length] << endl;
    }
    return 0;
}