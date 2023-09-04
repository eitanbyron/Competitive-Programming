#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

typedef pair<long long,long long> ii;
typedef pair<long long,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<long long> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;
long long augment(vvi& res, int s, int t, const vi& p, long long int minEdge,vi& path) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if(t!=0&&t!=1) path.push_back(t);
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]),path);
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
int EdmondsKarp (int n, vector<iii>& edges, int s, int t,vvi& paths) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    int numPath=0;
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
        addedFlow = augment(res, s, t, p, INF,paths[numPath]);
        numPath++;
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}
int main() {
    int n;
    vector<iii> edges;
    map<long long int,int> valueToIdx;
    map<pair<int,int>,string> edgeToString;
    cin>>n;
    vvi paths=vvi(n);
    long long int a,b;
    int minIndex=n+2;
    vector<long long int> results(3);
    vector<string> strings(3);
    for(int i=0;i<n;i++){
        edges.emplace_back(1, make_pair(0,i+2));
        cin>>a>>b;
        results[0]=a+b;
        results[1]=a-b;
        results[2]=a*b;
        strings[0]=to_string(a)+" + "+to_string(b)+" = "+ to_string(results[0]);
        strings[1]=to_string(a)+" - "+to_string(b)+" = "+ to_string(results[1]);
        strings[2]=to_string(a)+" * "+to_string(b)+" = "+ to_string(results[2]);
        for(int j=0;j<3;j++){
            long long int res=results[j];
            if(valueToIdx.find(res)==valueToIdx.end()){
                valueToIdx[res]=minIndex;
                edges.emplace_back(1, make_pair(i+2,minIndex));
                edges.emplace_back(1, make_pair(minIndex,1));
                edgeToString[make_pair(i+2,minIndex)]=strings[j];
                minIndex++;
            }
            else{
                edges.emplace_back(1, make_pair(i+2,valueToIdx[res]));
                edgeToString[make_pair(i+2,valueToIdx[res])]=strings[j];
            }
        }
    }
    if(EdmondsKarp(minIndex,edges,0,1,paths)==n){
        vi finalEdges(n);
        for(auto path:paths){
            finalEdges[path[1]-2]=path[0];
        }
        for(int i=0;i<n;i++){
            cout<<edgeToString[make_pair(i+2,finalEdges[i])]<<endl;
        }
    }
    else cout<<"impossible"<<endl;
    return 0;
}