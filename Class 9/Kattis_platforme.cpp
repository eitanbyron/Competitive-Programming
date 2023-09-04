//
// Created by barbe on 06/06/2023.
//

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    tuple<int, int, int> platforms[105];
    bool seen[10005][10005], platform[10005][10005];
    int n, height, start, end;
    ll res = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> height >> start >> end;
        platforms[i] = make_tuple(height, start, end);
    }
    sort(platforms, platforms + n);
    for (int i = 0; i < n; i++) {
        auto &[hei, sta, e] = platforms[i];
        for (int j = hei; j > 0; j--) {
            if (platform[j][sta] == true) {
                break;
            }

            seen[j][sta] = true;
            res++;
        }
        for (int j = hei; j > 0; j--) {
            if (platform[j][e-1] == true) {
                break;
            }

            seen[j][e - 1] = true;
            res++;
        }
        for (int j = sta; j < e; j++) {
            platform[hei][j] = true;
        }
    }
    cout << res << endl;
    return 0;
}