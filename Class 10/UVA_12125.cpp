#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <cmath>


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



/********** Max Flow **********/


int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}


double dist(double x1, double y1, double x2, double y2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(x1 - x2, y1 - y2); }



int n;
int cti(int pos, int t)
{ return n * t + pos; }

int main() {
    int t, jumps, peng,count;
    double d;
    double x,y;
    cin >> t;
    vector<iii> edges;
    vector<ii> locations;
    while (t--)
    {
        count =0;
        edges.clear();
        locations.clear();
        cin >> n >> d;
        int size = 2*n +1;
        for (int i =1; i<=n; i++)
        {
            cin >> x >> y >> peng >> jumps;
            count += peng;
            iii temp = {jumps, {i, n+i}};
            edges.push_back(temp);
            temp = {peng,{0,i}};
            edges.push_back(temp);
            ii temp2 = {x,y};
            locations.push_back(temp2);
        }

        for (int i = 0; i<n; i++)
        {
            for (int j = 0; j<n;j++)
            {
                if (j != i)
                {
                    if (dist(locations[i].first, locations[i].second, locations[j].first, locations[j].second) <= d)
                    {
                        iii temp = {INF, {i+n+1, j+1}};
                        edges.push_back(temp);
                    }
                }
            }
        }
        bool printed =false;
        for (int i = 1; i<=n; i++)
        {
            if (EdmondsKarp(size,edges,0,i) == count) {
                if(!printed)
                    printed = true;
                else
                    cout << " ";
                cout << i-1;

            }
        }
        if(!printed)
            cout << -1;
        cout << endl;
    }
    return 0;
}