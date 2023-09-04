#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


using namespace std;

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size) {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
    }
    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x) {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember; }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            return;
        }
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};


int main()
{
    int n;
    string s1, s2;
    int counter =0;
    unordered_map<string, int> ht;
    std::cin >> n;
    vector<int> arr(2*n,1);
    unionfind uf(2*n);
    for (int i=0; i<n; i++)
    {
        cin>> s1;
        cin >>s2;
        if (ht.find(s1) == ht.end())
        {
            ht[s1] = counter;
            counter++;
        }
        if (ht.find(s2) == ht.end())
        {
            ht[s2] = counter;
            counter++;
        }
        int p1 = uf.find(ht[s1]);
        int p2 = uf.find(ht[s2]);
        uf.Union(ht[s1],ht[s2]);
        int pnew = uf.find(ht[s1]);
        if (p1 == p2)
            cout << arr[p1]<<endl;
        else
        {
            arr[pnew] = arr[p1]+arr[p2];
            cout << arr[pnew]<<endl;
        }
    }
    return 0;
}