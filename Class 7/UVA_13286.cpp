#include <bits/stdc++.h>
#include <stdint.h>
#include <vector>
#include <map>
using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<ii> vii;
using namespace std;
const int MAX_N = 16384;
const int MAX_B = 16384;
struct Edge {
    int v, c, p;
    Edge(int v, int c = INT_MAX, int p = INT_MAX):
            v(v), c(c), p(p) {}
};
map<string, int> translate;
vi deg(MAX_N);
vii table(MAX_N);
vector<Edge> g[MAX_N];
int str2int(string x) {
    int &v = translate[x];
    if (v == 0) {
        v = translate.size();
        g[v].clear(), table[v] = {INT_MAX, INT_MAX};
    }
    return v;
}

int main() {
    int m, n;
    string s1, s2,s3;
    while (cin>>m>>n) {
        translate.clear();
        for (int i = 0; i < n; i++) {
            int c, p;
            cin>>s1>>s2>>s3>>c>>p;
            int u = str2int(s1), v = str2int(s2);
            g[v].emplace_back(u, c, p), deg[u]++;
        }

        queue<int> Q;
        for (int i = 1; i <= translate.size(); i++) {
            if (deg[i] == 0)
                Q.push(i), table[i] = {0, 0};
        }

        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            pair<int, int> t = table[u];
            for (Edge e : g[u]) {
                if (--deg[e.v] == 0)
                    Q.push(e.v);
                if ((t.first + e.c < table[e.v].first) ||
                    (t.first + e.c == table[e.v].first && t.second + e.p > table[e.v].second))
                    table[e.v] = {t.first + e.c, t.second + e.p};
            }
        }
        static long int dp[MAX_B];
        {
            memset(dp+1, -1, sizeof(dp[0])*m);
            int mx_w = 0;
            for (int i = 1; i <= translate.size(); i++) {
                int w = table[i].first, v = table[i].second;
                mx_w = min(mx_w+w, m);
                for (int j = mx_w; j >= w; j--) {
                    if (dp[j-w] >= 0)
                        dp[j] = max(dp[j], dp[j-w]+v);
                }
            }
        }

        long long ret_c = 0, ret_w = 0;
        for (int i = 1; i <= m; i++) {
            if (dp[i] > ret_w)
                ret_w = dp[i], ret_c = i;
        }
        cout<<ret_w<<endl;
        cout<<ret_c<<endl;
    }
    return 0;
}