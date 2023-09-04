#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
void recursion(vi& v, vi costs, int order) {
    vector<int> ans;

    if(v[order] == -2) {
        cout << "Impossible" << endl;
        return;
    }

    if(v[order] == -1) {
        cout << "Ambiguous" << endl;
        return;
    }

    while(order > 0) {
        ans.push_back(v[order]+1);
        order -= costs[v[order]];
    }

    if(order < 0) {
        cout << "Ambiguous" << endl;
        return;
    }

    sort(ans.begin(), ans.end());
    for(auto i : ans) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    vi v(32000, -2);
    v[0] = 0;

    int n;
    cin >> n;
    vi costs(n);
    for(auto& i : costs) {
        cin >> i;
    }

    for(int i = 0; i < n; i++) {
        int cost = costs[i];
        for(int j = 0; j <= 30000; j++) {
            if(v[j] >= 0) {
                if(v[j+cost] == -2) {
                    v[j+cost] = i;
                }
                else {
                    v[j+cost] = -1;
                }
            }
            if(v[j] == -1) {
                v[j+cost] = -1;
            }
        }
    }

    int m;
    cin >> m;
    for(int i = 0; i < m; i++) {
        int order;
        cin >> order;

        recursion(v, costs, order);
    }
}