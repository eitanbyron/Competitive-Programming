// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
const int INF = 1e9;

/********** Topological Sort **********/


// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|vertices_num|-1).
// output: is g a DAG (return value), a topological ordering of g (order).
// comment: order is valid only if g is a DAG.
// time: O(vertices_num+E).
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
    // DFS on digraph g from node u:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (auto& v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|vertices_num|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(vertices_num+E).
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
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|vertices_num|-1).
// output: strongly connected components graph of g (sccg).
// time: O(vertices_num+E).
void findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge u->v
            if (component[u] != component[v])
                sccg[component[u]].insert(component[v]);
}


/********** Shortest Paths **********/


// input: non-negatively weighted directed graph (g[u] contains pairs (v,col) such that u->v has weight col, nodes are named 0,1,...,|vertices_num|-1), source (s).
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

// input: weighted directed graph (g[u] contains pairs (v,col) such that u->v has weight col, nodes are named 0,1,...,|vertices_num|-1), source node (s).
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle.
// time: O(VE).
bool BellmanFord(const vvii& g, int s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // vertices_num times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight col
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

// input: weighted directed graph (g[u] contains pairs (v,col) such that u->v has weight col, nodes are named 0,1,...,|vertices_num|-1).
// output: the pairwise distances (d).
// time: O(vertices_num^3).
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
    vector<int> rank;
    vector<int> parent;

    unionfind (int size) {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++) parent[i]=i;
    }

    int find(int x) {
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x) {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if(q==p) return;
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
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


int augment(vector<map<int,int>>& res, int s, int t, const vi& p, int minEdge) {
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
    vector<map<int,int>> res(n);
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


class max_flow {
private:
    int vertices_num;
    vector<edge> edges;
    vector<vi> vertices;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t) {
        d.assign(vertices_num, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(vertices_num, {-1, -1});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;
            for (auto &idx : vertices[u]) {
                auto &[v, cap, flow] = edges[idx];
                if ((cap - flow > 0) && (d[v] == -1))
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx};
            }
        }
        return d[t] != -1;
    }

    ll DFS(int u, int t, ll f = INF) {
        if ((u == t) || (f == 0)) return f;
        for (int &i = last[u]; i < (int)vertices[u].size(); ++i) {
            auto &[v, cap, flow] = edges[vertices[u][i]];
            if (d[v] != d[u] + 1) continue;
            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(edges[vertices[u][i] ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

    void add_edge_internal(int u, int v, ll w) {
        if (u == v) return;
        edges.emplace_back(v, w, 0);
        vertices[u].push_back(edges.size() - 1);
        edges.emplace_back(u, 0, 0);
        vertices[v].push_back(edges.size() - 1);
    }

    static int in(int v) { return v; }
    int out(int v) const { return v + vertices_num / 2; }

public:
    explicit max_flow(int initialV) {
        vertices_num = 2 * initialV;
        edges.clear();
        vertices.assign(vertices_num, vi());  // double the nodes because vertex capacities
    }

    void set_node(int u, ll w) {  // set vertex capacity, MUST BE CALLED FOR EACH NODE
        add_edge_internal(in(u), out(u), w);
    }

    void add_edge(int u, int v, ll w, bool directed = true) {
        add_edge_internal(out(u), in(v), w);
        if (!directed) {
            add_edge_internal(out(v), in(u), w);
        }
    }

    ll getMaxFlow(int s, int t) {
        s = in(s);
        t = out(t);
        ll max_flow = 0;
        while (BFS(s, t)) {
            last.assign(vertices_num, 0);
            while (ll f = DFS(s, t))
                max_flow += f;
        }
        return max_flow;
    }
};

int row, col;
int getIndex(int r, int c) { return r * col + c; }
pair<int, int> getCoordinates(int i) { return {i / col, i % col}; }
bool coorOnEdge(int i) {
    auto [r, c] = getCoordinates(i);
    return r == 0 || r == row - 1 || c == 0 || c == col - 1;
}


int main() {
    int grid[301][301];
    cin >> row >> col;
    max_flow G(row * col + 1);
    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            cin >> grid[r][c];
            G.set_node(getIndex(r, c), grid[r][c]);
            int direction_row[] = {-1, 0, 1, 0};
            int direction_col[] = {0, 1, 0, -1};
            for (int i = 0; i < 4; i++) {
                int new_row = r + direction_row[i];
                int new_col = c + direction_col[i];
                if (new_row < 0 || new_row >= row || new_col < 0 || new_col >= col) continue;
                G.add_edge(getIndex(r, c), getIndex(new_row, new_col), INF);
            }

            if (coorOnEdge(getIndex(r, c))) {
                G.add_edge(row * col, getIndex(r, c), INF);
            }
        }
    }
    int castle_r, castle_c;
    G.set_node(row * col, INF);
    cin >> castle_r >> castle_c;
    int t = getIndex(castle_r, castle_c);
    cout << G.getMaxFlow(row * col, t) << endl;

    return 0;
}