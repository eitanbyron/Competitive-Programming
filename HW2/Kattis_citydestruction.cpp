//
// Created by barbe on 24/06/2023.
//
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<ll>> vvll;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
const int INF = 1e9;
int n;
ll d;
vvll mem;
vll h, e;

ll dp(int i, bool is_prev_destroyed)
{
    if (i == n) {
        return 0;
    }
    ll &answer = mem[i][is_prev_destroyed];
    if (answer != -1) {
        return answer;
    }
    ll current_health = h[i];

    if (i > 0 && is_prev_destroyed) {
        current_health -= e[i - 1];
    }

    if (current_health <= 0) {
        answer = dp(i + 1, true);
    }

    else {
        ll times_to_fully_destroy_current = (current_health - 1) / d + 1;
        ll time_to_fully_destroy_by_next;

        if(current_health - e[i+1] <=0){
            time_to_fully_destroy_by_next = 0;
        }
        else{
            time_to_fully_destroy_by_next = (current_health - e[i + 1] - 1) / d + 1;
        }
        answer = min(dp(i + 1, true) + times_to_fully_destroy_current, dp(i + 1, false) + time_to_fully_destroy_by_next);
    }
    return answer;
}
int main()
{
    int test_cases;
    cin >> test_cases;
    for (int t = 0; t < test_cases; ++t) {
        cin >> n >> d;
        e.assign(n + 1, 0);
        h.assign(n + 1, 0);
        mem.assign(n, vector<ll>(2, -1));
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> e[i];
        }
        cout << dp(0, false) << endl;
    }
    return 0;
}
