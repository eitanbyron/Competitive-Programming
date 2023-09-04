#include <algorithm>
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define INF 1E9


int main() {
    int T,N, R,C, a, b, m, dist, cases =1;
    double prob;
    vector<vector<int>> towns (105 , vector<int> (105, 0));
    vector<vector<double>> dp;
    string s;
    cin >> T;
    while (T--)
    {
        cin >> N >>R;
        for (int i =0; i< N; i++)
        {
            cin >> s;
            for (int j =0 ; j< N; j++)
            {
                if (s[j] == 'Y')
                    towns[i][j] = 1;
                else
                    towns[i][j] = INF;
            }
        }
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    towns[i][j] = min(towns[i][j], towns[i][k] + towns[k][j]);
                }
            }
        }
        dp.assign(105, vector<double>(10005, 0));
        dp[0][0] = 1;
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j < 10005; j++) {
                if (dp[i][j] == 0)
                    continue;
                for (int k = 1; k <= R && j + k < 10005; k++) {
                    dp[i+1][j+k] += dp[i][j] / R;
                }
            }
        }
        cin >> C;
        cout << "Case " << cases << endl;
        while (C--)
        {
            cin >> a >> b >> m;
            prob =0;
            dist = towns [a-1][b-1];
            if (dist != INF)
                for (int i = m; i >= 0; i--) {
                    prob += dp[dist][i];
                }
            cout << fixed << setprecision(6) << prob << endl;
        }
        cases++;
        cout << endl;
    }
    return 0;
}