#include <iostream>
#include <vector>

#define INF 6e6
using namespace std;

vector<vector<int>> adjmat;
vector<int> part_of_neg_cycle;


int main() {
    int n,m,q,u,v,w;
    cin >> n >>m >>q;
    while ((n != 0) && (q !=0))
    {
        adjmat.assign(n, vector<int>(n, INF));
        part_of_neg_cycle.clear();
        for (int i=0;i<n;i++){
            adjmat[i][i] = 0;
        }
        for (int i=0;i<m;i++){
            cin >> u >> v >> w;
            adjmat[u][v] = min(adjmat[u][v], w);
        }
        for (int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for (int j=0;j<n;j++){
                    if ((adjmat[i][k] == INF) || (adjmat[k][j] == INF))
                        continue;
                    adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                }
            }
        }
        for (int i=0;i<n;i++){
            if (adjmat[i][i] < 0){
                part_of_neg_cycle.emplace_back(i);
            }
        }
        for (int q_num = 0; q_num < q; q_num++){
            cin >> u >> v;
            bool neg_inf = false;
            for (auto k: part_of_neg_cycle){
                if ((adjmat[u][k] < INF) && (adjmat[k][v] < INF)){
                    neg_inf = true;
                    break;
                }
            }
            if (neg_inf){
                cout << "-Infinity" << endl;
            }
            else if (adjmat[u][v] == INF){
                cout << "Impossible" << endl;
            }
            else{
                cout << adjmat[u][v] <<endl;
            }
        }
        cout << endl;
        cin >> n >>m >>q;
    }
    return 0;
}
