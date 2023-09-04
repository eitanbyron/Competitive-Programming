#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <tuple>
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
typedef long long ll;


/********** Topological Sort **********/


// input: directed graph (g[a] contains the neighbors of a, nodes are named 0,1,...,|V|-1).
// output: is g a DAG (return value), a topological ordering of g (order).
// comment: order is valid only if g is a DAG.
// time: O(V+E).
bool topological_sort(const vvi& g, vi& order) {
    // compute indegree of all nodes
    vi indegree (g.size(), 0);
    for (int v=0; v<g.size(); v++) for (int u : g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v=0; v<g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u]==0) order.push_back(u);
        }
    return order.size()==g.size();
}


/********** Strongly Connected Components **********/


const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvi& g, int u, vi& S, vi& colorMap, int color) {
    // DFS on digraph g from node a:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (b), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (auto& v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[a] contains the neighbors of a, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
int findSCC(const vvi& g, vi& components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (int i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(),vi());
    for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    int numSCC = 0;
    for (int i = (int)g.size()-1; i >= 0; --i)
        if (components[postOrder[i]] == UNSEEN)
            KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
    return numSCC;
}

// Computes the SCC graph of a given digraph.
// input: directed graph (g[a] contains the neighbors of a, nodes are named 0,1,...,|V|-1).
// output: strongly connected components graph of g (sccg).
// time: O(V+E).
void findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge a->b
            if (component[u] != component[v])
                sccg[component[u]].insert(component[v]);
}


/********** Shortest Paths **********/


// input: non-negatively weighted directed graph (g[a] contains pairs (b,w) such that a->b has weight w, nodes are named 0,1,...,|V|-1), source (s).
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
        if (d > dist[u]) continue; // We may have found a shorter way to get to a after inserting it to q.
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

// input: weighted directed graph (g[a] contains pairs (b,w) such that a->b has weight w, nodes are named 0,1,...,|V|-1), source node (s).
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle.
// time: O(VE).
bool BellmanFord(const vvii& g, int s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges a->b with weight w
        for (int u = 0; u < g.size(); ++u) for (ii e : g[u]) {
                int v = e.first;
                int w = e.second;
                // relax the edge
                if (d[u] < INF && d[u]+w < d[v]) {
                    d[v] = d[u]+w;
                    changed = true;
                }
            }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}

// input: weighted directed graph (g[a] contains pairs (b,w) such that a->b has weight w, nodes are named 0,1,...,|V|-1).
// output: the pairwise distances (d).
// time: O(V^3).
void FloydWarshall(const vvii& g, vvi& d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (int u=0; u<g.size(); ++u) d[u][u] = 0;
    for (int u=0; u<g.size(); ++u) for (ii e: g[u]) {
            int v = e.first; int w = e.second;
            d[u][v] = min(d[u][v],w);
        }
    // relax distances using the Floyd-Warshall algorithm
    for (int k=0; k<g.size(); ++k)
        for (int u=0; u<g.size(); ++u)
            for (int v=0; v<g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k]+d[k][v]);
}


/********** Min Spanning Tree **********/


struct unionfind {
private:
    vector<int> parent, rank, sizes;

public:
    unionfind(int N) {
        parent.assign(N, 0);
        for (int i = 0; i < N; ++i) parent[i] = i;
        rank.assign(N, 0);
        sizes.assign(N, 1);
    }

    int find(int i) { return (parent[i] == i) ? i : (parent[i] = find(parent[i])); }
    bool isSameSet(int i, int j) { return find(i) == find(j);}
    int sizeOfSet(int i) { return sizes[find(i)]; }

    void unite(int i, int j) {
        if (isSameSet(i, j)) return;
        int x = find(i), y = find(j);
        if (rank[x] > rank[y]) swap(x, y);
        parent[x] = y;
        if (rank[x] == rank[y]) ++rank[y];
        sizes[y] += sizes[x];
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (vertices_num), all nodes are between 0 and vertices_num-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii>& edges, int n) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}


/********** Max Flow **********/


int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to parent.
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

// input: number of nodes (vertices_num), all nodes are between 0 and vertices_num-1,
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
        // save to parent the BFS tree from s to t using only edges with residuals
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
        // add flow on the path between s to t according to parent
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}

void bfs(const vvi& g, int s, vector<int>& d ) {
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    d.assign(g.size(),INF); d[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u]+1;
                q.push(v);
            }
    }
}


int main() {
    ll vertices_num, edges_tree_num, a, b, w, total_cost;
    vector<tuple<ll, ll, ll>> edges;
    int test_case_num;
    cin >> test_case_num;
    while (test_case_num--) {
        cin >> vertices_num;
        edges_tree_num = vertices_num - 1;
        edges.clear();
        total_cost = 0;
        unionfind uf(vertices_num);

        for (int i = 0; i < edges_tree_num; i++) {
            cin >> a >> b >> w;
            edges.emplace_back(w, a - 1, b - 1);
        }
        sort(edges.begin(), edges.end());
        for (int i = 0; i < edges_tree_num; i++) {
            ll a = get<1>(edges[i]);
            ll b = get<2>(edges[i]);
            ll w = get<0>(edges[i]);

            total_cost += w;
            total_cost += (w + 1) * (ll)(uf.sizeOfSet(a) * uf.sizeOfSet(b) - 1);
            uf.unite(a, b);
        }

        cout << total_cost << endl;
    }
}