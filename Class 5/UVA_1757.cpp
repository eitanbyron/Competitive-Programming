// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector<vector<char>> vvs;
const int INF = 1e9;



bool bfs(const vvi& g, int s, int stop) {
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if(u == stop){
            return true;
        }
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                if(v == stop){
                    return true;
                }
                q.push(v);
            }
    }
    return false;
}

int main() {

    int m , n;
    char a, b;
    string s1, s2;
    while (cin >> m >> n) {
        vvi trans(26);
        for (int i = 0; i < m; ++i) {
            cin >> a >> b;
            trans[a - 'a'].push_back(b - 'a');

        }
        for (int i = 0; i < n; ++i) {
            cin >> s1 >> s2;
            if (s1.size() != s2.size()) {
                cout << "no" << endl;
                continue;
            }
            bool result = false;
            for (int j = 0; j < s1.size(); ++j) {
                result = bfs(trans, s1[j] - 'a', s2[j] - 'a');
                if (!result) break;
            }
            if (result) {
                cout << "yes" << endl;
            } else {
                cout << "no" << endl;
            }
        }

    }
}