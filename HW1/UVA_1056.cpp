#include <iostream>
#include <map>
#include <vector>


#define INF 1e5


using namespace std;


int main() {
    int P, R, count, x,y, max, cases =0;
    string a,b;
    cin >> P >> R;
    while (P != 0 && R != 0)
    {
        map<string, int> peoples;
        vector<vector<int>> adj (P, vector<int> (P, INF));
        count=0,max =0;
        for(int i = 0; i < P; i++) {
            adj[i][i] = 1;
        }
        for(int i = 0; i < R; i++) {
            cin >> a >>b;
            if(peoples.find(a) == peoples.end())
                peoples[a] = count++, x = count-1;
            else    x = peoples.find(a)->second;
            if(peoples.find(b) == peoples.end())
                peoples[b] = count++, y = count-1;
            else    y = peoples.find(b)->second;
            adj[x][y] = 1;
            adj[y][x] = 1;
        }
        for(int i = 0; i < P; i++) {
            for(int j = 0; j < P; j++) {
                for(int k = 0; k < P; k++) {
                    if(adj[j][k] > adj[j][i] + adj[i][k])
                        adj[j][k] = adj[j][i] + adj[i][k];
                }
            }
        }
        for(int i = 0; i < P; i++)
            for(int j = 0; j < P; j++)
                if(adj[i][j] > max)
                    max = adj[i][j];
        cout<<"Network "<< ++cases<< ": ";
        if(max == INF)
            cout<<"DISCONNECTED" << endl;
        else
            cout << max << endl;
        cout <<endl;
        cin >> P >> R;
    }
    return 0;
}