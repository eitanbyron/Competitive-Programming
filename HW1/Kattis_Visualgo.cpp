#include <iostream>
#include <vector>
#include <queue>


#define INF 1e9

using namespace std;


int main() {
    int V,E, u,v,w,s,t;
    long long curr,currcost, next,nextcost;
    cin >> V>>E;
    vector<vector<pair<int,int>>> edges(200005);
    vector<int> dist(10005, INF);
    vector<bool> visited (10005, false);
    vector<long long> path(10005, 1);
    priority_queue<pair<int,int>> pq;
    while (E--)
    {
        cin >> u >>v>>w;
        edges[u].emplace_back(v,w);
    }
    cin >> s >>t;
    dist[s] = 0;
    pq.emplace(0,s);
    while(!pq.empty())
    {
        curr = pq.top().second;
        currcost = - pq.top().first;
        pq.pop();
        if (!visited[curr]) {
            visited[curr] = true;
            int size = edges[curr].size();
            for (int i =0 ; i<size; i++)
            {
                next = edges[curr][i].first;
                nextcost = edges[curr][i].second;
                if (dist[next]> currcost + nextcost)
                {
                    dist[next] = currcost + nextcost;
                    path[next] = path[curr];
                    if (!visited[next])
                        pq.emplace(-dist[next],next);
                }
                else if (dist[next] == currcost+nextcost)
                    path[next] = path[next] + path[curr];
            }
        }
    }
    if (!visited[t])
        cout << 0;
    else
        cout << path[t];
    return 0;
}