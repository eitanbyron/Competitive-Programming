#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#define EPS 1e-9
#define MAX_SIZE 100
using namespace std;
#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

struct unionfind {
    vector<int> parent;
    vector<int> rank;
    vector<int> sizes;
    vector<int> empty_set;
    unionfind(int size) {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;

        sizes.assign(size, 1);
        empty_set.assign(size, 1);
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void Union(int i, int j) {
        if (find(i) == find(j)) return;
        int x = find(i), y = find(j);
        if (rank[x] > rank[y]) swap(x, y);
        parent[x] = y;
        if (rank[x] == rank[y]) ++rank[y];
        sizes[y] += sizes[x];
        empty_set[y] += empty_set[x];
    }

};

int main(){
    int n, l, a, b;
    cin >> n >> l;
    unionfind uf(l);
    for (int item=0; item<n; item++){
        cin >> a >> b;
        a--;
        b--;
        bool cannotFit = false;
        if (uf.sizes[uf.find(a)] == 1){
            uf.empty_set[uf.find(a)]--;
            uf.Union(a, b);
        }
        else if (uf.sizes[uf.find(a)] == 1){
            uf.empty_set[uf.find(b)]--;
            uf.Union(a, b);
        }
        else if (uf.empty_set[uf.find(a)] > 0){
            uf.empty_set[uf.find(a)]--;
            uf.Union(a, b);
        }
        else if (uf.empty_set[uf.find(b)] > 0){
            uf.empty_set[uf.find(b)]--;
            uf.Union(a, b);
        }
        else{
            cannotFit = true;
        }
        if (cannotFit){
            cout << "SMECE" <<endl;
        }
        else cout << "LADICA" <<endl;


    }


    return 0;
}
