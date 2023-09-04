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

const int INF = 1e9;


/********** Shortest Paths **********/


// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist).
// time: O(ElogV).
void Dijkstra(const vvii& g, int s, vi& dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u]+w < dist[v]) {
                dist[v] = dist[u]+w;
                q.push({dist[v], v});
            }
        }
    }
}


using namespace std;

int mapping(int city, int fuel)
{ return city * 101 + fuel; }


int main() {
    int n,m, p, u,v,d, q,c,s,e, ans;
    vi prices, dist;
    cin >> n >> m;
    vvii graph (n* 101 +1, vii());
    for (int i =0; i< n; i++)
    {
        cin >> p;
        prices.emplace_back(p);
    }
    for (int i=0; i <m; i++)
    {
        cin >> u >>v >>d;
        for (int j = d; j <= 100; j++) {
            graph[mapping(u, j)].emplace_back(mapping(v, j - d), 0);
            graph[mapping(v, j)].emplace_back(mapping(u, j - d), 0);
        }
    }
    cin >> q;
    while (q--) {
        cin >> c >> s >> e;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c; j++) {
                graph[mapping(i, j)].emplace_back(mapping(i, j + 1), prices[i]);
            }
        }
        Dijkstra(graph, mapping(s,0), dist);
        ans = INF;
        for (int i = 0; i%101 <= c; i++) {
            ans = min(ans, dist[mapping(e, i)]);
        }
        if (ans == INF)
            cout << "impossible" << endl;
        else
            cout << ans << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c; j++) {
                graph[mapping(i, j)].pop_back();
            }
        }
    }
    return 0;
}