#include <iostream>
#include <algorithm>
#include <vector>
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

vector<bool> valid, used;


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
int Kruskal(vector<iii>& edges, int n, bool mode) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0, iter =0, sets = n;
    unionfind components(n);
    for (iii e : edges) {
        if (valid[iter]) {
            if (components.find(e.second.first) != components.find(e.second.second)) {
                mst_cost += e.first;
                components.unite(e.second.first, e.second.second);
                if (mode)
                    used[iter] = true;
                sets--;
            }
        }
        iter++;
    }
    return (sets == 1) ? mst_cost : INF;
}

int secondKruskal(vector<iii>& edges, int n)
{
    int min = INF, temp;
    for(int i=0; i<edges.size(); i++){
        if(used[i]){
            valid[i] = false;
            temp = Kruskal(edges,n,false);
            if(temp < min)
                min = temp;
            valid[i] = true;
        }
    }
    return min;
}



int main() {
    int t, m,n, a,b,c, s1,s2;
    vector<iii> edges;
    cin >> t;
    while (t--)
    {
        cin >> n >>m;
        edges.clear();
        used.assign(m, false);
        valid.assign(m, true);
        for (int i =0; i< m;i++)
        {
            cin >> a>> b >>c;
            edges.push_back({c,{a-1,b-1}});
        }
        s1 = Kruskal(edges,n, true);
        s2 = secondKruskal(edges,n);
        cout << s1 << " " << s2 << endl;
    }
    return 0;
}